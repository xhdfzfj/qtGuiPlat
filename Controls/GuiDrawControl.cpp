#include "GuiDrawControl.h"

/**
 * @brief GuiDrawControl::GuiDrawControl
 * @param pParent
 */
GuiDrawControl::GuiDrawControl(QQuickItem * pParent) : QQuickPaintedItem( pParent )
{
    qreal _tmpWidth, _tmpHeight;

    _tmpHeight = height();
    _tmpWidth = width();
}

/**
 * @brief GuiDrawControl::~GuiDrawControl
 */
GuiDrawControl::~GuiDrawControl()
{

}


void GuiDrawControl::paint( QPainter * pPainter )
{

}
