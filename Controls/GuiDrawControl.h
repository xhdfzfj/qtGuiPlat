#ifndef GUIDRAWCONTROL_H
#define GUIDRAWCONTROL_H

#include <QQuickItem>
#include <QPainter>
#include <QtQuick/QQuickPaintedItem>

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

};

#endif // GUIDRAWCONTROL_H
