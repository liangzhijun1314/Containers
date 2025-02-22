import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Rectangle {
    width: 300;
    height: 400;
    color: "white";

    ListModel {
        id: appModel;
        ListElement { name: "AddressBook"; icon:"images/AddressBook_48.png"}
        ListElement { name: "AudioPlayer"; icon:"images/AudioPlayer_48.png"}
        ListElement { name: "Camera"; icon:"images/Camera_48.png"}
        ListElement { name: "DateBook"; icon:"images/DateBook_48.png"}
        ListElement { name: "EMail"; icon:"images/EMail_48.png"}
        ListElement { name: "TodoList"; icon:"images/TodoList_48.png"}
        ListElement { name: "VideoPlayer"; icon:"images/VideoPlayer_48.png"}
    }

    GridView {
        id:view
        anchors.fill: parent;
        cellWidth: 100;
        cellHeight: 100;
        focus: true;
        model: appModel;
        highlight: Rectangle { width: 80; height: 80; color: "lightsteelblue"}


        delegate: Item {
            width: 100;
            height: 100;


            Column {
                anchors.horizontalCenter: parent.horizontalCenter;
                anchors.verticalCenter: parent.verticalCenter;
                Image {
                    id: myIcon;
                    width:50;
                    height: 50;
//                    anchors.horizontalCenter: parent.horizontalCenter;
//                    anchors.verticalCenter: parent.verticalCenter;
                    fillMode: Image.PreserveAspectFit
                    source: icon;
                }

                Text {
                    text: name;
                    anchors.horizontalCenter: parent.horizontalCenter
//                    anchors.top:myIcon.bottom
                    color:"black"
                    //                anchors {top: myIcon.bottom; horizontalCenter: parent.horizontalCenter+10}
                }
                CheckBox {
                    id: checkBox
                    width: 100;
                    height: 30;
                    text:name;
                    checked: myChecked;
                }
            }
            MouseArea {
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor   //此区域的鼠标光标形状
                onClicked: parent.GridView.view.currentIndex = index;

            }
        }
    }



//    Component {
//        id: highlight
//        Rectangle {
//            width: view.cellWidth; height: view.cellHeight
//            color: "lightsteelblue"; radius: 5
//            x: view.currentItem.x
//            y: view.currentItem.y
//            Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
//            Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
//        }
//    }

//    GridView {
//        id: view
//        width: 300; height: 400
//        cellWidth: 100; cellHeight: 100

//        model: appModel
//        delegate: Column {
//            Image { source: icon; anchors.horizontalCenter: parent.horizontalCenter }
//            Text { text: name; anchors.horizontalCenter: parent.horizontalCenter }
//        }

//        highlight: highlight
//        highlightFollowsCurrentItem: false
//        focus: true
//    }

}
