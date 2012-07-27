#ifndef LOG_FILE_HPP
#define LOG_FILE_HPP

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <vector>

#include <libs/participant.hpp>

class QFile;

class LogFile
	: public QObject
{
	Q_OBJECT
	typedef boost::shared_ptr<QFile> log_file_t;
public:
	explicit LogFile(const std::string& name);

public slots:
	void append(const QString & str);

private:
	log_file_t m_log_file;
};

#endif
