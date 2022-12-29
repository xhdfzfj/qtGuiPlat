﻿#ifndef GUIDRAWCONTROL_H
#define GUIDRAWCONTROL_H

#include <QQuickItem>
#include <QPainter>
#include <list>
#include <QtQuick/QQuickPaintedItem>
#include "../Class/ClearObjectInterface.h"
#include "../Class/DisplayElementClass.h"
#include "../Class/DataSourceClass.h"

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
 private:
    void sub_ConnectSignal();
    void sub_DrawBackground( QPainter * pPainter );  //绘制背景
    void sub_DrawDisplayElementS( QPainter * pPainter );  //绘制内容
    void sub_ReadySetHexDataDiaplay( void );
    void sub_CreateDisplayHexData( uint8_t * pDataP, int pNeedLen, int pLen );

    void sub_ClearObject();

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

    int mCurrX, mCurrY;

    DataSourceClass * mDataSourceP;

    std::list< DisplayElementClass * > mDisplayElementS;
};

#endif // GUIDRAWCONTROL_H
