import QtQuick 2.0

XmsText{
    id: id_root
    property alias size: id_root.font.pixelSize
    FontIconLoader{
        id: id_fonter
    }
    smooth: true
    antialiasing: true
    font.family: id_fonter.name
}
