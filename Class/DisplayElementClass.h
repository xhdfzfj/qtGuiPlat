#ifndef DISPLAYELEMENTCLASS_H
#define DISPLAYELEMENTCLASS_H

typedef enum __DisplayType_e
{
    DiplayHexDataType,
}DisplayType_e;

class DisplayElementClass
{
public:
    DisplayElementClass( DisplayType_e pType, int X, int Y, QString pQStr );
    ~DisplayElementClass();

private:
    DisplayType_e mType;

    int mX;
    int mY;

    QString mDisplayStr;

};

#endif // DISPLAYELEMENTCLASS_H
