/***/

import Qt 4.7
import "search.js" as Search

Item {
    id: adaptivepanel

    height: buttongrid.height > controlbuttons.height ? buttongrid.height : controlbuttons.height

    signal filterUpdated()

    property int buttonWidth: width / 10 - buttongrid.spacing
    property int buttonHeight: buttonWidth
    property int buttonMargin: 1

    Column {
        id: controlbuttons
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: buttonMargin

        PanelButton {
            id: backButton
            width: buttonWidth
            height: buttonHeight

            // Show back button only when going back is possible (i.e filter length > 0)
            opacity: filter.length > 0 ? 1 : 0

            onClicked: {
                filter = filter.substring(0, filter.length-1)
                Search.fillFilterModel()
                //Search.updateFilterModel()
                filterUpdated()
            }

            Image {
                source: "gfx/left.png"
                anchors.centerIn: parent
            }

            Behavior on opacity { NumberAnimation { duration: 500 }}
        }
    }
}
