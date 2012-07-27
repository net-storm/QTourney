/***/
import QtQuick 1.0

Rectangle
{
	id: container
	color: "darkgray"
	width: 30; height: 30
	property alias image_source: picture.source

	signal clicked

	Image { id: picture
		anchors.centerIn: parent
		source: "pics/exit.png"
	}

	MouseArea {	id: mouse_area
		anchors.fill: parent
		z : 1
		onClicked: {
			container.clicked()
		}
	}

	SystemPalette { id: palette }

	states: State { name: "pressed"
		when: mouse_area.pressed
		PropertyChanges { target: container; color: palette.dark }
	}
}

