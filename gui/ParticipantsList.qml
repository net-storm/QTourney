/***/
import QtQuick 1.0
import "data"
import "controls"
import "controls/adaptive_search"

Rectangle
{
	id: page
	property alias hide_state: listView.hide_state
	x: 0
	color: "black"

	anchors.top: parent.top
	anchors.bottom: parent.bottom
	width: 320
	height: 320

	// The actual list
	ListView {
		id: listView
		property string hide_state:''
		anchors.fill: parent

		model: registration
		//model: Participants {}
		delegate: ParticipantsDelegate {}

		function form_pairs() {
			model.form_pairs("1","2")
		}

		ScrollBar {
			flickable: listView
			vertical: true
		}

		AdaptiveSearch {
			id: adaptive
			anchors.fill: parent
			model: parent.model

			onFilterUpdated: {
				listView.model = adaptive.filtermodel
			}
		}
	}
}
