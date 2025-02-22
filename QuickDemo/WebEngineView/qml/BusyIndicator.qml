import QtQuick 2.6
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

BusyIndicator {
    id:busy
    anchors.centerIn: parent
    visible: running
    property string loadingimage:"qrc:/images/images/loading.gif"

    style:BusyIndicatorStyle {
        id:id_mystyle
        indicator: AnimatedImage {
            source:loadingimage;
        }
    }

}
