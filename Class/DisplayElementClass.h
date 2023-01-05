#ifndef DISPLAYELEMENTCLASS_H
#define DISPLAYELEMENTCLASS_H

#include <QString>
#include <QColor>
#include <QSize>
#include <QPoint>

typedef enum __DisplayType_e
{
    DiplayHexDataType,
    EllipipseTextType,  //椭圆加文本
}DisplayType_e;

class DisplayElementClass
{
public:
    DisplayElementClass( DisplayType_e pType, int X, int Y, QString pQStr );
    DisplayElementClass( DisplayType_e pType, int X, int Y, int pWidth, int pHeight, QString pQStr );
    ~DisplayElementClass();

    void SetFront( QColor pColor )  { mFrontColor = pColor; }
    QColor GetFrontColor() { return mFrontColor; }
    QPoint GetPoint() { return QPoint( mX, mY ); }
    QString GetDiplayString() { return mDisplayStr; }
    DisplayType_e GetDisplayType() { return mType; }
    QSize GetSize() { return QSize( mWidth, mHeight ); }

private:
    DisplayType_e mType;

    int mX;
    int mY;

    int mWidth;
    int mHeight;

    QString mDisplayStr;

    QColor mFrontColor;
};

#endif // DISPLAYELEMENTCLASS_H
