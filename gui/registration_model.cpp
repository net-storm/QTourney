#include <libs/participant.hpp>
#include "registration_model.hpp"
#include <QString>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QProcess>
// Standard includes
#  include <boost/make_shared.hpp>
#  include <boost/program_options.hpp>
#  include <boost/tokenizer.hpp>
#  include <boost/algorithm/string.hpp>
#  include <boost/lexical_cast.hpp>
#  include <algorithm>
#  include <functional>
#  include <iostream>
#  include <fstream>
#  include <iterator>
#  include <list>

namespace {

static QString to_string(const QString& value)
{
	return value.toUtf8().data();
}

static QString from_string(const std::string& value)
{
	return QString::fromUtf8(value.c_str(),value.size());
}

static int from_integer(const int value)
{
	return value;
}

}

void Registration::load(const std::string& file_name)
{
	std::ifstream is(file_name.c_str());
	if(is.bad()) std::cerr << "Unable to open file " << file_name << std::endl;
	emit log("  # Loading participants");
	std::string input_line;
	while(getline(is, input_line)) {
		using namespace boost::algorithm;
		std::string trimed_record = trim_copy(input_line);
		if ("END" != trimed_record) {
			try {
				update_participant_list(m_participants, trimed_record);
				emit log(from_string(trimed_record));
			} catch (const std::runtime_error& e) {
				std::cerr << "error: " << e.what() << std::endl;
			}
		} else {
			break;
		}
	}
	emit log("  # Registration started");
}

int Registration::rowCount(const QModelIndex &) const
{
	return m_participants.size();
}

Registration::Registration(QObject *parent)
	: QAbstractListModel(parent)
{
	QHash<int, QByteArray> roles;
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	roles[tournament::participant::prop_role_##prop_name + Qt::UserRole + 1] = #prop_name;
#include <libs/participant.inc>
	setRoleNames(roles);
}

QVariant Registration::data(const QModelIndex & index, int role) const
{
	if (index.row() < 0 || static_cast<std::size_t>(index.row()) > m_participants.size()) {
		return QVariant();
	}
	const tournament::participant &persone = m_participants[index.row()];

	switch(role) {
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	case tournament::participant::prop_role_##prop_name + Qt::UserRole + 1 : return from_##type_of_prop(persone.prop_name());
#include <libs/participant.inc>
		default :  return QVariant();
	}
}

bool Registration::update(int raw, const QString & role, const QVariant &value)
{
	find_and_update(value.toString());
	return true;
}

bool Registration::find_and_update(const QString &record)
{
	std::vector<std::size_t> changed_indexes;
	try {
		std::string trimed_record(record.toUtf8().data());
		changed_indexes = update_participant_list(m_participants, trimed_record);
		emit log(from_string(trimed_record));

		std::vector<std::size_t>::const_iterator itr = changed_indexes.begin();
		std::vector<std::size_t>::const_iterator end = changed_indexes.end();
		for (; itr != end; ++itr) {
			QModelIndex current = QAbstractListModel::index(*itr);
			emit dataChanged(current,current);
		}

	} catch (const std::runtime_error& e) {
		std::cerr << "error: " << e.what() << std::endl;
	}
	return true;
}

bool Registration::form_pairs(const QString & round_name, const QString & round_options)
{
	QStringList arguments;
//	arguments << round_options;

	QProcess form_pairs;
	form_pairs.start("./form_pairs", arguments);
	if (!form_pairs.waitForStarted())
		return false;

	std::string buffer;
	{
		participant_iter itr = m_participants.begin();
		participant_iter end = m_participants.end();
		for(;end != itr;++itr){
			if ("Reg" == itr->status()) {
				buffer = buffer + "\n" + itr->serialize();
			}
		}
	}
	if (buffer.empty()) return false;
	buffer += "/nEND";

	emit log("  # Forming pairs for " + round_name + " with options : "+ round_options);
	form_pairs.write(from_string(buffer).toUtf8());
	form_pairs.closeWriteChannel();

	if (!form_pairs.waitForFinished()) return false;

	{
		QString result = QString::fromUtf8(form_pairs.readAll());
		QStringList pairs_list = result.split("\n", QString::SkipEmptyParts);

		QStringList::const_iterator itr = pairs_list.constBegin();
		QStringList::const_iterator end = pairs_list.constEnd();
		for (; itr != end; ++itr) { emit new_pair(*itr); }
	}
	emit log("  # " + round_name + " started");
	return true;
}


