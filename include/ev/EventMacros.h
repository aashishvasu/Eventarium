// Aashish Vasudevan

#ifndef EVENTMACROS_H
#define EVENTMACROS_H

#include "ev/Event.h"

/*
 * Macros for easy declaration of classes based on evSingleEvent and evBroadcastEvent.
 */

// Macro for declaring a SingleEvent-based class
#define evDECLARE_SINGLE_EVENT(ClassName, ...) \
class ClassName : public evSingleEvent<__VA_ARGS__> \
{ \
public: \
using evSingleEvent<__VA_ARGS__>::evSingleEvent; \
};

/*
 * Broadcast Event Macro
 */
// Macro for declaring a BroadcastEvent-based class
#define evDECLARE_BROADCAST_EVENT(ClassName, ...) \
class ClassName : public evBroadcastEvent<__VA_ARGS__> \
{ \
public: \
using evBroadcastEvent<__VA_ARGS__>::evBroadcastEvent; \
};

#endif // EVENTMACROS_H
