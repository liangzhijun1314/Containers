import QtQuick 2.0  
  
Rectangle {  
    id: pushBtn;    // 内部调用对象名称  
  
    // 初始固有属性配置  
    width: 27;  
    height: 20;  
    color: "#00000000";  
    //  
  
    // 新添属性  
    // 初始新添image路径属性配置  
    property string imgCurrent: "";  
    property string imgNormal: "";  
    property string imgHover: "";  
    property string imgPressed: "";  
    //  
  
    // 信号属性配置  
    signal clicked();  
    // 新……  
  
    // 按钮image设置  
    Image {  
        source: imgCurrent;  
    }  
  
    // 鼠标活动状况  
    MouseArea {  
  
        anchors.fill: parent;   // 覆盖区域：整个pushBtn  
  
        // 悬停  
        hoverEnabled: true;     // 启用鼠标悬停  
        onEntered: {    // 悬停进入  
            parent.imgCurrent == parent.imgPressed? parent.imgCurrent = parent.imgPressed: parent.imgCurrent = parent.imgHover;  
        }  
        onExited: {     // 悬停离开  
             parent.imgCurrent == parent.imgPressed? parent.imgCurrent = parent.imgPressed: parent.imgCurrent = parent.imgNormal;  
        }  
  
        // 按下  
        onPressed: {  
            parent.imgCurrent = parent.imgPressed;  
        }  
  
        // 弹起  
        onReleased: {  
            parent.imgCurrent = parent.imgNormal;  
            parent.clicked();       // 鼠标按下发射clicked信号  
        }  
  
    }  
}