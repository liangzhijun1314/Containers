import QtQuick 2.6
import QtQuick.Window 2.2

Rectangle {
    width: 400; height: 240;
    color: "white"

    ListModel {
        id: appModel
        ListElement { name: "Music"; icon: "images/AudioPlayer_48.png" }
        ListElement { name: "Movies"; icon: "images/VideoPlayer_48.png" }
        ListElement { name: "Camera"; icon: "images/Camera_48.png" }
        ListElement { name: "Calendar"; icon: "images/DateBook_48.png" }
        ListElement { name: "Messaging"; icon: "images/EMail_48.png" }
        ListElement { name: "Todo List"; icon: "images/TodoList_48.png" }
        ListElement { name: "Contacts"; icon: "images/AddressBook_48.png" }
    }

    Component {
        id: appDelegate
        Item {
            width: 100; height: 100
            scale: PathView.iconScale

             Image {
                id: myIcon
                y: 20; anchors.horizontalCenter: parent.horizontalCenter
                source: icon
             }

             Text {
                anchors { top:myIcon.bottom; horizontalCenter: parent.horizontalCenter }
                text: name
             }

             MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
             }
        }
    }

    Component {
        id: appHighlight
        Rectangle { width: 80; height: 80; color: "lightsteelblue" }
    }

    PathView {
        id: view
        anchors.fill: parent
        highlight: appHighlight
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        model: appModel
        delegate: appDelegate

        path: Path {
            startX: 10
            startY: 50
            PathAttribute { name: "iconScale"; value: 0.5 }
            PathQuad { x: 200; y: 150; controlX: 50; controlY: 200 }
            PathAttribute { name: "iconScale"; value: 1.0 }
            PathQuad { x: 390; y: 50; controlX: 350; controlY: 200 }
            PathAttribute { name: "iconScale"; value: 0.5 }
        }
    }
}
