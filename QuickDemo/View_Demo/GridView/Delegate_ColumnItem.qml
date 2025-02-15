﻿import QtQuick 2.0
import QtQuick.Controls 1.2
Delegate_Abstract {
    id: id_root
    scrollMargin: 5
    property var itemModel
    property string monthId:""
    property string itemId: id_root.itemModel.videoInfo
    property string itemTitle:id_root.itemModel.videoTitle
    property string currentPlayItemId

    property alias checkedForPlaying: id_playingChecked.checked

    onCheckedForPlayingChanged: {
        console.log("-----------is---- checkedForPlaying----------" + checkedForPlaying)
        console.log("-------------- itemTitle---------" + id_root.itemTitle)
        if(checkedForPlaying){
            id_root.checked = checkedForPlaying;
        }
    }

    property ExclusiveGroup exclusiveGroupForPlaying: null

    hoverBackColor: "yellow"
    checkedBackColor:"yellow"

    Component.onCompleted: {
        console.log("id_root.itemModel.videoInfo = " + id_root.itemModel.videoInfo)
    }


    MouseArea{
        anchors.fill: parent
        anchors.rightMargin: id_root.scrollMargin
        Rectangle{
            id: id_playing_rect
            anchors.fill: parent
            color:"black"
            visible: true

            XmsCheckedItem{
                id: id_playingChecked
                exclusiveGroup: id_root.exclusiveGroupForPlaying
            }
        }

//        XmsIcon{
//            text:UI.ICON_PLAYER_PLAY
//            size: 15
//            anchors.left: parent.left
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.leftMargin: 4
//            visible: id_root.checkedForPlaying
//            color:"yellow"
//            tooltip: qsTr("播放中")
//        }

        XmsText{
            text:id_root.itemTitle
            anchors.left: parent.left
            anchors.leftMargin: 23
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            elide: Text.ElideRight
            color:"yellow"

        }
    }

}

