import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.3 //使用StackView必须引入

/*
* https://blog.csdn.net/foruok/article/details/46839569
*/

Window {
    visible: true
    width: 480
    height: 320
    title: qsTr("StackViewDemo")

    StackView {
        id: stack
        anchors.centerIn: parent
        width: 480; height: 330
        property var home: null;
        Text {
            text: "Click to create first page";
            font.pointSize: 14;
            font.bold: true;
            color: "blue";
            anchors.centerIn: parent;
            MouseArea {
                anchors.fill: parent;
                onClicked: if(stack.depth == 0)stack.push(page);
            }
        }
    }

    Component {
        id: page;
        Rectangle {
            color: Qt.rgba(stack.depth*0.1, stack.depth *0.2,stack.depth*0.3);
            Text {
                anchors.centerIn: parent;
                text: "depth - " + stack.depth;
                font.pointSize: 24;
                font.bold: true;
                color: stack.depth <= 4 ? Qt.lighter(parent.color) : Qt.darker(parent.color);
            }

            Button {
                id: next;
                text: "Next";
                width: 70; height: 30;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;
                anchors.margins: 8;
                onClicked: {
                    if (stack.depth < 8)
                        stack.push(page);
                }
            }

            Button {
                id: back;
                text: "Back";
                width: 70; height: 30;
                anchors.right: next.left;
                anchors.top: next.top;
                anchors.rightMargin: 8;
                onClicked: {
                    if (stack.depth > 0)
                        stack.pop();
                }
            }

            Button {
                id: home;
                text: "Home";
                width: 70; height: 30;
                anchors.right: back.left;
                anchors.top: next.top;
                anchors.rightMargin: 8;
                onClicked: {
                    if (stack.depth > 0)
                        stack.pop(stack.initialItem);
                }
            }

            Button {
                id: clear;
                text: "Clear";
                width: 70; height: 30;
                anchors.right: home.left;
                anchors.top: next.top;
                anchors.rightMargin: 8;
                onClicked: {
                    if (stack.depth > 0)
                        stack.clear();
                }
            }
        }
    }
}
