 TEMPLATE = app

 QT += declarative

 INCLUDEPATH += ./.. 
 INCLUDEPATH += C:/boost/104601
 

RESOURCES += tournament.qrc

 HEADERS = \
    log_file.hpp \
    registration_model.hpp \
    tournament_model.hpp \
    rounds_model_adapter.hpp \
    ../libs/tournament.hpp \
    duels_model_adapter.hpp
 SOURCES = main.cpp \
		   ../libs/participant.cpp \
    ../libs/round.cpp \
    ../libs/duel.cpp \
    ../libs/details/state.cpp \
    ../libs/details/states/win.cpp \
    ../libs/details/states/tie.cpp \
    ../libs/details/states/forfeit.cpp \
    ../libs/details/states/fighting.cpp \
    ../libs/details/states/factory.cpp \
    ../libs/details/states/challenge.cpp \
    ../libs/details/states/canceled.cpp \
    log_file.cpp \
    registration_model.cpp \
    duels_model_adapter.cpp \
    rounds_model_adapter.cpp \
    ../libs/tournament.cpp

OTHER_FILES += \
	test.qml \
	SlidePannel.qml \
	ParticipantsList.qml \
	ParticipantsDelegate.qml \
	ParticipantFunctions.js \
	tournament.qml \
	controls/ScrollBar.qml \
	controls/Scrollable.qml \
	controls/LabeledText.qml \
	controls/ImageButton.qml \
	controls/TextButton.qml \
	controls/ToggleButton.qml \
    PairsDelegate.qml \
    PairsList.qml \
    controls/SpinButtons.qml \
    RoundsList.qml \
    RoundsDelegate.qml

CONFIG (debug, debug|release) {
	CONFIG       += console
}
