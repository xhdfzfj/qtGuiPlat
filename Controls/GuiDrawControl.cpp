#include <cmath>
#include <QtDebug>
#include <QBrush>
#include <QQmlProperties>
#include <QTime>
#include <QSize>
#include <QRandomGenerator>
#include "GuiDrawControl.h"


/**
 * @brief GuiDrawControl::GuiDrawControl
 * @param pParent
 */
GuiDrawControl::GuiDrawControl(QQuickItem * pParent) : QQuickPaintedItem( pParent )
{
    mActivedFlag = false;
    mDataSourceP = nullptr;
    mBinTreeObjP = nullptr;
    mPainterImageP = nullptr;

    mDisplayX = 0;
    mDisplayY = 0;

    mFont = QFont( "SimSun", 16 );
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

    if( mPainterImageP != nullptr )
    {
        delete mPainterImageP;
    }

    if( mBinTreeObjP != nullptr )
    {
        delete mBinTreeObjP;
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
        else
        {
            //绘制二叉树
            sub_RefreshDisplayElement();
        }
    }
}

/**
 * @brief GuiDrawControl::sub_CreateBinaryTree
 * @param pHeight
 */
//int _tmpBinTreeNode[] = { 50, 40, 60, 45, 55, 65 };
int _tmpBinTreeNode[] = { 50, 45, 30, 46, 60, 70, 80, 90, 65, 20, 35, 33, 40, 75, 15, 25 };
void GuiDrawControl::sub_CreateBinaryTree( int pHeight )
{
    if( mBinTreeObjP != nullptr )
    {
        delete mBinTreeObjP;
    }

    mBinTreeObjP = new BinaryTreeClass<int, int>();

    QList< int > _tmpNumberS;
    int i, j;
    int _tmpLen;

//    _tmpLen = pow( 2, pHeight ) - 1;
//    //QRandomGenerator::global()->generate()
//    qsrand( QTime(0,0,0).secsTo( QTime::currentTime()));
//    for( i = 0; i < _tmpLen; i++ )
//    {
//        _tmpNumberS.append(qrand() % 10000 );
//        bool flag=true;
//        while(flag)
//        {
//            for(j=0;j<i;j++)
//            {
//                if(_tmpNumberS[i]==_tmpNumberS[j])
//                {
//                    break;
//                }
//            }
//            if(j<i)
//            {
//                _tmpNumberS[i]=rand() % 10000;
//            }
//            if(j==i)
//            {
//                flag=!flag;
//            }
//        }
//    }

    for( i = 0; i < 16; i++ )
    {
        _tmpNumberS.append( _tmpBinTreeNode[ i ] );
    }
    mBinTreeObjP->sub_CreateTree( std::list< int >( _tmpNumberS.begin(), _tmpNumberS.end() ) );

    sub_DrawBinaryTree();
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
 * @brief GuiDrawControl::sub_DrawBackground
 * @param pPainterP
 * @param pSize
 */
void GuiDrawControl::sub_DrawBackground( QPainter *pPainterP, QSize pSize )
{
    int _tmpWidth, _tmpHeight;

    _tmpWidth = pSize.width();
    _tmpHeight = pSize.height();

    if( ( _tmpWidth != 0 ) && ( _tmpHeight != 0 ) )
    {
        QRect _tmpRect;
        QBrush _tmpBrush;

        _tmpRect = QRect(0, 0, _tmpWidth, _tmpHeight );

        _tmpBrush = QBrush( mBackgroundColor );

        pPainterP->setBrush( _tmpBrush );
        pPainterP->drawRect( _tmpRect );

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
    QFont _tmpFont = mFont;
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

    if( mPainterImageP != nullptr )
    {

    }
    else
    {
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
        else
        {
            //绘制二叉树
            sub_RefreshDisplayElement();
        }
    }
}

/**
 * @brief GuiDrawControl::sub_HorScrollBarChanage
 * @param pPosition
 */
void GuiDrawControl::sub_HorScrollBarChanage( qreal pPosition )
{
    int _changeValue;

    if( mPainterImageP != nullptr )
    {
        _changeValue = pPosition * mPainterImageP->width();

        mDisplayX = _changeValue;

        if( ( mDisplayX + width() ) > mPainterImageP->width() )
        {
            mDisplayX = mPainterImageP->width() - width();
        }

        update();
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
    else
    {
        //绘制二㕚树
        sub_DrawBinaryTree();
    }

    update();
}

/**
 * @brief GuiDrawControl::fun_BTreeXcoorndinate
 * @param pParentS
 * @param pDestNodeP
 * @return
 */
int GuiDrawControl::fun_BTreeXcoorndinate( std::map< int64_t, DisplayElementClass * > pParentS,
                                           TreeNodeClass< int, int > * pDestNodeP,
                                           DisplayElementClass * & pRetParentDispObjP )
{
    int64_t _tmpIndex;
    int z, _retValue;
    std::map< int64_t, DisplayElementClass * >::iterator _tmpParentItm;
    DisplayElementClass * _tmpParentDisplayObjP;
    int _startX, _endX;

    _retValue = 0;
    _tmpIndex = ( int64_t )pDestNodeP->GetParent();
    _tmpParentItm = pParentS.find( _tmpIndex );
    if( _tmpParentItm != pParentS.end() )
    {
        _tmpParentDisplayObjP = _tmpParentItm->second;
        pRetParentDispObjP = _tmpParentDisplayObjP;
        z = pDestNodeP->GetParent()->JudgeLeftOrRight( pDestNodeP );  //0 不是子节点 1为左子 2为右子
        if( z == 1 )
        {
            _retValue = _tmpParentDisplayObjP->GetPoint().x() - ( _tmpParentDisplayObjP->GetStartDistance() / 2 );
        }
        else if( z == 2 )
        {
            _retValue = _tmpParentDisplayObjP->GetPoint().x() + ( _tmpParentDisplayObjP->GetEndDistance() / 2 );
        }
    }

    return _retValue;
}


/**
 * @brief GuiDrawControl::sub_CreateBTreeDrawElement
 * @param pTreeHeight
 */
void GuiDrawControl::sub_CreateBTreeDrawElement( int pTreeHeight )
{
    int _width;
    int _height;
    QFont _tmpFont = mFont;
    QFontMetrics _tmpFm( _tmpFont );
    DisplayElementClass * _tmpDisplayObjP;
    TreeNodeClass< int, int > * _tmpNodeP;
    DisplayElementClass * _tmpParentDisplayObjP;
    QString _tmpTestString = "FFFFFFFF";
    int _AllHeight, _AllWidth;
    int i, j, z;
    int _x, _y;
    int _x0, _y0;
    int _x1, _y1;

    _width = _tmpFm.horizontalAdvance( _tmpTestString );
    _height = _tmpFm.height();

    mDisplayElementS.clear();

    _AllWidth =  2 * ( pow( 2, ( pTreeHeight - 1 ) ) ) * _width - _width;       //他每个元素之间都空一个宽度

    if( _AllWidth <= width() )
    {
        _AllWidth = width();
    }

    std::list< TreeNodeClass< int, int > * > _tmpList;
    std::list< TreeNodeClass< int, int > * >::iterator _tmpIte;
    std::map< int64_t, DisplayElementClass * > _tmpParentS;
    std::map< int64_t, DisplayElementClass * >::iterator _tmpParentItm;

    _y = Y_SPACE;
    for( i = 1; i <= pTreeHeight; i++ )
    {
        _x = _AllWidth / pow( 2, i );

        mBinTreeObjP->sub_ReadyTransferLayer( i );
        _tmpList = mBinTreeObjP->fun_GetLayerElementS();
        if( !_tmpList.empty() )
        {
            j = 0;
            qDebug() << "layer:" << i;
            for( _tmpIte = _tmpList.begin(); _tmpIte != _tmpList.end(); ++_tmpIte )
            {
                _tmpNodeP = *_tmpIte;
                qDebug() << "node value:" << _tmpNodeP->GetCompareValue();

                _tmpParentDisplayObjP = nullptr;
                if( !_tmpParentS.empty() )
                {
                    _x = fun_BTreeXcoorndinate( _tmpParentS, _tmpNodeP, _tmpParentDisplayObjP );
                }

                _tmpTestString = QString::number( _tmpNodeP->GetCompareValue() );
                _width = _tmpFm.horizontalAdvance( _tmpTestString );
                _height = _tmpFm.height();

                _tmpDisplayObjP = new DisplayElementClass( EllipipseTextType, _x - ( _width / 2 ), _y,
                                                           _width + DisplayElementClass::EllipipeWidthSpace,
                                                           _height + DisplayElementClass::EllipipeHeightSpace, _tmpTestString );

                _AllHeight = _y + _height + DisplayElementClass::EllipipeHeightSpace + Y_SPACE;

                if( _tmpParentDisplayObjP == nullptr )
                {
                    j = _x - ( _width / 2 ) - X_SPACE;
                    z = _AllWidth - X_SPACE - ( _x - ( _width / 2 ) );
                }
                else
                {
                    j = _x - ( _width / 2 );
                    if( j < _tmpParentDisplayObjP->GetPoint().x() )
                    {
                        z = _tmpParentDisplayObjP->GetPoint().x() - j;
                        j = _tmpParentDisplayObjP->GetStartDistance() / 2;
                    }
                    else
                    {
                        j = j - _tmpParentDisplayObjP->GetPoint().x();
                        z = _tmpParentDisplayObjP->GetEndDistance() / 2;
                    }
                }
                _tmpDisplayObjP->SetDistance( j, z );
                _tmpDisplayObjP->SetFront( Qt::yellow );
                _tmpParentS[ ( int64_t )_tmpNodeP ] = _tmpDisplayObjP;
                mDisplayElementS.push_back( _tmpDisplayObjP );

                //联线的绘图对象
                if( _tmpParentDisplayObjP != nullptr )
                {
                    _x0 = _tmpParentDisplayObjP->GetPoint().x() + _tmpParentDisplayObjP->GetSize().width() / 2;
                    _y0 = _tmpParentDisplayObjP->GetPoint().y() + _tmpParentDisplayObjP->GetSize().height();

                    _x1 = _tmpDisplayObjP->GetPoint().x() + _tmpDisplayObjP->GetSize().width() / 2;
                    _y1 = _tmpDisplayObjP->GetPoint().y();
                    _tmpDisplayObjP = new DisplayElementClass( LineType, _x0, _y0, _x1, _y1 );
                    mDisplayElementS.push_back( _tmpDisplayObjP );
                    _tmpDisplayObjP->SetFront( Qt::green );
                }

            }

            _y += 2 * ( _height + DisplayElementClass::EllipipeHeightSpace ) + DisplayElementClass::EllipipeHeightSpace;
        }
    }

    sub_DrawToImage( _AllWidth, _AllHeight );
    //mPainterImageP->save( "1.jpg", "JPG" );

    update();
}

/**
 * @brief GuiDrawControl::sub_DrawBinaryTree
 */
void GuiDrawControl::sub_DrawBinaryTree()
{
    int _tmpHeight;

    if( mBinTreeObjP != nullptr )
    {

        _tmpHeight = mBinTreeObjP->fun_GetTreeHeight();

        qDebug() << "tree height " << _tmpHeight;

        sub_CreateBTreeDrawElement( _tmpHeight );

    }
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
    QSize _tmpSize;

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
        else if( _tmpDisplayObjP->GetDisplayType() == EllipipseTextType )
        {
            //椭圆与文本
            _tmpPoint = _tmpDisplayObjP->GetPoint();
            _tmpSize = _tmpDisplayObjP->GetSize();

            pPainter->drawEllipse( _tmpPoint.x(), _tmpPoint.y(), _tmpSize.width(), _tmpSize.height() );
            pPainter->drawText( _tmpPoint.x() + 10, _tmpPoint.y() + _tmpSize.height() - 15, _tmpDisplayObjP->GetDiplayString() );
        }
        else if( _tmpDisplayObjP->GetDisplayType() == LineType )
        {
            _tmpPoint = _tmpDisplayObjP->GetPoint();
            _tmpSize = _tmpDisplayObjP->GetSize();

            pPainter->drawLine( _tmpPoint.x(), _tmpPoint.y(), _tmpSize.width(), _tmpSize.height() );
        }
    }
}

/**
 * @brief GuiDrawControl::sub_DrawToImage
 * @param pWidth
 * @param pHeight
 */
void GuiDrawControl::sub_DrawToImage( int pWidth, int pHeight )
{
    if( mPainterImageP != nullptr )
    {
        delete mPainterImageP;
        mPainterImageP = nullptr;
    }

    if( pWidth < width() )
    {
        pWidth = width();
    }
    if( pHeight < height() )
    {
        pHeight = height();
    }
    mPainterImageP = new QImage( pWidth, pHeight, QImage::Format_ARGB32 );
    //mPainterImageP->fill( QColor(0,0,0,0) );

    QPainter _tmpPainter( mPainterImageP );

    sub_DrawBackground( &_tmpPainter, QSize( pWidth, pHeight ) );

    if( !mDisplayElementS.empty() )
    {
        sub_DrawDisplayElementS( &_tmpPainter );
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

    pPainter->setRenderHint( QPainter::Antialiasing );

    if( mPainterImageP != nullptr )
    {
        pPainter->drawImage( 0, 0, *mPainterImageP, mDisplayX, mDisplayY );
    }
    else
    {
        if( !mDisplayElementS.empty() )
        {
            sub_DrawDisplayElementS( pPainter );
        }
    }
}
