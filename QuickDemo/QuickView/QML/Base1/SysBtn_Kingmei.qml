    import QtQuick 2.0  
    import "../Base"  
      
      
    Row {  
        id: sysBtns;    // 内部调用对象名称  
      
        anchors.rightMargin: 10;      // 右侧空隙：10个像素  
      
        // 信号属性配置  
        signal min();  
        signal close();  
      
        // 系统按钮图片目录属性配置  
        property string imgPath: "../Base_1/Image/";  
      
        // 系统按钮（从左到右顺序添加）  
        PushBtn_Kingmei {  
            id: minBtn;     // 内部调用对象名称  
      
            // 最小化按钮image源  
            imgNormal: imgPath + "min_normal.png";  
            imgPressed: imgPath + "min_pressed.png";  
            imgHover: imgPath + "min_hover.png";  
            imgCurrent: imgNormal;  
      
            // 槽  
            onClicked: {  
                parent.min();  
            }  
        }  
      
        PushBtn_Kingmei {  
            id: closeBtn;       // 内部调用对象名称  
      
            // 关闭按钮image源  
            imgNormal: imgPath + "close_normal.png";  
            imgPressed: imgPath + "close_pressed.png";  
            imgHover: imgPath + "close_hover.png";  
            imgCurrent: imgNormal;  
      
            // 槽  
            onClicked: {              
                parent.close();  
            }  
      
        }  
    }  