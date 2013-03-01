#include "EventCatcher.h"

namespace rageLib{

/*
**
**  CONSTRUCTORS/DESTRUCTORS
**
*/
//{
EventCatcher::EventCatcher():
    m_listeners() {
}
//}
/*
**
**  WRITE ACCESSORS
**
*/
//{
void EventCatcher::addEvent(rageLib::EventReceiver* receiver) {
    m_listeners.insert(receiver);
}

void EventCatcher::removeEvent(rageLib::EventReceiver* receiver) {
    m_listeners.erase(receiver);
}
//}
/*
**
**  NON CONST METHODS
**
*/
//{
void EventCatcher::wait() {
    SDL_Event event;
    SDL_WaitEvent(&event);
    transmit(event);
}

void EventCatcher::poll() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) transmit(event);
}

void EventCatcher::transmit(SDL_Event const& event) {
    switch(event.type) {
        case SDL_MOUSEMOTION:
            for(auto receiver : m_listeners) {
                receiver->onMouseMotion(event.motion);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            for(auto receiver : m_listeners) {
                receiver->onMouseDown(event.button);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            for(auto receiver : m_listeners) {
                receiver->onMouseUp(event.button);
            }
            break;
        case SDL_QUIT:
            for(auto receiver : m_listeners) {
                receiver->onQuit();
            }
            break;
        default:
            break;
    }
}
}
//}
