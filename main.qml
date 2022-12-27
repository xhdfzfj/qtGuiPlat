import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import xhd.controls.guidrawcontrol 1.0

Window {
    width: 1024
    height: 768
    visible: true
    title: qsTr("图形平台")
    id:guiMainWindow

    Rectangle
    {
        anchors.fill: parent
        id:guiMainRectangle

        ColumnLayout
        {
            Rectangle
            {
                id:guiToolBarRect
                Layout.preferredHeight: 80
                Layout.preferredWidth: guiMainRectangle.width
                color:"red"
            }

            GuiDrawControl
            {
                Layout.preferredHeight: guiMainRectangle.height -guiToolBarRect.height
                Layout.preferredWidth: guiMainRectangle.width
            }
        }
    }
}
