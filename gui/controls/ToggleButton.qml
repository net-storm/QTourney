/***/

import QtQuick 1.0

Rectangle
{
	id: container

	property alias text: label.text

	signal clicked

	width: label.width + 20;
	height: label.height + 10
	smooth: true
	radius: 10

	gradient: Gradient
	{
		GradientStop { id: gradient_stop; position: 0.0; color: palette.light }
		GradientStop { position: 1.0; color: palette.button }
	}

	SystemPalette {
		id: palette
	}

	MouseArea {
		id: mouse_area
		anchors.fill: parent
		onClicked: {
			container.state = container.state==""? 'toggled' : ""
			container.clicked()
		}
	}

	Text {
		id: label
		anchors.centerIn: parent
	}

	states: State {
		name: "toggled"
		//PropertyChanges { target: gradient_stop ; color: palette.dark }
	}
}
