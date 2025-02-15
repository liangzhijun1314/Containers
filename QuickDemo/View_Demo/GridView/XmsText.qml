﻿import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.1

Text{
    id: id_root
    property int size:6
    property string tooltip:text
    property bool defaultFont:true
    property bool isMouseEnable:true
    property alias cursorShape:id_mouseArea.cursorShape
    property string fontdefine: id_font.name
    property alias effectivePressed:id_mouseArea.containsMouse
    font.family: fontdefine
    font.pixelSize: size
    elide: Text.ElideRight
    color:"black"

    FontTextLoader{
        id: id_font
    }

    signal emitClick()
    signal emitPressed()
    signal emitReleased()
    signal emitExited()
    signal emitEntered()
    signal emitDoubleClick()

    MouseArea {
        id: id_mouseArea
//        property bool keyPressed: false
//        property bool effectivePressed: pressed && containsMouse || keyPressed
        visible:  isMouseEnable
        anchors.fill: parent
        hoverEnabled: true
        onExited: {
            Tooltip.hideText()
            id_root.emitExited()
        }
        onEntered: {
            id_root.emitEntered()
        }
        onDoubleClicked: {
            id_root.emitDoubleClick()
        }

        onCanceled: Tooltip.hideText()
        Timer {
            interval: 1000
            running: id_mouseArea.containsMouse && tooltip.length
            onTriggered: Tooltip.showText(id_mouseArea, Qt.point(id_mouseArea.mouseX, id_mouseArea.mouseY), tooltip)
        }
        onPressed: {
            id_root.emitPressed()

        }

        onReleased: {
            id_root.emitReleased()

        }

        onClicked: {
            id_root.emitClick()
        }
    }
}
