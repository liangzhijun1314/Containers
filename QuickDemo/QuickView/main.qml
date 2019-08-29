import QtQuick 2.6
import QtQuick.Controls 1.5

Rectangle
{
    id: mainWnd;

    height: 600;
    width: 960;
    color: "yellow";

    border.width: 2;
    border.color: "#ff808080";
//    border.color: "#ffc0c0c0";
//    radius: 10;
    opacity: 1;        // 区分颜色透明度和窗口透明度

    Button {
        id:id_close
        anchors.centerIn: parent;
        text: "--关闭--";
        onClicked: {
            wndCtrl.close();    // 注册后即可使用注册名进行viewer对象调用
        }
    }
}


