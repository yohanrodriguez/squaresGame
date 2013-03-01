#include "Case.h"

Case::Case(Border* const top, Border* const bottom, Border* const left, Border* const right) :
    m_borders({top, bottom, left, right})
{
}

/*!
*   Le propriétaire est celui qui clos le carré, donc celui qui a cliqué sur une des 4 bordures en dernier
*/
Player const* Case::getOwner() const{
    if(
        m_borders.bottom->hasOwner()
        && m_borders.top->hasOwner()
        && m_borders.left->hasOwner()
        && m_borders.right->hasOwner()
    ) {
        //On compare les 4 bordures pour trouver celle qui à été réclamée le plus tard
        Border* t1 = (m_borders.top->getClaimTime() > m_borders.bottom->getClaimTime()) ? m_borders.top : m_borders.bottom;
        Border* t2 = (m_borders.left->getClaimTime() > m_borders.right->getClaimTime()) ? m_borders.left : m_borders.right;

        return (t1->getClaimTime() > t2->getClaimTime()) ? t1->getOwner() : t2->getOwner();
    }
    return PlayersManager::singleton()->getEmptyPlayer();
}

Border* Case::getTopBorder() const {
    return m_borders.top;
}

Border* Case::getLeftBorder() const {
    return m_borders.left;
}

Border* Case::getRightBorder() const {
    return m_borders.right;
}

Border* Case::getBottomBorder() const {
    return m_borders.bottom;
}
