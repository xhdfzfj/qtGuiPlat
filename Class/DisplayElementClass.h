#ifndef DISPLAYELEMENTCLASS_H
#define DISPLAYELEMENTCLASS_H

#include <QString>
#include <QColor>
#include <QPoint>

typedef enum __DisplayType_e
{
    DiplayHexDataType,
}DisplayType_e;

class DisplayElementClass
{
public:
    DisplayElementClass( DisplayType_e pType, int X, int Y, QString pQStr );
    ~DisplayElementClass();

    void SetFront( QColor pColor )  { mFrontColor = pColor; }
    QColor GetFrontColor() { return mFrontColor; }
    QPoint GetPoint() { return QPoint( mX, mY ); }
    QString GetDiplayString() { return mDisplayStr; }
    DisplayType_e GetDisplayType() { return mType; }

private:
    DisplayType_e mType;

    int mX;
    int mY;

    QString mDisplayStr;

    QColor mFrontColor;
};

#endif // DISPLAYELEMENTCLASS_H
