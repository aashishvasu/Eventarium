
### Documentation for `evBroadcastEvent`

# evBroadcastEvent

`evBroadcastEvent` allows for handling events that can have multiple subscriber functions. It supports adding, removing, and broadcasting to multiple subscribers.

## Functions

| Name of Function | Description | Sample Usage |
|------------------|-------------|--------------|
| `Add` | Adds a function to the event's subscribers. | `int id = event.Add([](int a){ std::cout << a; });`<br>`void myFunc(int a) { std::cout << a; }`<br>`int id = event.Add(myFunc);` |
| `IsBound` | Checks if the event has any functions bound to it. | `if (event.IsBound()) { /* ... */ }` |
| `Unbind` | Unbinds all functions currently subscribed to the event. | `event.Unbind();` |
| `Pause` | Pauses the event, preventing subscribers from being called. | `event.Pause();` |
| `Resume` | Resumes the event, allowing subscribers to be called. | `event.Resume();` |
| `GetStatus` | Gets the current status of the event. | `#include "ev/Enums.h"`<br><br>`EventStatus status = event.GetStatus();` |
| `Remove` | Removes a specific subscriber by its subscription ID. | `event.Remove(id);` |
| `Broadcast` | Broadcasts the event to all subscribers if the event is active. | `event.Broadcast(5);` |
| `BroadcastUnchecked` | Broadcasts the event to all subscribers without checking the event's status. | `event.BroadcastUnchecked(5);` |

## Example Usage

```cpp
evBroadcastEvent<int> myEvent;

// Adding a lambda function
int id1 = myEvent.Add([](int value) {
    std::cout << "Lambda Value: " << value << std::endl;
});

// Adding a normal function
void printInt(int value) {
    std::cout << "Function Value: " << value << std::endl;
}
int id2 = myEvent.Add(printInt);

// Broadcasting to all subscribers
myEvent.Broadcast(10);

// Removing a subscriber
myEvent.Remove(id1);

// Broadcasting again
myEvent.Broadcast(20);
```
