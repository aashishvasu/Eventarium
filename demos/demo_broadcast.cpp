#include "ev/Event.h"
#include "ev/EventMacros.h"

#include <iostream>

// Regular function to bind to the broadcast event
void RegularFunction(float num) {
	std::cout << "Regular Function: Received float " << num << std::endl;
}

// Declare a broadcast event that takes a float
evDECLARE_BROADCAST_EVENT(FloatBroadcastEvent, float)

class CustomFloatBroadcastEvent : public evBroadcastEvent<float> {
public:
	// Optionally, you could add more functionality here
};

int main() {
	// Instance of the macro-generated broadcast event
	FloatBroadcastEvent myBroadcastEvent;

	// Bind a lambda expression to the broadcast event
	myBroadcastEvent.Add([](float number) {
		std::cout << "Lambda Handler: Received float " << number << '\n';
	});

	// Bind the regular function to the broadcast event
	myBroadcastEvent.Add(RegularFunction);

	// Trigger the macro-generated broadcast event
	std::cout << "Triggering Macro-Generated BroadcastEvent...\n";
	myBroadcastEvent.Broadcast(3.14f);

	// Instance of the subclassed broadcast event
	CustomFloatBroadcastEvent myCustomEvent;
	
	// Bind a lambda expression to the subclassed event
	myCustomEvent.Add([](float number) {
		std::cout << "Lambda in Subclass: Received float " << number * 2 << " (doubled)\n";
	});
	
	// Bind the regular function to the subclassed event
	myCustomEvent.Add(RegularFunction);
	
	// Trigger the subclassed broadcast event using the custom method
	std::cout << "\nTriggering Subclassed BroadcastEvent ...\n";
	myCustomEvent.Broadcast(1.57f);

	return 0;
}
