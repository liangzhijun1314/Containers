import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
Rectangle {
//    width: 300;
//    height: 500;
    color: "white";

    Item{
        ExclusiveGroup{
            id: id_pagePlayInfo_group
        }
    }

    Column{
        width: parent.width
        spacing: 10
        Item{
            width: 1
            height: 10
        }

        Item{
            id: id_programeBT_2
            anchors.left: parent.left
            anchors.right: parent.right
            implicitHeight:25
            Rectangle{
                color:"#009ce4"
                anchors.fill: parent
                anchors.rightMargin: 18
                opacity: id_mouseArea.containsMouse ? 0.8:1
            }


            XmsText{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -12
                color:"#FFFFFF"
                text:qsTr("节目单22222222222222")
                tooltip: qsTr("节目单")

            }

            XmsIcon{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 26
                tooltip: qsTr("节目单")
                size: 16
                text:"\u00e4"
                color:"#FFFFFF"
            }

            MouseArea{
                id: id_mouseArea_2
                hoverEnabled: true
                cursorShape:  Qt.PointingHandCursor
                anchors.fill: parent
                onClicked:{
                    console.debug("显示节目单------")
                    var t_obj ={
                        "itemId": id_root._channelId,
                        "itemUrl": id_root._channelUrl,
                        "itemName": id_root._programTitle
                    }
                    console.log("id_root._channelId = " + id_root._channelId)
                    console.log("id_root._channelUrl = " + id_root._channelUrl)
                    console.log("id_root._programTitle = " + id_root._programTitle)

                }
            }
        }


        // 多视角使用组件
        Column{
            id: id_mult_col

            anchors.left: parent.left
            anchors.right: parent.right
//            width:parent.width
            spacing: 15
            ExclusiveGroup{
                id: id_multList_group
            }

            ListModel{
                id: id_multLiveModel

                Component.onCompleted: {
                    console.log("========add ===========mutltiLiveData =")

                    var t_multListObj =[]
                    t_multListObj = [{"videoCid":"","videoId":"cctv1","videoIndex":1,"videoInfo":"CCTV-1 综合","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228152123_350.png","videoTitle":"CCTV-1 综合","videoUrl":"pa:\/\/cctv_p2p_hdcctv1","videoVsid":"cctv1"},{"videoCid":"","videoId":"cctv2","videoIndex":2,"videoInfo":"CCTV-2 财经","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228157827_739.png","videoTitle":"CCTV-2 财经","videoUrl":"pa:\/\/cctv_p2p_hdcctv2","videoVsid":"cctv2"},{"videoCid":"","videoId":"cctv3","videoIndex":3,"videoInfo":"CCTV-3 综艺","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228164442_566.png","videoTitle":"CCTV-3 综艺","videoUrl":"pa:\/\/cctv_p2p_hdcctv3","videoVsid":"cctv3"},{"videoCid":"","videoId":"cctv4","videoIndex":4,"videoInfo":"CCTV-4 中文国际(亚)","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228170546_750.png","videoTitle":"CCTV-4 中文国际(亚)","videoUrl":"pa:\/\/cctv_p2p_hdcctv4","videoVsid":"cctv4"},{"videoCid":"","videoId":"cctveurope","videoIndex":5,"videoInfo":"CCTV-4 中文国际(欧)","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228180692_22.png","videoTitle":"CCTV-4 中文国际(欧)","videoUrl":"pa:\/\/cctv_p2p_hdcctveurope","videoVsid":"cctveurope"},{"videoCid":"","videoId":"cctvamerica","videoIndex":6,"videoInfo":"CCTV-4 中文国际(美)","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228192813_77.png","videoTitle":"CCTV-4 中文国际(美)","videoUrl":"pa:\/\/cctv_p2p_hdcctvamerica","videoVsid":"cctvamerica"},{"videoCid":"","videoId":"cctv5","videoIndex":7,"videoInfo":"CCTV-5 体育","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228199737_256.png","videoTitle":"CCTV-5 体育","videoUrl":"pa:\/\/cctv_p2p_hdcctv5","videoVsid":"cctv5"},{"videoCid":"","videoId":"cctv6","videoIndex":8,"videoInfo":"CCTV-6 电影","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228218702_0.png","videoTitle":"CCTV-6 电影","videoUrl":"pa:\/\/cctv_p2p_hdcctv6","videoVsid":"cctv6"},{"videoCid":"","videoId":"cctv7","videoIndex":9,"videoInfo":"CCTV-7 军事农业","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228224349_953.png","videoTitle":"CCTV-7 军事农业","videoUrl":"pa:\/\/cctv_p2p_hdcctv7","videoVsid":"cctv7"},{"videoCid":"","videoId":"cctv8","videoIndex":10,"videoInfo":"CCTV-8 电视剧","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228230684_491.png","videoTitle":"CCTV-8 电视剧","videoUrl":"pa:\/\/cctv_p2p_hdcctv8","videoVsid":"cctv8"},{"videoCid":"","videoId":"cctvjilu","videoIndex":11,"videoInfo":"CCTV-9 纪录","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228236766_299.png","videoTitle":"CCTV-9 纪录","videoUrl":"pa:\/\/cctv_p2p_hdcctvjilu","videoVsid":"cctvjilu"},{"videoCid":"","videoId":"cctvdoc","videoIndex":12,"videoInfo":"CCTV-9 纪录(英语)","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV-9 纪录(英语)","videoUrl":"pa:\/\/cctv_p2p_hdcctvdoc","videoVsid":"cctvdoc"},{"videoCid":"","videoId":"cctv10","videoIndex":13,"videoInfo":"CCTV-10 科教","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228247340_186.png","videoTitle":"CCTV-10 科教","videoUrl":"pa:\/\/cctv_p2p_hdcctv10","videoVsid":"cctv10"},{"videoCid":"","videoId":"cctv11","videoIndex":14,"videoInfo":"CCTV-11 戏曲","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228252579_49.png","videoTitle":"CCTV-11 戏曲","videoUrl":"pa:\/\/cctv_p2p_hdcctv11","videoVsid":"cctv11"},{"videoCid":"","videoId":"cctv12","videoIndex":15,"videoInfo":"CCTV-12 社会与法","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228717965_817.png","videoTitle":"CCTV-12 社会与法","videoUrl":"pa:\/\/cctv_p2p_hdcctv12","videoVsid":"cctv12"},{"videoCid":"","videoId":"cctv13","videoIndex":16,"videoInfo":"CCTV-13 新闻","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386230110212_471.png","videoTitle":"CCTV-13 新闻","videoUrl":"pa:\/\/cctv_p2p_hdcctv13","videoVsid":"cctv13"},{"videoCid":"","videoId":"cctvchild","videoIndex":17,"videoInfo":"CCTV-14 少儿","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386230442948_16.png","videoTitle":"CCTV-14 少儿","videoUrl":"pa:\/\/cctv_p2p_hdcctvchild","videoVsid":"cctvchild"},{"videoCid":"","videoId":"cctv15","videoIndex":18,"videoInfo":"CCTV-15 音乐","videoPosition":9,"videoSnapImg":"http:\/\/p1.img.cctvpic.com\/photoAlbum\/page\/performance\/img\/2013\/12\/5\/1386228606639_885.png","videoTitle":"CCTV-15 音乐","videoUrl":"pa:\/\/cctv_p2p_hdcctv15","videoVsid":"cctv15"},{"videoCid":"","videoId":"cctv9","videoIndex":19,"videoInfo":"CCTV-News","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV-News","videoUrl":"pa:\/\/cctv_p2p_hdcctv9","videoVsid":"cctv9"},{"videoCid":"","videoId":"cctvxiyu","videoIndex":20,"videoInfo":"CCTV-西语","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV-西语","videoUrl":"pa:\/\/cctv_p2p_hdcctvxiyu","videoVsid":"cctvxiyu"},{"videoCid":"","videoId":"cctvfrench","videoIndex":21,"videoInfo":"CCTV-法语","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV-法语","videoUrl":"pa:\/\/cctv_p2p_hdcctvfrench","videoVsid":"cctvfrench"},{"videoCid":"","videoId":"cctvarabic","videoIndex":22,"videoInfo":"CCTV-阿语","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV-阿语","videoUrl":"pa:\/\/cctv_p2p_hdcctvarabic","videoVsid":"cctvarabic"},{"videoCid":"","videoId":"cctvrussian","videoIndex":23,"videoInfo":"CCTV-俄语","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV-俄语","videoUrl":"pa:\/\/cctv_p2p_hdcctvrussian","videoVsid":"cctvrussian"},{"videoCid":"","videoId":"cctv5plus","videoIndex":24,"videoInfo":"CCTV5+ 体育赛事","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV5+ 体育赛事","videoUrl":"pa:\/\/cctv_p2p_hdcctv5plus","videoVsid":"cctv5plus"},{"videoCid":"","videoId":"zhongxuesheng","videoIndex":25,"videoInfo":"CCTV 中学生","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV 中学生","videoUrl":"pa:\/\/cctv_p2p_hdzhongxuesheng","videoVsid":"zhongxuesheng"},{"videoCid":"","videoId":"xinkedongman","videoIndex":26,"videoInfo":"CCTV 新科动漫","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV 新科动漫","videoUrl":"pa:\/\/cctv_p2p_hdxinkedongman","videoVsid":"xinkedongman"},{"videoCid":"","videoId":"zhinan","videoIndex":27,"videoInfo":"CCTV 电视指南","videoPosition":9,"videoSnapImg":"","videoTitle":"CCTV 电视指南","videoUrl":"pa:\/\/cctv_p2p_hdzhinan","videoVsid":"zhinan"}]
                    console.log("-------------------t_multListObj = " + t_multListObj)

                    id_multLiveModel.append(t_multListObj)
                    console.log("---------id_itemList_repeater.count = " + id_itemList_repeater.count)
                }
            }

            Repeater{
                id: id_itemList_repeater
                model: id_multLiveModel
//                Text{
//                    text:id_multLiveModel.get(index).videoInfo
//                }

//                XmsText{
//                    text:id_multLiveModel.get(index).videoInfo
//                }

                Delegate_ColumnItem{
//                    height: 25
//                    width:100
//                    itemModel:id_multLiveModel.get(index)


                    id:id_columnItem
                    height: 25
                    anchors.left: parent.left
                    anchors.right: parent.right
                    //currentPlayItemId: id_root.currentPlayMediaId
                    //checked: id_root.currentPlayMediaId === itemId ? true: false
                    anchors.rightMargin: 3
                    exclusiveGroupForPlaying: id_pagePlayInfo_group //id_itemGroup
                    exclusiveGroup: id_multList_group
                    itemModel: id_multLiveModel.get(index)
                    onEmitDoubleClick:{
                        id_root.currentPlayMediaId = itemId
                    }
                }

            }
        }

        Item{
            id: id_programeBT
            anchors.left: parent.left
            anchors.right: parent.right
            implicitHeight:25
            Rectangle{
                color:"#009ce4"
                anchors.fill: parent
                anchors.rightMargin: 18
                opacity: id_mouseArea.containsMouse ? 0.8:1
            }


            XmsText{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -12
                color:"#FFFFFF"
                text:qsTr("节目单11111111")
                tooltip: qsTr("节目单")

            }

            XmsIcon{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 26
                tooltip: qsTr("节目单")
                size: 16
                text:"\u00e4"
                color:"#FFFFFF"
            }

            MouseArea{
                id: id_mouseArea
                hoverEnabled: true
                cursorShape:  Qt.PointingHandCursor
                anchors.fill: parent
                onClicked:{
                    console.debug("显示节目单------")
                    var t_obj ={
                        "itemId": id_root._channelId,
                        "itemUrl": id_root._channelUrl,
                        "itemName": id_root._programTitle
                    }
                    console.log("id_root._channelId = " + id_root._channelId)
                    console.log("id_root._channelUrl = " + id_root._channelUrl)
                    console.log("id_root._programTitle = " + id_root._programTitle)

                }
            }
        }

        Item{
            width: 1
            height: 10
        }
    }
}
