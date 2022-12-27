#include <QtDebug>
#include <QBrush>
#include "GuiDrawControl.h"

/**
 * @brief GuiDrawControl::GuiDrawControl
 * @param pParent
 */
GuiDrawControl::GuiDrawControl(QQuickItem * pParent) : QQuickPaintedItem( pParent )
{
    mActivedFlag = false;
    mDataSourceP = nullptr;
}

/**
 * @brief GuiDrawControl::~GuiDrawControl
 */
GuiDrawControl::~GuiDrawControl()
{

}

/**
 * @brief GuiDrawControl::sub_ConnectSignal
 */
void GuiDrawControl::sub_ConnectSignal()
{

}

/**
 * @brief GuiDrawControl::sub_WidthChangeByQml
 * @param pWdith
 */
void GuiDrawControl::sub_SizeChanage()
{
    if( mActivedFlag )
    {
        qDebug() << "test test test";
    }
}

/**
 * @brief GuiDrawControl::sub_DrawBackground
 */
void GuiDrawControl::sub_DrawBackground( QPainter * pPainter )
{
    qreal _tmpWidth, _tmpHeight;

    _tmpWidth = width();
    _tmpHeight = height();

    if( ( _tmpWidth != 0 ) && ( _tmpHeight != 0 ) )
    {

//        QRect _tmpRect;
        QBrush _tmpBrush;

        _tmpBrush = QBrush( mBackgroundColor );
//        _tmpRect = QRect(0, 0, _tmpWidth, _tmpHeight );

//        pPainter->drawRect( _tmpRect );

        pPainter->setBackground( _tmpBrush );
    }
}

/**
 * @brief GuiDrawControl::sub_ComponetLoadend
 */
void GuiDrawControl::sub_ComponetLoadend()
{
    qDebug() << __FUNCTION__ << " width:" << width() << " height:" << height();

    mActivedFlag = true;
    mBackgroundColor = fillColor();

    update();
}

/**
 * @brief GuiDrawControl::sub_DisplayFile
 * @param pPath
 */
void GuiDrawControl::sub_DisplayFile( QUrl pPath )
{
    qDebug() << __FUNCTION__;
    if( pPath.isLocalFile() )
    {
        qDebug() << "Local file";

        std::string _tmpStr;

        _tmpStr = pPath.path().toStdString();
    }
}

/**
 * @brief GuiDrawControl::paint
 * @param pPainter
 *      重绘事件的生载
 */
void GuiDrawControl::paint( QPainter * pPainter )
{
    //paint( pPainter );  //调用基类的重绘函数

    sub_DrawBackground( pPainter );
}
