﻿import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
    id: id_root
    signal emitDoubleClick
    signal emitDetailClick
    signal emitDeleteClick
    signal emitPressAndHold
    signal emitClick
    signal emitCheckClick
    implicitWidth: 200
    implicitHeight: 200

    property Loader dlgLoader: null
    property string itemParentId:""
    property int itemId:-1
    property int indexNum:-1
    property var modelData:null

    property int scrollMargin:5

    property int currentSelectedId:-1
    property real __selectOpacity:0.7

    property alias isHovered:id_hoverBg.visible
    property alias isPressed: id_pressBg.visible
    property alias isChecked: id_checkedBg.visible
    default property alias content:id_content.children
    property alias hoverBackColor: id_hoverBg.color
    property alias normalBackColor: id_normalBg.color
    property alias pressedBackColor: id_pressBg.color
    property alias checkedBackColor: id_checkedBg.color

    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null
    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(id_root)
    }
    onCheckedChanged: {
        if(id_root.checked) emitCheckClick()
    }

    Item{
        anchors.fill: parent
        anchors.rightMargin: id_root.scrollMargin
        Rectangle{
            id: id_normalBg
            anchors.fill: parent
            color:"white"
        }
        Rectangle{
            id: id_hoverBg
            anchors.fill: parent
            visible: false
            color:UI.color_app_tree_item_hover

        }
        Rectangle{
            id: id_pressBg
            anchors.fill: parent
            visible: false
            color:"#D9E9F1"

        }
        Rectangle{
            id: id_checkedBg
            anchors.fill: parent
            visible: id_root.checked
            color:"yellow"
            opacity: __selectOpacity
        }


    }

    MouseArea{
        id: id_mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor
        enabled: id_root.enabled
        onClicked: {
            //id_root.checked = true
            emitClick()
        }
        onEntered: {
            id_hoverBg.visible = true
            __selectOpacity = 1
        }

        onExited: {
            id_hoverBg.visible = false
            __selectOpacity =0.7
        }
        onPressed: id_pressBg.visible = true
        onReleased: id_pressBg.visible = false
        onDoubleClicked: {
            id_root.checked = true
            emitDoubleClick()
        }

        Item{
            id: id_content
            anchors.fill: parent
        }
    }
}

