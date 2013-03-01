#ifndef rageLib_EventCatcher_H
#define rageLib_EventCatcher_H

/*!
*   \file EventCatcher.h
*   \brief Attapeur d'evenements de rageLib
*   \author A. Kryzaal
*   \version 0.1
*   \date 03/01/2012
*   \todo Le séparer en plusieurs classes, rageLib::sdl::EventReceiver, rageLib::irrlicht::EventReceiver ...
*/

#include <SDL/SDL.h>
#include <set>

#include "EventReceiver.h"

/*!
*   \namespace rageLib
*   \brief Ensemble de classes appartenant a la bibliothéque Rage Solutions C++
*/
namespace rageLib{

class EventReceiver;

/*!
*   \class EventCatcher EventCatcher.h
*   \brief Attrapeur d'événements de rageLib
*/
class EventCatcher {

public:
    /*!
    *   \brief Méthode Singleton
    */
    static EventCatcher* get() {
        static EventCatcher* instance(nullptr);
        if(nullptr == instance) {
            instance = new EventCatcher();
        }
        return instance;
    }

    /*!
    *   \brief On bloque l'execution jusqu'a réception d'un évenement, que l'on traitera
    */
    void wait();

    /*!
    *   \brief On traite tout la liste des événements en attente sans bloquer l'execution
    */
    void poll();

    /*!
    *   \brief Enregistre un nouveau listener
    *   \param receiver : L'adresse de l'element a ajouter.
    */
    void addEvent(rageLib::EventReceiver* receiver);

    /*!
    *   \brief Supprime un élément de la liste des listeners
    *   \param receiver : L'adresse de l'element a enlever.
    */
    void removeEvent(rageLib::EventReceiver* receiver);

protected:

    /*!
    *   \brief Transmet l'événement a tous les listeners enregistrés
    *   \param event : L'événement a transmettre
    */
    void transmit(SDL_Event const& event);

    /*!
    *   \brief La liste des listeners
    */
    std::set<rageLib::EventReceiver*> m_listeners;

private:
    EventCatcher();
};
}

#endif // rageLib_EventCatcher_H
