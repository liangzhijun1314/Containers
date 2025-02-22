import QtQuick 2.5
import QtQuick.Window 2.2

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Hello World")

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            Qt.quit();
//        }
//    }

//    Text {
//        text: qsTr("Hello World")
//        anchors.centerIn: parent
//    }
//}



import QtQuick 2.5
import Qt.labs.controls 1.0

ApplicationWindow { id: root
    visible: true
    width: 840
    height: 680
    title: qsTr("Hello World")

    Button{ id: btn
        anchors.centerIn: parent
        text: "click"
        onClicked: {
            modelDlg.open()
            modelDlg.x = parent.width/2 - modelDlg.width/2
            modelDlg.y = parent.height/2 - modelDlg.height/2
        }
    }
    ModelDialog{
        id: modelDlg
    }
}
