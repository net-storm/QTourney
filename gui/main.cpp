#include "log_file.hpp"
#include <libs/tournament.hpp>
#include "registration_model.hpp"
#include "duels_model_adapter.hpp"
#include "rounds_model_adapter.hpp"
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QApplication>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	QDeclarativeView view;
	QDeclarativeContext *ctxt = view.rootContext();

	LogFile log_file("log.txt");

	Registration registration_model;
	ctxt->setContextProperty("registration", &registration_model);

	QObject::connect(
		  &registration_model	, SIGNAL(log(QString))
		, &log_file				, SLOT(append(QString))
	);

	Tournament root_model;

	Rounds rounds_model(&root_model);
	ctxt->setContextProperty("rounds", &rounds_model);

	QObject::connect(
		  &rounds_model			, SIGNAL(log(QString))
		, &log_file				, SLOT(append(QString))
	);

	Duels duels_model(&root_model);
	ctxt->setContextProperty("duels", &duels_model);

	QObject::connect(
		  &duels_model			, SIGNAL(log(QString))
		, &log_file				, SLOT(append(QString))
	);
	QObject::connect(
		  &registration_model	, SIGNAL(new_pair(QString))
		, &duels_model			, SLOT(add_pair(QString))
	);
	QObject::connect(
		  &duels_model			, SIGNAL(data_changed(QString))
		, &registration_model	, SLOT(find_and_update(QString))
	);
	QObject::connect(
		  &duels_model			, SIGNAL(round_state_changed(QString))
		, &rounds_model			, SLOT(find_and_update(QString))
	);

	rounds_model.load("rounds.txt");
	registration_model.load("list.txt");

	view.setSource(QUrl("QRC:tournament.qml"));
	view.show();

	return app.exec();
}
