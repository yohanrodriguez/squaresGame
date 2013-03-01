#include "Border.h"

Border::Border():
    m_owner(PlayersManager::singleton()->getEmptyPlayer()),
    m_claimTime(0)
{
}

Player const* Border::getOwner() const {
    return m_owner;
}

/*!
* Avoir un propriétaire implique que sa couleur ne soit pas le blanc ( couleur du joueur vide )
*/
bool Border::hasOwner() const {
    return rageLib::sdl::Colors::get()->white != m_owner->getColor();
}

/*!
*   Le plus grand est simplement le plus récemment cliqué
*/
clock_t Border::getClaimTime() const {
    return m_claimTime;
}

/*!
*   Lorsque l'on définit un propriétaire, on indique a quelle date il a été défini
*/
void Border::setOwner(Player const* owner) {
    if(rageLib::sdl::Colors::get()->white == owner->getColor()) {
        m_claimTime = 0;
    } else {
        m_claimTime = clock();
    }
    m_owner = owner;
}
