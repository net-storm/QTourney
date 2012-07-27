/***/

import QtQuick 1.0
import "controls"

Rectangle
{
	id: slide

	anchors.top: parent.top
	anchors.bottom: parent.bottom

	width: 0;
	color: "black"
	//border.width: 2
	//border.color: "darkgray"

	states: State {
		name: "opened"
		PropertyChanges { target: slide; width: 400 }
//		PropertyChanges { target: children; opacity: 1 }
	}

	transitions: Transition {
		PropertyAnimation {
			properties: "width,x,y,opacity"
			duration: 300;
		}
	}
}
