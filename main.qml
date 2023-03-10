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

    onWidthChanged:
    {
        onGuiWindowSizeChanage()
    }
    onHeightChanged:
    {
        onGuiWindowSizeChanage()
    }

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
                Layout.preferredWidth: guiMainWindow.width

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

                Button
                {
                    id:selfFitBtn
                    height: 25
                    text:qsTr("树显示")
                    anchors.top: openBtn.top
                    x: 120
                    onClicked:
                    {
                        guiDrawControl.sub_CreateBinaryTree( 5 );
                    }

                    ToolTip
                    {
                        delay: 50   //50ms后出现
                        timeout: 2000 //2秒后消失
                        visible: selfFitBtn.hovered //mouse进入button中
                        text:qsTr( "生成高度5的二叉树" )
                    }

                }
            }

            Rectangle
            {

                Layout.preferredHeight: guiMainRectangle.height -guiToolBarRect.height
                Layout.preferredWidth: guiMainRectangle.width

                //Row
                //{
                //    anchors.fill:parent

//                    Flickable
//                    {
//                        id:guiDrawFlickable
//                        //anchors.fill: parent
//                        clip: true

//                        GuiDrawControl
//                        {
//                            id:guiDrawControl

//                            fillColor: "black"
//                        }
//                    }

                    GuiDrawControl
                    {
                        id:guiDrawControl

                        fillColor: "black"
                    }
//                    Rectangle
//                    {
//                        color:"red"

//                    }

                //}

                ScrollBar
                {
                    id: verticalScrollBar
                    width: 16;
                    height: guiDrawControl.height - 5
                    anchors.left: guiDrawControl.right
                    opacity: 1
                    visible: true
                    enabled: true
                    orientation: Qt.Vertical
                    onPositionChanged:
                    {
                        console.log( "scrollbar ", position );
                        guiDrawControl.sub_ScrollBarChanage( position );
                    }
                }

                ScrollBar
                {
                    id: horizontalScrollBar
                    width: guiDrawControl.width;
                    height: 24
                    anchors.top: guiDrawControl.bottom
                    opacity: 1
                    visible: true
                    enabled: true
                    orientation: Qt.Horizontal
                    onPositionChanged:
                    {
                        console.log( "scrollbar ", position );
                        guiDrawControl.sub_HorScrollBarChanage( position );
                    }
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
                //Qt.quit();
            }
    }


    function onGuiWindowSizeChanage()
    {
        guiDrawControl.width = guiMainWindow.width - verticalScrollBar.width;
        guiDrawControl.height = guiMainRectangle.height -guiToolBarRect.height - horizontalScrollBar.height;

        guiDrawControl.sub_SizeChanage()
    }

    Component.onCompleted:
    {
        console.log( "Componet.completed ", guiToolBarRect.width, guiToolBarRect.height );
        console.log( "Componet.completed ", guiDrawControl.width, guiDrawControl.height );
        guiDrawControl.width = guiToolBarRect.width - verticalScrollBar.width;
        guiDrawControl.height = guiMainWindow.height -guiToolBarRect.height - horizontalScrollBar.height;

        guiDrawControl.sub_ComponetLoadend( verticalScrollBar );
    }
}
