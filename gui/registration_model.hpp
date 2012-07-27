#ifndef _FHVBXCVHSFGJSGVNXCVNHBHKDFG_
#define _FHVBXCVHSFGJSGVNXCVNHBHKDFG_

#include <QAbstractListModel>
#include <boost/shared_ptr.hpp>
#include <vector>

#include <libs/participant.hpp>

class Registration
	: public QAbstractListModel
{
	Q_OBJECT
	typedef std::vector<tournament::participant> participant_list;
	typedef participant_list::const_iterator participant_iter;
public:
	Registration(QObject *parent = 0);

	void load(const std::string& file_name);

	void add(const std::string&);

public slots:

	int rowCount(const QModelIndex & parent = QModelIndex()) const;

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	bool update(int index, const QString & source, const QVariant &value);

	bool form_pairs(const QString & round_name, const QString & round_options);

	bool find_and_update(const QString & record);

signals:

	void new_pair(const QString& record);

	void round_state_changed(const QString & round_name, const QString & round_state);

	void log(const QString &str);

private:
	participant_list m_participants;
};

#endif
