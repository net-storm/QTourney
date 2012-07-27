/***/

import QtQuick 1.0

Rectangle {
	id: control_background

	height: value_info.height

	property alias text: value_info.text
	property alias minus_image_source: minus_image.source
	property alias plus_image_source: plus_image.source
	property int min_value: 0
	property int value: 0
	property int max_value: 3

	Row {
		id : top_layout
		anchors.fill: parent
		spacing: 5

		TextButton {
			id : minus_button
			text: "-"
			width : 30
			anchors.verticalCenter: parent.verticalCenter
			onClicked: if(value > min_value) { value = value - 1 }
			Image {
				id: minus_image
				anchors.fill: parent
			}
		}

		TextButton {
			id : value_info
			text: value
			width : top_layout.width - minus_button.width - parent.spacing * 2 - plus_button.width
			anchors.verticalCenter: parent.verticalCenter
			Image {
				anchors.fill: parent
			}
		}

		TextButton {
			id : plus_button
			text: "+"
			width : 30
			anchors.verticalCenter: parent.verticalCenter
			onClicked: if(value < max_value) { value = value + 1 }
			Image {
				id: plus_image
				anchors.fill: parent
			}
		}
	}
}

