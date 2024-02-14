# evSingleEvent

`evSingleEvent` is designed for handling events that can bind to a single function. This class allows for simple event subscription and execution mechanisms.

## Functions

| Name of Function | Description | Sample Usage |
|------------------|-------------|--------------|
| `Bind` | Binds a function to the event. | `event.Bind([](int a){ std::cout << a; });`<br>`void myFunc(int a) { std::cout << a; }`<br>`event.Bind(myFunc);` |
| `IsBound` | Checks if the event has a function bound to it. | `if (event.IsBound()) { /* ... */ }` |
| `Unbind` | Unbinds the currently bound function, if any. | `event.Unbind();` |
| `Pause` | Pauses the event, preventing the bound function from being called. | `event.Pause();` |
| `Resume` | Resumes the event, allowing the bound function to be called. | `event.Resume();` |
| `GetStatus` | Gets the current status of the event. | `#include "ev/Enums.h"`<br><br>`EventStatus status = event.GetStatus();` |
| `Execute` | Executes the bound function if one is bound and the event is active. | `event.Execute(5);` |
| `ExecuteUnchecked` | Executes the bound function without checking if one is bound or the event's status. | `event.ExecuteUnchecked(5);` |

## Example Usage

```cpp
evSingleEvent<int> myEvent;

// Binding a lambda function
myEvent.Bind([](int value) {
    std::cout << "Value: " << value << std::endl;
});

// Executing the event
myEvent.Execute(10);

// Binding a normal function
void printInt(int value) {
    std::cout << "Value: " << value << std::endl;
}
myEvent.Bind(printInt);
myEvent.Execute(20);
```
