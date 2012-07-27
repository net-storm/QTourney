#ifndef DUELS_MODEL_ADAPTER_H
#define DUELS_MODEL_ADAPTER_H

#include <QAbstractListModel>
#include <libs/duel.hpp>

namespace tournament {

class participant;
class round;

}

class Tournament;

class Duels
	: public QAbstractListModel
{
	Q_OBJECT
	typedef std::vector<tournament::participant> participants;
public:
	explicit Duels(Tournament * data_model);

public slots:

	int rowCount(const QModelIndex & parent = QModelIndex()) const;

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	bool add_pair(const QString & record);

	bool update(int index, const QString &record);

	bool select_round(const QString &new_name);

signals:

	void log(const QString &str);

	void data_changed(const QString &str);

	void round_state_changed(const QString &str);

private :

	void list_participants( const participants & a_collection );

private :
	Tournament  * m_tournament;
};

#endif // DUELS_MODEL_ADAPTER_H
