/***/
import QtQuick 1.0
import "data"
import "controls"
import "ParticipantFunctions.js" as Helper

// Delegate for the pair.
// This delegate has ??? states:

Component {

	Item { id: item

		// property to contain the visibility of the details.
		property real details_opacity : 0
		property real hits_opacity : 1
		property bool duel_is_over : false
		property bool left_wins : true

		state: status
		height: 105
		width: parent.width
		clip: true

		function serialize() {
			if (left_wins){
				return "% " + Helper.serialize(left_participart)
					+ " % " + item.state
					+ " % " + Helper.serialize(right_participart)
					+ " % " + details
			} else {
				return "% " + Helper.serialize(right_participart)
					+ " % " + item.state
					+ " % " + Helper.serialize(left_participart)
					+ " % " + details
			}
		}

		function update_model() {
			listView.model.update(index, serialize())
		}

		function update_model_from_state(state) {
			if (!item.duel_is_over) {
				update_model()
			}
		}

		Rectangle { id: background
			x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
			border.color: "gray"
			radius: 5
		}

		// Note that elements that should not be visible in the list
		// mode have their opacity set to item.details_opacity.
		Column { id: top_layout
			x: 10; y: 10;
			width: parent.width - x * 2;
			height: parent.height - y * 2

			Row { id : controls_section
				spacing: 10

				Column { id: side_holder
					width: 30; spacing: 5

					Rectangle { id: index_lable
						width: parent.width;
						height: left_participant_image.height;
						radius: 5
						border.color: "gray"

						Text { id: index_text_area
							anchors.fill: parent
							text: index
							font.bold: true; font.pointSize: 10
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}

					ImageButton { id : more_less_button
						width: parent.width;
						radius: 5
						height: left_participart_hits.height;
						image_source : item.state == "challenges" ? "data/pics/moreDown.png" : "data/pics/moreUp.png"
						onClicked: item.state == "challenges" ? item.state = 'fighting' : item.state = 'challenges'
					}

					TextButton { id : cancel_button
						width: parent.width;
						height: left_participart_fts.height;
						radius: 5
						text : "Cancel"
						opacity: item.details_opacity
					}

					TextButton { id : ok_button
						width: parent.width;
						height: 30
						radius: 5
						text : "Ok"
						opacity: item.details_opacity
						onClicked: item.update_model()
					}
				}

				Column { id: left_participart

					property alias name : left_participart_nick_name.text
					property alias team : left_participart_team.text
					property alias hits : left_participart_hits.value
					property alias forfeits : left_participart_fts.value

					width : (top_layout.width - side_holder.width - middle_separator.width - parent.spacing * 3) / 2
					spacing: 5

					Row { id: left_participant_info_layout
						spacing : 5

						Image { id: left_participant_image
							height: 30
							width: height;
							source: "data/pics/teams/" + left_team + ".png"
							//source: "data/pics/team.png"

							Text { id: left_participart_team
								opacity: 0
								text: left_team
							}
						}

						Rectangle { id: left_participart_text_area
							height: left_participant_image.height
							width: left_participart.width - left_participant_image.width - parent.spacing
							border.color: "gray"
							Text { 	id: left_participart_nick_name
								anchors.fill: parent
								text: (left_name !== "")? left_name : left_firstname + " " +left_surname
								font.bold: true; font.pointSize: 10
								horizontalAlignment: Text.AlignLeft
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}
					}

					Row { id: left_participant_hits_layout
						spacing : 5

						Rectangle {	id: left_participant_score_area
							height: left_participart_hits.height;
							width: 30
							border.color: "gray"
							Text { id: left_participart_score
								text: left_score
								anchors.fill: parent
								font.pointSize: 10
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}

						SpinButtons { id: left_participart_hits
							opacity: item.hits_opacity
							width : left_participart.width - left_participant_score_area.width - parent.spacing
							border.color: "gray"
						}

						Rectangle { id: left_participant_stats_area
							opacity: 1 - item.hits_opacity
							width : left_participart.width - left_participant_score_area.width - parent.spacing
							height: left_participart_hits.height
							border.color: "red"

							Text { id: left_participart_stats
								text: left_hits + " / (" + left_forfeits + ")"
								anchors.fill: parent
								font.pointSize: 10
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}
					}

					Row { id: left_participant_fts_layout
						spacing : 5

						Rectangle { id: left_participant_fts_area
							opacity: item.details_opacity
							height: left_participart_fts.height;
							width: 30
							border.color: "gray"

							Text { id: left_participart_forfeits
								text: left_forfeits
								anchors.fill: parent
								font.pointSize: 10
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}

						SpinButtons { id : left_participart_fts
							opacity: item.details_opacity
							width : left_participart.width - left_participant_fts_area.width - parent.spacing
							border.color: "gray"
						}
					}

					Row { id: left_participant_buttons_layout
						spacing: 25
						anchors.right: parent.right

						TextButton { text: "Wins"
							opacity: item.details_opacity
							width: 50
							height: 30
							onClicked: {
								item.left_wins = true;
								item.state = "wins";
							}
						}

						TextButton { text: "Kick"
							opacity: item.details_opacity
							width: 50
							height: 30
							onClicked: {
								item.left_wins = false;
								item.state = "forfeits"
							}
						}
					}
				}

				Column { id: middle_separator
					width: 30; spacing: 5

					Rectangle { // middle_separator_vs
						id: middle_separator_vs
						width: parent.width;
						height: left_participant_image.height;
						radius: 5
						border.color: "gray"

						Text { // status_lable
							id : status_lable
							anchors.fill: parent
							text: "VS"
							font.bold: true; font.pointSize: 10
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}

					Rectangle { // middle_separator_hits
						id: middle_separator_hits
						width: parent.width;
						height: left_participart_hits.height;
						radius: 5
						border.color: "gray"

						Text { // Hits
							anchors.fill: parent
							text: "Hits"
							font.pointSize: 10
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}

					Rectangle { // middle_separator_fts
						id: middle_separator_fts
						width: parent.width;
						opacity: item.details_opacity
						height: left_participart_fts.height;
						radius: 5
						border.color: "gray"

						Text { // Fts
							anchors.fill: parent
							text: "Fts"
							font.pointSize: 10
							horizontalAlignment: Text.AlignHCenter
							verticalAlignment: Text.AlignVCenter
						}
					}

					TextButton { // Tie
						opacity: item.details_opacity
						text: "Tie"
						width: parent.width
						height: 30
						onClicked: item.state = "ties"
					}
				}

				Column { id: right_participart

					property alias name : right_participart_nick_name.text
					property alias team : right_participart_team.text
					property alias hits : right_participart_hits.value
					property alias forfeits : right_participart_fts.value

					width : (top_layout.width - side_holder.width - middle_separator.width - parent.spacing * 3) / 2
					spacing: 5

					Row { id: right_participant_info_layout
						spacing : 5

						Rectangle { id: right_participant_text_area
							height: right_participant_image.height
							width: right_participart.width - right_participant_image.width - parent.spacing
							border.color: "gray"
							Text { id: right_participart_nick_name
								anchors.fill: parent
								text: (right_name !== "")? right_name : right_firstname + " " + right_surname
								font.bold: true; font.pointSize: 10
								horizontalAlignment: Text.AlignRight
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}

						Image { id: right_participant_image
							width: 30;
							height: 30
							source: "data/pics/teams/" + right_team + ".png"
							//source: "data/pics/team.png"

							Text { id: right_participart_team
								opacity: 0
								text: right_team
							}
						}
					}

					Row { id: right_participant_hits_layout
						spacing : 5

						Rectangle { id: right_participant_stats_area
							opacity: 1 - item.hits_opacity
							width : right_participart.width - right_participant_score_area.width - parent.spacing
							border.color: "red"
							height: right_participart_hits.height

							Text { id: right_participart_stats
								text: right_hits + " / (" + right_forfeits + ")"
								anchors.fill: parent
								font.pointSize: 10
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}

						SpinButtons { id: right_participart_hits
							opacity: item.hits_opacity
							width : right_participart.width - right_participant_score_area.width - parent.spacing
							border.color: "gray"
						}

						Rectangle { id: right_participant_score_area
							height: right_participart_hits.height;
							width: 30
							border.color: "gray"

							Text { id: right_participart_score
								text: right_score
								anchors.fill: parent
								font.pointSize: 10
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}
					}

					Row { id: right_participant_fts_layout
						spacing : 5

						SpinButtons { id: right_participart_fts
							opacity: item.details_opacity
							width : right_participart.width - right_participant_fts_area.width - parent.spacing
							border.color: "gray"
						}

						Rectangle { id: right_participant_fts_area
							opacity: item.details_opacity
							height: right_participart_fts.height;
							width: 30
							border.color: "gray"

							Text { id: right_participart_forfeits
								text: right_forfeits
								anchors.fill: parent
								font.pointSize: 10
								horizontalAlignment: Text.AlignHCenter
								verticalAlignment: Text.AlignVCenter
								wrapMode: Text.WordWrap
							}
						}
					}

					Row { id: right_participant_buttons_layout
						spacing: 25

						TextButton { text: "Kick"
							opacity: item.details_opacity
							width: 50
							height: 30
							onClicked: {
								item.left_wins = true;
								item.state = "forfeits"
							}
						}

						TextButton { text: "Wins"
							opacity: item.details_opacity
							width: 50
							height: 30
							onClicked: {
								item.left_wins = false;
								item.state = "wins"
							}
						}
					}
				}
			}

			Row { id: horizontal_separator
				opacity: item.details_opacity
				width: parent.width;
				height: top_layout.height - controls_section.height - status_bar.height
			}

			Rectangle { id: status_bar
				width: parent.width; height: 15; radius: 5
				border.color: "gray"

				Text { text: status
					anchors.fill: parent
					font.pointSize: 10
					verticalAlignment: Text.AlignVCenter
					wrapMode: Text.WordWrap
				}
			}
		}

		states: [
			  State { name: "fighting"

				PropertyChanges { target: item; details_opacity: 1; x: 0 } // Make details visible
				PropertyChanges { target: item; height: listView.height } // Fill the entire list area with the detailed view

				// Move the list so that this item is at the top.
				PropertyChanges { target: item.ListView.view; explicit: true; contentY: item.y }

				// Disallow flicking while we're in detailed view
				PropertyChanges { target: item.ListView.view; interactive: false }
			}

			, State { name: "wins"
				PropertyChanges { target: more_less_button; opacity : 0 }
				PropertyChanges { target: status_lable; text : "Wins" }
				PropertyChanges { target: item; hits_opacity : 0; duel_is_over : true }
				StateChangeScript { name: "update_model"; script: item.update_model_from_state("wins"); }
			}

			, State { name: "forfeits"
				PropertyChanges { target: more_less_button; opacity : 0 }
				PropertyChanges { target: status_lable; text : "Fts" }
				PropertyChanges { target: item; hits_opacity : 0; duel_is_over : true }
				StateChangeScript { name: "update_model"; script: item.update_model_from_state("forfeits"); }
			}

			, State { name: "ties"
				PropertyChanges { target: more_less_button; opacity : 0 }
				PropertyChanges { target: status_lable; text : "Ties" }
				PropertyChanges { target: item; hits_opacity : 0; duel_is_over : true }
				StateChangeScript { name: "update_model"; script: item.update_model_from_state("ties"); }
			}
		]

		transitions: [

			Transition { // Make the state changes smooth

				ParallelAnimation {

					ColorAnimation { property: "color"
						duration: 300
					}

					NumberAnimation { properties: "details_opacity,x,contentY,height,width"
						duration: 300
					}
				}
			}
			, Transition { from : "fighting"; to: "ties"
				SequentialAnimation { ScriptAction { scriptName: "update_model" } }
			}
			, Transition { from : "fighting"; to: "wins"
				SequentialAnimation { ScriptAction { scriptName: "update_model" } }
			}
			, Transition { from : "fighting"; to: "forfeits"
				SequentialAnimation { ScriptAction { scriptName: "update_model" } }
			}
		]
	}
}
