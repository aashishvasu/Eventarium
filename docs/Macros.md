# Event Macros Documentation

This document provides an overview of the macros defined in `EventMacros.h` for easy declaration of event classes based on [`evSingleEvent`](docs/evSingleEvent.md) and [`evBroadcastEvent`](docs/evBroadcastEvent.md) within the `Eventarium` C++ library.

## Macros

### Single Event Macro

- **Macro Name**: `evDECLARE_SINGLE_EVENT`
- **Purpose**: Declares a class based on `evSingleEvent` for handling single subscriber events.
- **Parameters**:
  - `ClassName`: The name of the class to be declared.
  - `...`: Variadic template arguments representing the types of arguments the event function will accept.

#### Example Usage

```cpp
evDECLARE_SINGLE_EVENT(MySingleEvent, int, std::string)

void HandleSingleEvent(int num, std::string str) {
    std::cout << "Handling single event with num: " << num << " and str: " << str << std::endl;
}

MySingleEvent event;
event.Bind(HandleSingleEvent);
event.Execute(42, "Hello World");
```

### Broadcast Event Macro

- **Macro Name**: `evDECLARE_BROADCAST_EVENT`
- **Purpose**: Declares a class based on `evBroadcastEvent` for handling events with multiple subscribers.
- **Parameters**:
  - `ClassName`: The name of the class to be declared.
  - `...`: Variadic template arguments representing the types of arguments the event function will accept.

#### Example Usage

```cpp
evDECLARE_BROADCAST_EVENT(MyBroadcastEvent, int)

void SubscriberOne(int value) {
    std::cout << "Subscriber One received value: " << value << std::endl;
}

void SubscriberTwo(int value) {
    std::cout << "Subscriber Two received value: " << value << std::endl;
}

MyBroadcastEvent broadcastEvent;
int id1 = broadcastEvent.Add(SubscriberOne);
int id2 = broadcastEvent.Add(SubscriberTwo);

broadcastEvent.Broadcast(100);
```