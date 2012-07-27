/***/
import QtQuick 1.0
import "data"
import "controls"
import "ParticipantFunctions.js" as PartHelper

// Delegate for the single participant.
// This delegate has two states:
// 1. List mode (default), which just shows the picture, title and team.
// 2. Details mode

Component {

	Item { id: round

		// a property to contain the visibility of the details.
		property real detailsOpacity : 0

		property alias name : name_caption.text

		state: status

		height: parent.height
		width: 70
		clip: true

		// A simple rounded rectangle for the background
		Rectangle {
			id: background
			x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
			border.color: "gray"
			property color selection_color : "yellow"
			color: round.ListView.isCurrentItem ? selection_color : "white"
			radius: 5
			state: status

			MouseArea {
				anchors.fill: parent
				MouseArea{
					anchors.fill : parent
					onClicked: {
						round.ListView.view.currentIndex = index
						round.ListView.view.current_round_name = round.name
						duels.select_round(round.name)
					}
				}
			}

			Text { id : name_caption
				z : 1
				anchors.horizontalCenter: parent.horizontalCenter
				text : model.name
			}

			Text { id : state_caption
				y: 10
				z : 1
				anchors.horizontalCenter: parent.horizontalCenter
				text : round.state
			}
/*
			TextButton { id: details_button
				y: 10
				height: 10
				anchors.horizontalCenter: parent.horizontalCenter
				text : "< >"
				onClicked: {

				}
			}
*/
			states: [
				  State { name: "planned"
					PropertyChanges { target: background; selection_color: "black"; opacity : 0 }
				}

				, State { name: "opened"
					PropertyChanges { target: background; selection_color: "yellow" }
					//PropertyChanges { target: participant.ListView.view; explicit: true; contentY: participant.y }
					// Disallow flicking while we're in detailed view
					//PropertyChanges { target: participant.ListView.view; interactive: false }

				}

				, State { name: "started"
					PropertyChanges { target: background; selection_color: "red" }
				}

				, State { name: "finished"
					PropertyChanges { target: background; selection_color: "green" }
				}
			]

			transitions: Transition { // Make the state changes smooth

				ParallelAnimation {

					ColorAnimation {
						property: "color"
						duration: 300
					}

					NumberAnimation {
						duration: 300
						properties: "detailsOpacity,x,contentY,height,width"
					}
				}
			}
		}
	}
}
