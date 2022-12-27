import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
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

                Button
                {
                    id:openBtn
                    height: 25
                    text:qsTr("浏览...")
                    x:5
                    y:20
                    onClicked:
                    {
                        fds.open()
                    }
                }
            }

            GuiDrawControl
            {
                id:guiDrawControl
                Layout.preferredHeight: guiMainRectangle.height -guiToolBarRect.height
                Layout.preferredWidth: guiMainRectangle.width

                fillColor: "black"
                onWidthChanged:
                {
                    console.log( "GuiDrawControl onWidthChanaged:%d", guiToolBarRect.width )
                    onGuiDrawControlSizeChanage()
                }
                onHeightChanged:
                {
                    onGuiDrawControlSizeChanage()
                }
            }
        }
    }

    FileDialog
    {
            id:fds
            title: "选择文件"
            folder: shortcuts.desktop
            selectExisting: true
            selectFolder: false
            selectMultiple: false
            //nameFilters: ["json文件 (*.json)"]
            onAccepted:
            {
                //labels.text = fds.fileUrl;
                console.log("You chose: " + fds.fileUrl);
                guiDrawControl.sub_DisplayFile( fds.fileUrl )
            }

            onRejected:
            {
                //labels.text = "";
                console.log("Canceled");
                Qt.quit();
            }
    }


    function onGuiDrawControlSizeChanage()
    {
        guiDrawControl.sub_SizeChanage()
    }

    Component.onCompleted:
    {
        console.log( "Componet.completed-->%d--%d", guiToolBarRect.width, guiToolBarRect.height );
        console.log( "Componet.completed-->%d--%d", guiDrawControl.width, guiDrawControl.height );
        guiDrawControl.sub_ComponetLoadend();
    }
}
