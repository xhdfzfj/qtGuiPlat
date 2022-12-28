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

        if( mDataSourceP == nullptr )
        {
            mDataSourceP = new DataSourceClass();
        }

        mDataSourceP->sub_SetFileDataSource( _tmpStr );

        sub_ReadySetHexDataDiaplay();
    }
}

/**
 * @brief GuiDrawControl::sub_ReadySetHexDataDiaplay
 */
void GuiDrawControl::sub_ReadySetHexDataDiaplay( void )
{
    QFont _tmpFont( "SimSun", 16 );
    QFontMetrics _tmpFm( _tmpFont );

    QString _tmpTestString = "FF";

    int _width = _tmpFm.width( _tmpTestString );
    int _height = _tmpFm.height();

    _tmpTestString = "F";

    int _spaceWidth = _tmpFm.width( _tmpTestString );

    mFont = _tmpFont;
    mHexDataWidth = _width;
    mHexSpaceWidth = _spaceWidth;
    mHexDataHeight = _height;

    int _tmpLineByteS;
    int _tmpLineS;
    int _x;

    qreal _windowWidth = width();
    qreal _windowHeight = height();

    _x = 0;
    _windowWidth -= 10; //扣除行开头的5个像素与结束的5个像素
    _windowHeight -= 10; //扣除与顶部的间隔5个像素与结束的5个像素

    do
    {
        _tmpLineByteS = ( _windowWidth - _x ) / ( mHexDataWidth + mHexSpaceWidth );
        _x += mHexSpaceWidth;
        qDebug() << "_tmpLineByteS " << _tmpLineByteS;
    }while( ( _tmpLineByteS & 0x07 ) != 0 );

    _tmpLineS = _windowHeight / _height;

    mHexDataLineByteS = _tmpLineByteS;
    mHexDataLineS = _tmpLineS;

    unsigned char * _tmpCurrentPageBufP;

    _tmpCurrentPageBufP = new unsigned char [ _tmpLineS * _tmpLineByteS ];

    int i = mDataSourceP->GetData( _tmpCurrentPageBufP, _tmpLineByteS * _tmpLineS );

    if( i > 0 )
    {
        sub_CreateDisplayHexData( _tmpCurrentPageBufP, _tmpLineByteS * _tmpLineS, i );
        delete [] _tmpCurrentPageBufP;
    }
}

/**
 * @brief GuiDrawControl::sub_CreateDisplayHexData
 * @param pDataBufP
 * @param pNeedLen
 *          要求显示的长度
 * @param pLen
 *          实际要显示的长度
 */
void GuiDrawControl::sub_CreateDisplayHexData( uint8_t * pDataBufP, int pNeedLen, int pLen )
{

}

/**
 * @brief GuiDrawControl::paint
 * @param pPainter
 *      重绘事件的生载
 */
void GuiDrawControl::paint( QPainter * pPainter )
{
    //paint( pPainter );  //调用基类的重绘函数

    //sub_DrawBackground( pPainter );
}
