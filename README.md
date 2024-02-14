# Eventarium
## Description
Eventarium is designed to offer a straightforward and efficient means to manage events and callbacks in C++. It leverages template programming to provide a flexible API that can support various use cases, from simple notification systems to complex event-driven architectures.

## Overview
This library was originally created as an exercise to create something similar to [Unreal Engine's delegate system](https://benui.ca/unreal/delegates-advanced/), but in a more modern way and a more portable and lightweight approach. I found myself using it in a few projects, so I decided to put it here.

Eventarium introduces two main classes: `evSingleEvent` and `evBroadcastEvent`. [`evSingleEvent`](docs/evSingleEvent.md) allows for a single subscriber to an event, making it ideal for one-to-one notifications. On the other hand, [`evBroadcastEvent`](docs/evBroadcastEvent.md) supports multiple subscribers, allowing for a one-to-many notification pattern. The system is built using modern C++11 features, making it compatible with a wide range of platforms and projects. It's header-only, which means integrating it into your project is as simple as including the relevant files (or build using CMake, whichever you prefer). Eventarium doesn't rely on any third-party libraries, keeping your project lightweight and reducing dependencies.

## Usage and Implementation
Eventarium has two ways to use its event handling capabilities:
1. **(Recommended)** [Macro usage with `evDECLARE...`macros](docs/Macros.md): This method is recommended for most users as it reduces boilerplate code, making your event management cleaner and more maintainable.
2. Direct usage by subclassing or creating templated objects from `evSingleEvent` or `evBroadcastEvent`: This approach offers more control and is straightforward, suitable for those who prefer explicit class management.

| :exclamation:  Check out [demos/demo_single.cpp](demos/demo_single.cpp) and [demos/demo_broadcast.cpp](demos/demo_broadcast.cpp) for samples |
|-------------------------------------------------------------------------------------------------------------------------------------------------------|

### Using `evDECLARE` Macros

The `evDECLARE` macros simplify the declaration of event classes. Here's how you can use them:

#### SingleEvent with evDECLARE
First, declare your event class using the `evDECLARE_SINGLE_EVENT` macro.
```cpp
#include "EventMacros.h"

evDECLARE_SINGLE_EVENT(ValueChangedEvent, int)
```

Then, use it like so:
```cpp
ValueChangedEvent onValueChanged;

// Bind to lambda. Can be bound to a regular function as well.
onValueChanged.Bind([](int newValue) {
    std::cout << "Value changed to: " << newValue << std::endl;
});

// Trigger the event
onValueChanged.Execute(42);
```

#### BroadcastEvent with evDECLARE
Declare your event class using the `evDECLARE_BROADCAST_EVENT` macro.
```cpp
#include "EventMacros.h"

evDECLARE_BROADCAST_EVENT(MessageReceivedEvent, std::string)
```

Usage:
```cpp
// First, define a standard function that matches the macro signature.
void HandleMessage(const std::string& message)
{
    std::cout << "Standard function received: " << message << std::endl;
}

MessageReceivedEvent onMessageReceived;

// Bind to lambda. Can be bound to a regular function as well.
int subscriber1 = onMessageReceived.Add([](const std::string& message) {
    std::cout << "Subscriber 1 received: " << message << std::endl;
});

// Adding a subscriber using a standard function
int subscriber2 = onMessageReceived.Add(HandleMessage);

// Trigger the event
onMessageReceived.Broadcast("Hello, World!");

// Removing a subscriber
onMessageReceived.Remove(subscriber1);
onMessageReceived.Remove(subscriber2);
```

These macros streamline the process of defining event classes, allowing you to focus more on the logic of your application rather than boilerplate code.

### Direct Usage

#### SingleEvent
```cpp
#include "Event.h"

evSingleEvent<int> onValueChanged;

// Bind to lambda. Can be bound to a regular function as well.
onValueChanged.Bind([](int newValue) {
    std::cout << "Value changed to: " << newValue << std::endl;
});

// Trigger the event
onValueChanged.Execute(42);
```

#### BroadcastEvent
```cpp
#include "Event.h"

evBroadcastEvent<std::string> onMessageReceived;

// First, define a standard function that matches the event's signature.
void HandleMessage(const std::string& message)
{
    std::cout << "Standard function received: " << message << std::endl;
}

// Subscriber with a lambda function
int subscriber1 = onMessageReceived.Add([](const std::string& message) {
    std::cout << "Subscriber 1 received: " << message << std::endl;
});

// Adding a subscriber using a standard function
int subscriber2 = onMessageReceived.Add(HandleMessage);

// Trigger the event
onMessageReceived.Broadcast("Hello, World!");

// Remove a subscriber
onMessageReceived.Remove(subscriber1);
onMessageReceived.Remove(subscriber2);
```

## Installation
### Header Only
Eventarium is a header-only library, simplifying its integration into your project. To use it, follow these steps:

1. Clone this repository or download the latest release
   ```
   git clone https://github.com/aashishvasu/eventarium.git
   ```
3. Include the `Event.h` and `EventMacros.h` files in your project.
4. Use `Event.h` for direct usage, `EventMacros.h` for macro based use.

### CMake
CMake is provided if you want to build Eventarium as a library and statically link against it.
1. Clone this repository or download the latest release
   ```
   git clone https://github.com/aashishvasu/eventarium.git
   ```
2. Create build folder
   ```
   mkdir build
   ```
   ```
   cd build
   ```  
3. Generate project
    ```
   cmake ..
   ```
Ensure your compiler supports C++11 or later. No additional dependencies are required.

## Contributing

Contributions from everyone are welcome to improve or extend Eventarium.
1. [**Fork**](https://github.com/aashishvasu/eventarium/fork) the repository on GitHub.
2. **Clone** the project to your own machine.
3. **Commit** changes to your own branch.
4. Submit a **Pull request**

### Reporting Issues
If you find a bug or have a suggestion for improving Eventarium, please [open an issue on GitHub](https://github.com/aashishvasu/eventarium/issues). Provide as much detail as you can, including code samples and your environment details if applicable.

Happy coding!
