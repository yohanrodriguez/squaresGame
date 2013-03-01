#include "EventReceiver.h"

namespace rageLib{

/*
**
**  CONSTRUCTORS/DESTRUCTORS
**
*/
//{
EventReceiver::EventReceiver() {
    listen();
}

EventReceiver::~EventReceiver() {
    mute();
}
//}
/*
**
**  NON CONST METHODS
**
*/
//{
void EventReceiver::listen() {
    EventCatcher::get()->addEvent(this);
}

void EventReceiver::mute() {
    EventCatcher::get()->removeEvent(this);
}
}
//}
