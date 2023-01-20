#include "DisplayElementClass.h"

/**
 * @brief DisplayElementClass::DisplayElementClass
 * @param pType
 * @param X
 * @param Y
 * @param pQStr
 */
DisplayElementClass::DisplayElementClass(DisplayType_e pType, int X, int Y, QString pQStr)
{
    mType = pType;
    mX = X;
    mY = Y;
    mDisplayStr = pQStr;
    mTreeNodeP = nullptr;
    mParentDisplayObjP = nullptr;
}

DisplayElementClass::DisplayElementClass( DisplayType_e pType, int X, int Y, int pWidth, int pHeight, QString pQStr )
{
    mType = pType;
    mX = X;
    mY = Y;
    mDisplayStr = pQStr;

    mWidth = pWidth;
    mHeight = pHeight;
    mTreeNodeP = nullptr;
    mParentDisplayObjP = nullptr;
}

DisplayElementClass::DisplayElementClass( DisplayType_e pType, int X, int Y, int X1, int Y1 )
{
    mType = pType;
    mX = X;
    mY = Y;
    mWidth = X1;
    mHeight = Y1;
    mTreeNodeP = nullptr;
    mParentDisplayObjP = nullptr;
}

/**
 * @brief DisplayElementClass::~DisplayElementClass
 */
DisplayElementClass::~DisplayElementClass()
{

}

