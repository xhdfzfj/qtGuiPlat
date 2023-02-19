#ifndef GUIDRAWCONTROL_H
#define GUIDRAWCONTROL_H

#include <QQuickItem>
#include <QPainter>
#include <list>
#include <map>
#include <QImage>
#include <QtQuick/QQuickPaintedItem>
#include "../Class/ClearObjectInterface.h"
#include "../Class/DisplayElementClass.h"
#include "../Class/DataSourceClass.h"
#include "../Class/BinaryTreeClass.h"
#include "../Class/TreeNodeClass.h"

#define X_SPACE  5
#define Y_SPACE  5

class GuiDrawControl : public QQuickPaintedItem, ClearObjectInterface
{
    Q_OBJECT
public:
    GuiDrawControl( QQuickItem * pParent = nullptr );
    virtual ~GuiDrawControl();

    Q_INVOKABLE void sub_ComponetLoadend( QObject * pObjectP );
    Q_INVOKABLE void sub_SizeChanage();
    Q_INVOKABLE void sub_DisplayFile( QUrl pPath );
    Q_INVOKABLE void sub_ScrollBarChanage( qreal pPosition );
    Q_INVOKABLE void sub_HorScrollBarChanage( qreal pPosition );
    Q_INVOKABLE void sub_CreateBinaryTree( int pHight );

 private:
    void sub_ConnectSignal();
    void sub_DrawBackground( QPainter * pPainter );  //绘制背景
    void sub_DrawBackground( QPainter * pPainterP, QSize pSize );   //根据大小进行背景的绘制
    void sub_DrawDisplayElementS( QPainter * pPainter );  //绘制内容
    void sub_ReadySetHexDataDiaplay( void );
    void sub_CreateDisplayHexData( uint8_t * pDataP, int pNeedLen, int pLen );
    void sub_RefreshDisplayElement( void );
    void sub_CreateBTreeDrawElement( int pTreeHeight );

    void sub_ClearObject() override;

    void sub_DrawBinaryTree();

    int fun_BTreeXcoorndinate( std::map< int64_t, DisplayElementClass * > pParentS,
                               TreeNodeClass< int, int > * pDestNodeP,
                               DisplayElementClass * & pRetParentDispObjP );
    void sub_DrawToImage( int pWidth, int pHeight );
    void sub_AdjustFitWindow( int & pRetWidth );
    bool fun_AdjustTreeLevelDisplay( int pCurrTreeLevel, int pTreeLevel, int pSpaceValue,
                                     std::map< int, std::list< DisplayElementClass * > * > * pAllElementS, int & pRetWidth );
//    bool fun_AdjustDisplayNode( DisplayElementClass * pDisplayObj1P,
//                                DisplayElementClass * pDisplayObj2P,
//                                DisplayElementClass * pDisplayObj3P,
//                                DisplayElementClass * pDisplayObj4P );
    int fun_FindSameParent( DisplayElementClass * pDisplayObj1P, DisplayElementClass * pDisplayObj2P );

    /*********************************
     * 系统重载
     * ******************************/
public:
    void paint( QPainter *painter ) override;

signals:


    /********************************
     * 变量定义
     * ******************************/
private:
    QColor mBackgroundColor;
    bool mActivedFlag;
    QFont mFont;
    int mHexDataWidth;
    int mHexSpaceWidth;
    int mHexDataHeight;
    int mHexDataLineByteS;
    int mHexDataLineS;
    int mAllLineS;

    int mCurrX, mCurrY;
    int mDisplayX, mDisplayY;

    DataSourceClass * mDataSourceP;

    std::list< DisplayElementClass * > mDisplayElementS;

    QObject * mScrollBarObjP;

    BinaryTreeClass< int, int > * mBinTreeObjP;

    QImage * mPainterImageP;
};

#endif // GUIDRAWCONTROL_H
