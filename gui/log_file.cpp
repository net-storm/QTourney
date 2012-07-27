#include "log_file.hpp"
#include <QDebug>
#include <QFile>

// Standard includes
#  include <boost/make_shared.hpp>

namespace {

static QFile * open(const std::string & filename, const QIODevice::OpenMode & mode)
{
	QFile * handler = new QFile(filename.c_str());
	handler->open(mode);
	return handler;
}

static void close_on_destruction(QFile * handler)
{
	handler->close();
	delete handler;
}

}

LogFile::LogFile(const std::string & name)
	: m_log_file(open(name.c_str(), QIODevice::WriteOnly | QIODevice::Truncate), close_on_destruction)
{ }

void LogFile::append(const QString & str)
{
	QTextStream writeData(m_log_file.get());
	writeData << str << endl;
	qDebug() << str;
}
