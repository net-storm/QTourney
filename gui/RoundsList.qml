/***/
import QtQuick 1.0
import "data"
import "controls"
import "controls/adaptive_search"

Rectangle {
	id: page
	color: "transparent"
	height: 30
	property alias current_round_name : listView.current_round_name
	property alias current_round_state : listView.current_round_state

	ListView { id: listView
		anchors.fill: parent
		orientation : ListView.Horizontal

		model: rounds
		delegate: RoundsDelegate {}

		focus: true
		currentIndex: -1
		property string current_round_name : currentItem == null? "not_selected" : currentItem.name
		property string current_round_state : currentItem == null? "planned" : currentItem.state
	}
}
