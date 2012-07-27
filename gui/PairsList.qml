/***/
import QtQuick 1.0
import "data"
import "controls"
import "controls/adaptive_search"

Rectangle {
	id: page
	x: 0
	property bool active : false
	color: "black"

	anchors.top: parent.top
	anchors.bottom: parent.bottom
	width: 320
	height: 320

	signal formPairs

	// The actual list
	ListView { id: listView
		anchors.fill: parent

		model: duels
		delegate: PairsDelegate {}

		ScrollBar {
			flickable: listView
			vertical: true
		}

		TextButton { id : form_pairs_button
			opacity: (page.active && 0 == listView.count) ? 1 : 0
			text : "Form pairs atomatically"
			height: 100
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			onClicked: {
				page.formPairs()
			}
		}
	}
}
