/***/
import QtQuick 1.0

Rectangle
{
	id: main_page
	
	width: 400
	height: 600
	
	MouseArea
	{
		anchors.fill: parent
		onClicked: {
			   Runtime.getRuntime().exec(myCommand);
		}
	}
}