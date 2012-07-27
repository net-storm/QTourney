#include "rounds_model_adapter.hpp"
#include <libs/tournament.hpp>
#include <libs/round.hpp>
#include <libs/duel.hpp>
#include <libs/details/state.hpp>
#include <libs/participant.hpp>
#include <libs/details/states/factory.hpp>

#include <QString>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QProcess>

// Standard includes
#include <string>

namespace {

static std::string to_string(const QString& value)
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

static bool from_deathmatch_t(const bool value)
{
	return value;
}

}

void Rounds::load(const std::string& file_name)
{
	emit log("  # Loading tournament agenda");
	std::ifstream is(file_name.c_str());
	if(is.bad()) std::cerr << "Unable to open file " << file_name << std::endl;
	using namespace boost::algorithm;
	std::string input_line;
	while(getline(is, input_line)) {
		if ("END" == trim_copy(input_line)) {
			break;
		} else {
			add(input_line);
		}
	}
	m_tournament->open_next_round();
}

void Rounds::add(const std::string& record)
{
	std::string trimed_record = boost::algorithm::trim_copy(record);
	if (trimed_record.empty()) return;
	if (trimed_record[0] == '#') return;

	tournament::round new_round = tournament::round(record);
	if (new_round.is_invalid()) {
		std::cerr << "record " + record + " is invalid" << std::endl;
		return;
	}
	m_tournament->add_round(new_round);
	emit log(from_string(record));
}

bool Rounds::find_and_update(const QString &round_name)
{
	int index = m_tournament->round_index(to_string(round_name));
	if (index < 0) return false;

	tournament::round a_round = m_tournament->get_round(index);

	const std::string state = a_round.status();

	QModelIndex current = QAbstractListModel::index(index);

	//qDebug() << "Raw = " << index << " Role = " << action.c_str() << " Value =" << record;
	emit dataChanged(current,current);
	return true;
}

Rounds::Rounds(Tournament * data_model)
	: QAbstractListModel(0)
	, m_tournament(data_model)
{
	QHash<int, QByteArray> roles;
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
	roles[tournament::round::prop_role_##prop_name + Qt::UserRole + 1] = #prop_name;
#include <libs/round.inc>
	setRoleNames(roles);
}

int Rounds::rowCount(const QModelIndex & parent) const
{
	return m_tournament->rounds_count();
}

QVariant Rounds::data(const QModelIndex & index, int role) const
{
	if (index.row() < 0 || static_cast<std::size_t>(index.row()) > rowCount()) {
		return QVariant();
	}
	const tournament::round &a_round = m_tournament->get_round(index.row());
	switch(role) {
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
	case tournament::round::prop_role_##prop_name + Qt::UserRole + 1 : return from_##type_of_prop(a_round.prop_name());
#include <libs/round.inc>
		default :  break;
	}
	return QVariant(); // just nothing
}
