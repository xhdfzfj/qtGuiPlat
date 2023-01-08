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
    LineType,           //线
}DisplayType_e;

class DisplayElementClass
{
public:
    DisplayElementClass( DisplayType_e pType, int X, int Y, QString pQStr );
    DisplayElementClass( DisplayType_e pType, int X, int Y, int pWidth, int pHeight, QString pQStr );
    DisplayElementClass( DisplayType_e pType, int X, int Y, int X1, int Y1 );
    ~DisplayElementClass();

    void SetFront( QColor pColor )  { mFrontColor = pColor; }
    QColor GetFrontColor() { return mFrontColor; }
    QPoint GetPoint() { return QPoint( mX, mY ); }
    QString GetDiplayString() { return mDisplayStr; }
    DisplayType_e GetDisplayType() { return mType; }
    QSize GetSize() { return QSize( mWidth, mHeight ); }

    void SetDistance( int pStartDistance, int pEndDistance )    { mStartDistance = pStartDistance; mEndDistance = pEndDistance; }
    int GetStartDistance() { return mStartDistance; }
    int GetEndDistance() { return mEndDistance; }

private:
    DisplayType_e mType;

    int mX;
    int mY;

    int mWidth;
    int mHeight;

    int mStartDistance; //到开始处的距离
    int mEndDistance;   //到结束处的距离

    QString mDisplayStr;

    QColor mFrontColor;

public:
    static const int EllipipeWidthSpace = 20;
    static const int EllipipeHeightSpace = 20;
};

#endif // DISPLAYELEMENTCLASS_H
