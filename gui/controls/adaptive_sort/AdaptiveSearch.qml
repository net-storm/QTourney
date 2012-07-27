/***/
import Qt 4.7
import "search.js" as Search

Item {
    id: adaptiveroot

    // Source model for data
    property QtObject model: undefined
    property QtObject fullModel

    signal filterUpdated()
    signal aboutToShow()
    signal show()
    signal hide()

    property int buttonWidth
    property int buttonHeight

    property QtObject filtermodel: ListModel {}
    property variant uniqueChars: undefined
    property string filter: ""

    state: "minimized"

    Component.onCompleted: {
        fullModel = model
    }

    // Search button for minimized-state
    Image {
        id: searchicon
        source: searchiconarea.pressed ? "gfx/search_pressed.png" : "gfx/search.png"

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        // Indicator that is shown when filter is set and search panel is closed
        Image {
            source: "gfx/filterset.png"
            opacity: filter.length > 0 ? 1 : 0
        }

        MouseArea {
            id: searchiconarea
            anchors.fill: parent
            onClicked: {
                aboutToShow()
                uniqueChars = new Array();
                Search.fillFilterModel()
                Search.updateFilterModel()
                adaptiveroot.state = "maximized"
                show()
            }
        }
    }
}
