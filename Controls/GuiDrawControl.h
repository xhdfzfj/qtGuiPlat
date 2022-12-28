#ifndef GUIDRAWCONTROL_H
#define GUIDRAWCONTROL_H

#include <QQuickItem>
#include <QPainter>
#include <QtQuick/QQuickPaintedItem>
#include "../Class/DataSourceClass.h"

class GuiDrawControl : public QQuickPaintedItem
{
    Q_OBJECT
public:
    GuiDrawControl( QQuickItem * pParent = nullptr );
    virtual ~GuiDrawControl();

    Q_INVOKABLE void sub_ComponetLoadend();
    Q_INVOKABLE void sub_SizeChanage();
    Q_INVOKABLE void sub_DisplayFile( QUrl pPath );
 private:
    void sub_ConnectSignal();
    void sub_DrawBackground( QPainter * pPainter );  //绘制背景
    void sub_ReadySetHexDataDiaplay( void );
    void sub_CreateDisplayHexData( uint8_t * pDataP, int pNeedLen, int pLen );

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

    DataSourceClass * mDataSourceP;

};

#endif // GUIDRAWCONTROL_H
