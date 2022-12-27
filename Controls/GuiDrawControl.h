#ifndef GUIDRAWCONTROL_H
#define GUIDRAWCONTROL_H

#include <QQuickItem>
#include <QtQuick/QQuickPaintedItem>

class GuiDrawControl : public QQuickPaintedItem
{
    Q_OBJECT
public:
    GuiDrawControl( QQuickItem * pParent = nullptr );
    virtual ~GuiDrawControl();

    /*********************************
     * 系统重载
     * ******************************/
public:
    void paint( QPainter *painter ) override;

signals:

};

#endif // GUIDRAWCONTROL_H
