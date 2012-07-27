/***/
import QtQuick 1.0
import "controls"

Rectangle {	id: main_page
	width: 1000
 	height: 800
	color: "black"

	Rectangle { id: overview_area
		color: "blue"
		border.width: 2
		border.color: "darkgray"
		anchors.left: slide_pannel.right
		anchors.right: parent.right
		anchors.top: upper_tool_bar.bottom
		anchors.bottom: status_bar.top
	}
	
	SlidePannel { id: slide_pannel
		anchors.left: main_tool_bar.right
		anchors.top: upper_tool_bar.bottom
		anchors.bottom: status_bar.top

		ParticipantsList { id: participants_list
			hide_state : 'Reg'
			anchors.fill: parent
			opacity: 0
		}

		ParticipantsList { id: registered_list
			hide_state : 'Add'
			anchors.fill: parent
			opacity: 0
		}

		PairsList { id: pairs_list
			anchors.fill: parent
			opacity: 0
			active : rounds_list.current_round_state == "opened" ? true : false
			onFormPairs : {
				if (rounds_list.current_round_name != "") {
					if (duels.current_round_state != "finished"){
						registration.form_pairs(rounds_list.current_round_name,"round_options");
					}
				}
			}
		}
	}

	Rectangle {	id: upper_tool_bar
		height: 40
		color: "darkgray"
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		
		Image {
			anchors.fill: parent
			source: "data/pics/toolbaritem.png"
		}
		
		Row { id: upper_tool_bar_layout
			spacing: 5
			anchors.margins: 5
			anchors.fill : parent
			
			ImageButton { id : register
				z: 1
				image_source: "data/pics/register.png"
				onClicked:	  main_page.state == 'registration'
							? main_page.state = ""
							: main_page.state = 'registration'
			}

			RoundsList { id: rounds_list
				color: "transparent"
				width : upper_tool_bar.width - register.width - upper_tool_bar_layout.spacing - upper_tool_bar_layout.anchors.margins*2
			}
		}
	}	
		
	Rectangle { id: main_tool_bar
		color: "darkgray"
		width: 40
		anchors.left: parent.left
		anchors.top: upper_tool_bar.bottom
		anchors.bottom: status_bar.top

		Image {
			anchors.fill: parent
			source: "data/pics/toolbaritem_h.png"
		}

		Flow {
			spacing: 5
			anchors.margins: 5
			anchors.fill : parent
			
			ImageButton {
				id : participants_button
				image_source: "data/pics/participant.png"
				onClicked:	  main_page.state == 'participants'
							? main_page.state = ""
							: main_page.state = 'participants'
			}
			ImageButton {
				id: duels_button
				image_source: "data/pics/duel.png"
				onClicked:	  main_page.state == 'duels'
							? main_page.state = ""
							: main_page.state = 'duels'
			}
			ImageButton {
				id : teams_button
				image_source: "data/pics/team.png"
				onClicked:	  main_page.state == 'teams'
							? main_page.state = ""
							: main_page.state = 'teams'
			}
			ImageButton {
				image_source: "data/pics/load.png"
				onClicked:	  main_page.state == 'load'
							? main_page.state = ""
							: main_page.state = 'load'
			}
			ImageButton {
				image_source: "data/pics/setup.png"
				onClicked:	  main_page.state == 'setup'
							? main_page.state = ""
							: main_page.state = 'setup'
			}
			ImageButton {
				id : log
				image_source: "data/pics/log.png"
				onClicked:	  main_page.state == 'log'
							? main_page.state = ""
							: main_page.state = 'log'
			}
			ImageButton {
				id : close
				image_source: "data/pics/exit.png"
				onClicked: Qt.quit();
			}
		}
	}

	Rectangle 
	{
		height: 20
		id: status_bar
		color: "darkgray"
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		
		Image {
			anchors.fill: parent
			source: "data/pics/toolbaritem.png"
		}

		Flow 
		{
			spacing: 5
			anchors.margins: 5
			anchors.fill : parent
		}
	}

	states {
		State {
			name: "registration"
			PropertyChanges { target: slide_pannel; state: "opened" }
			PropertyChanges { target: participants_list; opacity: 1 }
			PropertyChanges { target: registered_list; opacity: 0 }
			PropertyChanges { target: pairs_list; opacity: 0 }
		}

		State {
			name: "participants"
			PropertyChanges { target: slide_pannel; state: "opened" }
			PropertyChanges { target: participants_list; opacity: 0 }
			PropertyChanges { target: registered_list; opacity: 1 }
			PropertyChanges { target: pairs_list; opacity: 0 }
		}

		State {
			name: "duels"
			PropertyChanges { target: slide_pannel; state: "opened" }
			PropertyChanges { target: participants_list; opacity: 0 }
			PropertyChanges { target: registered_list; opacity: 0 }
			PropertyChanges { target: pairs_list; opacity: 1 }
		}
	}

	transitions {
		Transition {
			PropertyAnimation {
				properties: "width,x,y,opacity"
				duration: 300;
			}
		}
	}
}
