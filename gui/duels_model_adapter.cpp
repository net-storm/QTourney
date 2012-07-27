#include "duels_model_adapter.hpp"
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

}

Duels::Duels(Tournament * data_model)
	: QAbstractListModel(0)
	, m_tournament(data_model)
{
	QHash<int, QByteArray> roles;
	roles[Qt::UserRole + 1] = "status";
	roles[Qt::UserRole + 2] = "ground";
	roles[Qt::UserRole + 3] = "details";
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	roles[(tournament::participant::prop_role_##prop_name * 2 - 1) + Qt::UserRole + 100] = QByteArray("left_") + #prop_name; \
	roles[(tournament::participant::prop_role_##prop_name * 2 - 0) + Qt::UserRole + 100] = QByteArray("right_") + #prop_name;
#include <libs/participant.inc>
	setRoleNames(roles);
}

int Duels::rowCount(const QModelIndex &) const
{
	return m_tournament->duels_count();
}

QVariant Duels::data(const QModelIndex & index, int role) const
{
	if (index.row() < 0 || static_cast<std::size_t>(index.row()) > rowCount()) {
		return QVariant();
	}
	const tournament::duel &a_duel = m_tournament->get_current_round().get_duel(index.row());
	const tournament::participant &winner = a_duel.winner();
	const tournament::participant &loser  = a_duel.loser();

	switch(role) {
		case Qt::UserRole + 1 : return from_string(a_duel.state());
		case Qt::UserRole + 3 : return from_string("");
		case Qt::UserRole + 2 : return from_string(a_duel.details());
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
		case (tournament::participant::prop_role_##prop_name * 2 - 1) + Qt::UserRole + 100 : return from_##type_of_prop(winner.prop_name()); \
		case (tournament::participant::prop_role_##prop_name * 2 - 0) + Qt::UserRole + 100 : return from_##type_of_prop(loser.prop_name());
#include <libs/participant.inc>
		default :  break;
	}
	return QVariant(); // just nothing
}

bool Duels::add_pair(const QString &record)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	const bool result = update(rowCount(), record);
	endInsertRows();
	return result;
}

bool Duels::update(int index, const QString &record)
{
	if (m_tournament->update_pair(to_string(record))) {
		const tournament::round &current_round = m_tournament->get_current_round();

		emit log(from_string(current_round.name()) + " " + record);

		emit round_state_changed(from_string(current_round.name()));

		if (current_round.complete()) {
			emit log("  # " + from_string(current_round.name()) + " " + from_string(current_round.status()));
			emit log("  # Winners");
			list_participants(current_round.winners());
			emit log("  # Losers");
			list_participants(current_round.losers());

			int index = m_tournament->round_index(current_round.name()) + 1;
			assert (index > 0 );

			if (index < m_tournament->rounds_count()) {
				emit round_state_changed(from_string(m_tournament->get_round(index).name()));
			} else {
				emit log("  # Tournament finished");
			}
		}

		QModelIndex current = QAbstractListModel::index(index);
		emit dataChanged(current,current);
		return true;
	}
	return false;
}

void Duels::list_participants( const participants & a_collection )
{
	participants::const_iterator itr = a_collection.begin();
	participants::const_iterator end = a_collection.end();
	for (; itr != end; ++itr) {
		QString record_update = from_string(itr->serialize_all());
		emit log(record_update);
		emit data_changed(record_update);
	}
}

bool Duels::select_round(const QString &new_name)
{
	beginRemoveRows(QModelIndex(), 0, rowCount()-1);
	m_tournament->select_round(to_string(new_name));
	endRemoveRows();

	beginInsertRows(QModelIndex(), 0, rowCount()-1);
	endInsertRows();

	int size = rowCount();
	QModelIndex first = QAbstractListModel::index(0);
	QModelIndex last  = QAbstractListModel::index(rowCount()-1);
	emit dataChanged(first,last);
	return true;
}
