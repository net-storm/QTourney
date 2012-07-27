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

	Item { id: participant
		// a property to contain the visibility of the details.
		property real detailsOpacity : 0

		state: status == listView.hide_state? "Unshown" : ''

		height: 90
		width: parent.width
		clip: true

		// A simple rounded rectangle for the background
		Rectangle {
			id: background
			x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
			border.color: "gray"
			radius: 5
		}

		// This mouse region covers the entire delegate.
		// When clicked it changes mode to 'Details'.  If we are already
		// in Details mode, then no change will happen.
		MouseArea {
			anchors.fill: parent
			onClicked: participant.state = 'Details';
		}

		// Note that elements that should not be visible in the list
		// mode have their opacity set to recipe.detailsOpacity.
		Row {
			id: topLayout
			x: 10;
			y: 10;
			height: participantImage.height;
			width: parent.width
			spacing: 10

			Image {
				id: participantImage
				width: 70;
				height: 70
				source: "data/pics/teams/" + team + ".png"
			}

			Column {
				width: background.width - participantImage.width - 105;
				height: participantImage.height
				spacing: 5

				Text {
					id: nick_name
					text: (name !== "")? name : firstname + " " +surname
					font.bold: true; font.pointSize: 14
					width: details.width
				}

				Text {
					id: team_name
					text: team
					font.pointSize: 12; font.bold: true
					width: details.width
				}

				Text {
					id: rating_value
					text: "Rating: " + score
					width: details.width
				}

				Row	{
					spacing: 5

					TextButton
					{
						opacity: participant.detailsOpacity
						text: "Ok"
						width: 70
						height: 35
						onClicked: { participant.state = ''}
					}

					TextButton
					{
						opacity: participant.detailsOpacity
						text: "Apply"
						width: 70
						height: 35

						onClicked:
						{
							score = 1600;
							//myModel.save();
						}
					}

					TextButton {
						opacity: participant.detailsOpacity
						text: "Close"
						width: 70
						height: 35
						onClicked: participant.state = '';
					}
				}
			}

			ToggleButton {
				id: register_button
				width: 70
				height: 35
				anchors.bottom: parent.bottom
				opacity: 1 - participant.detailsOpacity
				state: status == listView.hide_state? "toggled": ""
				text : listView.hide_state == "Add" ? "Kick" : "Reg"
				onClicked: {
					listView.model.update(index, "status", listView.hide_state + PartHelper.serialize_all(model))
				}
			}
		}

		Item {
			id: details
			x: 10; width: parent.width - 20
			anchors { top: topLayout.bottom; topMargin: 10; bottom: parent.bottom; bottomMargin: 10 }
			opacity: participant.detailsOpacity

			Column {
				spacing: 10
				width: parent.width
				anchors.fill: parent

				Text
				{
					id: properties_title
					text: "Properties"
					font.pointSize: 12; font.bold: true
				}

				Flickable
				{
					id: flick
					width: parent.width
					height: parent.height - 3 * parent.spacing
					contentHeight: parent.height - 2 * parent.spacing

					clip: true

					Column
					{
						id: properties_layout
						spacing: 5

						LabeledText { label_text: "Surname";	value_text: last_name }
						LabeledText { label_text: "Firstname";  value_text: first_name }
						LabeledText { label_text: "Midname";	value_text: middle_name }
						LabeledText { label_text: "Nick";	   value_text: name }
						LabeledText { label_text: "Team";	   value_text: team }
						LabeledText { label_text: "Rating";	 value_text: score }
						//LabeledText { label_text: "Statiscics"; value_text: stats }
						//LabeledText { label_text: "Notes";	  value_text: note }
					}

					Image
					{
						anchors { right: parent.right; top: parent.top }
						source: "data/pics/moreUp.png"
						opacity: parent.atYEnd ? 0 : 1
					}

					Image
					{
						anchors { right: parent.right; bottom: parent.bottom }
						source: "data/pics/moreDown.png"
						opacity: parent.atYBeginning ? 0 : 1
					}
				}
			}
		}

		states: [
			  State {
				name: "Details"

				PropertyChanges { target: background; color: "white" }
				PropertyChanges { target: participantImage; width: 130; height: 130 } // Make picture bigger
				PropertyChanges { target: participant; detailsOpacity: 1; x: 0 } // Make details visible
				PropertyChanges { target: participant; height: listView.height } // Fill the entire list area with the detailed view

				// Move the list so that this item is at the top.
				PropertyChanges { target: participant.ListView.view; explicit: true; contentY: participant.y }

				// Disallow flicking while we're in detailed view
				PropertyChanges { target: participant.ListView.view; interactive: false }
			}

			, State {
				name: "Unshown"
				when: register_button.state == 'toggled'

				PropertyChanges { target: background; color: "white" }
				PropertyChanges { target: participantImage; width: 0; height: 0 }
				PropertyChanges { target: participant; height: 0 }
				PropertyChanges { target: register_button; height: 0 }
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
