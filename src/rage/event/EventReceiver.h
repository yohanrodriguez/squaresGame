#ifndef rageLib_EventReceiver_H
#define rageLib_EventReceiver_H

/*!
*   \file EventReceiver.h
*   \brief Listener d'EventCatcher
*   \author A. Kryzaal
*   \version 0.1
*   \date 03/01/2012
*/

#include "EventCatcher.h"

/*!
*   \namespace rageLib
*   \brief Ensemble de classes appartenant a la bibliothéque Rage Solutions C++
*/
namespace rageLib{

/*!
*   \class EventReceiver EventReceiver.h
*   \brief Classe mére de toute classe voulant recevoir des événements.
*/
class EventReceiver {

public:

    /*!
    *   \brief Constructeur d'EventReceiver
    */
    EventReceiver();

    /*!
    *   \brief Destructeur d'EventReceiver
    */
    virtual ~EventReceiver();

    /*!
    *   \brief Met en mode écoute le receveur
    */
    void listen();

    /*!
    *   \brief Désactive l'ecoute des événements
    */
    void mute();

private:

    friend class EventCatcher;

    /*!
    *   \brief Méthode recevant les signaux de type Mouse Up
    *   \param event : l'objet SDL contenant les infos de l'evenement
    */
    virtual void onMouseUp(SDL_MouseButtonEvent const event) {
        doNothing(event);
    };

    /*!
    *   \brief Méthode recevant les signaux de type Mouse Down
    *   \param event : l'objet SDL contenant les infos de l'evenement
    */
    virtual void onMouseDown(SDL_MouseButtonEvent const event) {
        doNothing(event);
    };

    /*!
    *   \brief Méthode recevant les signaux de type Mouse Motion
    *   \param event : l'objet SDL contenant les infos de l'evenement
    */
    virtual void onMouseMotion(SDL_MouseMotionEvent const event) {
        doNothing(event);
    };

    /*!
    *   \brief Méthode recevant les signaux de type Quit
    */
    virtual void onQuit() {};

    inline void doNothing(...) const {};
};
}

#endif // rageLib_EventReceiver_H
