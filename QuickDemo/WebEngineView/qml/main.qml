import QtQuick 2.6
import QtQuick.Window 2.2
import QtWebEngine 1.2

Window {
    id:mainwindow
    width: 1024
    height: 750
    visible: true
    title: qsTr("WebEngine Demo")

    WebEngineView {
        id:webview
        anchors.fill: parent
//        url:"http://cbox.cntv.cn/cbox2015/zhiboepg/index.shtml"
//        url:"http://cbox.cntv.cn/cbox2015/live/index.shtml"
//        url:"http://cntv.com.cn"
        url:"http://www.baidu.com"
        //国外网站可以全屏
//        url:"http://www.youtube.com"
//        url:"http://digg.com/videos"

        //只有全屏功能的网页 可以全屏
//        url:"E://test.html"

        //国内视频
//        url:"http://www.youku.com"
//        url:"http://tv.sohu.com"
//        url:"http://v.qq.com"

        profile.cachePath: "qrc:/tmp/temp.dat"    //加载网页会有缓存产生，缓存的路径   目前这个可能不起作用
        settings.autoLoadImages: true  //自动在网页上加载图像 默认情况下启用
        settings.defaultTextEncoding: "utf-8"  //设置默认编码。该值必须是描述编码的字符串, 如 "utf-8" 或 "iso-8859-1"。如果留空, 将使用默认值。
        settings.errorPageEnabled: true  //Enables displaying the built-in error pages of Chromium. Enabled by default.
        settings.hyperlinkAuditingEnabled: false   //启用对超链接的ping特性的支持。默认情况下禁用
        settings.javascriptCanAccessClipboard: false  //允许 JavaScript 程序读取或写入剪贴板。 默认情况下禁用
        settings.javascriptCanOpenWindows: true //允许 JavaScript 程序打开新窗口。默认情况下启用。
        settings.javascriptEnabled: true  //启用 JavaScript 程序的运行。默认情况下启用。
        settings.linksIncludedInFocusChain: true  //在键盘焦点链中包含超链接。默认情况下启用。
        settings.localContentCanAccessFileUrls: true //允许本地加载的文档访问其他本地 url。默认情况下启用。
        settings.localContentCanAccessRemoteUrls: false  //允许本地加载的文档访问远程 url。默认情况下禁用。
        settings.localStorageEnabled: true      //启用对 HTML 5 本地存储功能的支持。默认情况下启用。
        settings.spatialNavigationEnabled: false  //
        settings.pluginsEnabled: true  //网页中的视频可以加载，默认是flash player
        settings.fullScreenSupportEnabled: true  //告诉 web 引擎此应用程序中是否支持全屏。默认情况下启用。在 QtWebEngine 1.2 被介绍了。


        zoomFactor:1.0    //网页缩放的比例   0.25 to 5.0  The default factor is 1.0.   需要import   QtWebEngine 1.1以后
//        icon: "qrc:/images/CBox.ico"
        smooth: true  //增强渲染质量
        property bool isShowBusyIndicator: true

        onLoadingChanged: {  // 加载状态变化的信号对应的接收函数
            switch(loadRequest.status)
            {
            case WebEngineLoadRequest.LoadStartedStatus:
                loadingflg.running = true
                console.log("LoadStartedStatus : "+ url)
                break;
            case WebEngineLoadRequest.LoadSucceededStatus:
                loadingflg.running = false
                console.log("LoadSucceededStatus : "+ url)
                break;
            case WebEngineLoadRequest.LoadFailedStatus:
                loadingflg.running = true
                console.log("LoadFailedStatus : "+ url)
                webview.reload()
                break;
            default:
                // 加上以下内容 容易出现切换tab页面时卡住的问题
//                loadingflg.running = true
//                console.log("default : "+ url)
//                webview.reload()
                break;
            }
        }

        onFullScreenRequested: {
            if (request.toggleOn)
                mainwindow.showFullScreen()
            else
                mainwindow.showNormal()
            request.accept()
            console.log("haha")
        }

        MouseArea{
            z:100
            anchors.fill: parent
            acceptedButtons: Qt.RightButton  //只接受鼠标右键
        }

        BusyIndicator{
            id:loadingflg
//            visible: isShowBusyIndicator
            anchors.centerIn: parent
            running: true

        }
        onLinkHovered: {
//            externallyUrl = hoveredUrl
//            console.log("onLinkHovered externallyUrl : "+ externallyUrl)
            console.log("onLinkHovered hoveredUrl : "+ hoveredUrl)
        }

        onNewViewRequested: request.openIn(webview)   //加上该句就是网址变化时可以很好的加载新的内容

    }

}
