import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
    id: id_root
    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null
    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(id_root)
    }
}

