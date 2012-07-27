/***/

import QtQuick 1.0

Rectangle
{
	id: control

	property alias label_text: label.text
	property alias value_text: value.text

	height: base_layout.height
	width: base_layout.width
	Row
	{
		id: base_layout
		height: label.height + 10
		spacing: 5

		Text {
			id: label
			text: "label_text"
			font.bold: true; font.pointSize: 14
			anchors.baseline: parent.bottom
		}

		Text
		{
			id: separator
			text: ":"
			font.bold: true; font.pointSize: 14
			anchors.baseline: parent.bottom
		}

//		Rectangle
//		{
//			id: edit_background
//			border.color: "gray"
//			//anchors.right: base_layout.right
//			height: base_layout.height
//			//width: base_layout.width

			TextEdit
			{
				id: value
				text: "value_text"
				font.pointSize: 12
				anchors.baseline: parent.bottom
			}
//		}
	}
}


