#include <QtDebug>
#include <QBrush>
#include <QQmlProperties>
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
    sub_ClearObject();

    if( mDataSourceP != nullptr )
    {
        delete mDataSourceP;
    }
}

/**
 * @brief GuiDrawControl::sub_ClearObject
 */
void GuiDrawControl::sub_ClearObject()
{
    DisplayElementClass * _tmpObjP;

    while( !mDisplayElementS.empty() )
    {
        _tmpObjP = mDisplayElementS.front();
        mDisplayElementS.pop_front();

        delete _tmpObjP;
    }
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
    sub_ClearObject();

    if( mActivedFlag )
    {
        if( mDataSourceP != nullptr )
        {
            if( mDataSourceP->GetDataSourceType() == FileDataType )
            {
                sub_ReadySetHexDataDiaplay();
                update();
            }
        }
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
void GuiDrawControl::sub_ComponetLoadend( QObject * pObjectP )
{
    qDebug() << __FUNCTION__ << " width:" << width() << " height:" << height();

    mActivedFlag = true;
    mBackgroundColor = fillColor();

    mScrollBarObjP = pObjectP;

    update();

    //QQmlProperty( pObjectP, "contentHeight").write( height() + 100 );
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
    _windowWidth -= 2 * X_SPACE; //扣除行开头的5个像素与结束的5个像素
    _windowHeight -= 2 * Y_SPACE; //扣除与顶部的间隔5个像素与结束的5个像素

    do
    {
        _tmpLineByteS = ( _windowWidth - _x ) / ( mHexDataWidth + mHexSpaceWidth );
        _x += mHexSpaceWidth;
        qDebug() << "_tmpLineByteS " << _tmpLineByteS;
    }while( ( _tmpLineByteS & 0x07 ) != 0 );

    _tmpLineS = _windowHeight / _height;
    mAllLineS = ( mDataSourceP->GetAllDataLen() + ( _tmpLineByteS - 1 ) ) / _tmpLineByteS;

    mHexDataLineByteS = _tmpLineByteS;
    mHexDataLineS = _tmpLineS;

    unsigned char * _tmpCurrentPageBufP;

    _tmpCurrentPageBufP = new unsigned char [ _tmpLineS * _tmpLineByteS ];

    int i = mDataSourceP->GetData( _tmpCurrentPageBufP, _tmpLineByteS * _tmpLineS );

    mCurrX = X_SPACE;
    mCurrY = Y_SPACE;

    if( i > 0 )
    {
        sub_CreateDisplayHexData( _tmpCurrentPageBufP, _tmpLineByteS * _tmpLineS, i );
        delete [] _tmpCurrentPageBufP;

        update();
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
    int _x, _y;
    QString _tmpStr;
    uint8_t * _tmpP;
    int _tmpLen;
    int i;
    DisplayElementClass * _tmpDisplayObjP;

    _x = mCurrX;
    _y = mCurrY;

    _tmpP = pDataBufP;

    for( i = 0; i < pLen; i++ )
    {
        if( /*( i != 0 ) &&*/ ( ( i % mHexDataLineByteS ) == 0 ) )
        {
            _y += mHexDataHeight;
            _x = mCurrX;
        }

        qDebug() << "x " << _x << " _y " << _y;

        _tmpStr = QString( "%1" ).arg( ( qulonglong )_tmpP[ i ], 2, 16, QLatin1Char( '0' ) );
        _tmpStr = _tmpStr.toUpper();

        _tmpDisplayObjP = new DisplayElementClass( DiplayHexDataType, _x, _y, _tmpStr );
        _tmpDisplayObjP->SetFront( Qt::blue );

        mDisplayElementS.push_back( _tmpDisplayObjP );

        _x += ( mHexDataWidth + mHexSpaceWidth );
    }

    mCurrX = _x;
    mCurrY = _y;
}

/**
 * @brief GuiDrawControl::sub_ScrollBarChanage
 * @param pPosition
 */
void GuiDrawControl::sub_ScrollBarChanage( qreal pPosition )
{
    qDebug() << "Scrollbar Postion " << pPosition;

    int _tmpLine;
    int _tmpPos;

    if( mDataSourceP != nullptr )
    {
        if( mDataSourceP->GetDataSourceType() == FileDataType )
        {
            if( mHexDataLineS < mAllLineS )
            {
                //一页显示不完
                _tmpLine = pPosition * mAllLineS;
                _tmpLine -= ( mHexDataLineS / 2 );
                if( _tmpLine < 0 )
                {
                    _tmpLine = 0;
                }
                _tmpPos = ( _tmpLine * mHexDataLineByteS );

                qDebug() << "new pos " << _tmpPos;

                mDataSourceP->sub_SetDataOffset( _tmpPos );
                sub_RefreshDisplayElement();
            }
        }
    }
}

/**
 * @brief GuiDrawControl::sub_RefreshDisplayElement
 */
void GuiDrawControl::sub_RefreshDisplayElement( void )
{
    sub_ClearObject();

    if( mDataSourceP != nullptr )
    {
        if( mDataSourceP->GetDataSourceType() == FileDataType )
        {
            unsigned char * _tmpCurrentPageBufP;

            _tmpCurrentPageBufP = new unsigned char [ mHexDataLineS * mHexDataLineByteS ];

            mCurrX = X_SPACE;
            mCurrY= Y_SPACE;

            int i = mDataSourceP->GetData( _tmpCurrentPageBufP, mHexDataLineS * mHexDataLineByteS );
            sub_CreateDisplayHexData( _tmpCurrentPageBufP, mHexDataLineS * mHexDataLineByteS, i );
            delete [] _tmpCurrentPageBufP;
        }
    }

    update();
}

/**
 * @brief GuiDrawControl::sub_DrawDisplayElementS
 * @param pPainter
 */
void GuiDrawControl::sub_DrawDisplayElementS( QPainter *pPainter )
{
    QPen _tmpPend;
    QColor _tmpColor;
    QPoint _tmpPoint;

    pPainter->setFont( mFont );

    foreach ( DisplayElementClass * _tmpDisplayObjP, mDisplayElementS )
    {
        _tmpColor = _tmpDisplayObjP->GetFrontColor();

        _tmpPend.setColor( _tmpColor );
        _tmpPoint = _tmpDisplayObjP->GetPoint();

        pPainter->setPen( _tmpPend );

        if( _tmpDisplayObjP->GetDisplayType() == DiplayHexDataType )
        {
            pPainter->drawText( _tmpPoint, _tmpDisplayObjP->GetDiplayString() );
        }
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

    //sub_DrawBackground( pPainter );

    if( !mDisplayElementS.empty() )
    {
        sub_DrawDisplayElementS( pPainter );
    }
}
