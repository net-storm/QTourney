#ifndef ROUNDS_ADAPTER_MODEL_HPP
#define ROUNDS_ADAPTER_MODEL_HPP

#include <QAbstractListModel>
#include <libs/duel.hpp>

namespace tournament {

class participant;
class round;

}

class Tournament;

class Rounds
	: public QAbstractListModel
{
	Q_OBJECT
public:

	explicit Rounds(Tournament *);

	//Q_PROPERTY(QString current_round_state READ get_current_round_state)

	//QString get_current_round_state() const;

	void load(const std::string &file_name);

	void add(const std::string &record);

public slots:

	int rowCount(const QModelIndex & parent = QModelIndex()) const;

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	bool find_and_update(const QString &round_name);

	//bool update(int index, const QString &record);

	//bool select_round(const QString & name);

	//bool set_round_state(const QString & name, const QString & state);

signals:

	void log(const QString &str);

	void data_changed(const QString &str);

private :
	Tournament  * m_tournament;
};

#endif // ROUNDS_ADAPTER_MODEL_HPP




