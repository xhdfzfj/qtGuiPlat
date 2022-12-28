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
}

/**
 * @brief DisplayElementClass::~DisplayElementClass
 */
DisplayElementClass::~DisplayElementClass()
{

}

