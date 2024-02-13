#include "ev/Event.h"
#include "ev/EventMacros.h"

#include <iostream>
#include <string>

// Regular function to bind to the event
void OnEventFunction(int value, std::string message) {
	std::cout << "Function: Value = " << value << ", Message = " << message << std::endl;
}

// Declare a single event using the macro
evDECLARE_SINGLE_EVENT(MySingleEvent, int, std::string)

// Subclassing evSingleEvent directly
class CustomSingleEvent : public evSingleEvent<int, std::string> {
public:
	// Optionally, you could add more functionality here
};

int main() {
	// Using the macro-generated class
	MySingleEvent event;
	// Bind a lambda to the event
	event.Bind([](int value, std::string message) {
		std::cout << "Lambda (Macro): Value = " << value << ", Message = " << message << std::endl;
	});
	// Execute the event
	std::cout << "Executing macro-generated single event with lambda...\n";
	event.Execute(10, "Hello from macro lambda!");

	// Bind a regular function to the event
	event.Bind(OnEventFunction);
	// Execute the event
	std::cout << "Executing macro-generated single event with function...\n";
	event.Execute(20, "Hello from macro function!");

	// Using the subclassed event
	CustomSingleEvent customEvent;
	// Bind a lambda to the custom event
	customEvent.Bind([](int value, std::string message) {
		std::cout << "Lambda (Subclass): Value = " << value << ", Message = " << message << std::endl;
	});
	// Execute the custom event
	std::cout << "Executing subclassed single event with lambda...\n";
	customEvent.Execute(30, "Hello from subclass lambda!");

	// Bind a regular function to the custom event
	customEvent.Bind(OnEventFunction);
	// Execute the custom event
	std::cout << "Executing subclassed single event with function...\n";
	customEvent.Execute(40, "Hello from subclass function!");

	return 0;
}
