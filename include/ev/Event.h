// Aashish Vasudevan

#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <unordered_map>

/*
 * Base interface for event handling, supporting binding and unbinding operations.
 */
template<typename... Args>
class IEvent
{
public:
	virtual ~IEvent() = default;
	virtual bool IsBound() = 0;
	virtual void Unbind() = 0;
};

/*
 * Implementation of an event that can bind to a single function.
 */
template<typename... Args>
class evSingleEvent : public IEvent<Args...>
{
public:
	// Binds a function to the event.
	void Bind(std::function<void(Args...)> f);

	// Checks if the event has a function bound to it.
	bool IsBound() override;

	// Unbinds the currently bound function, if any.
	void Unbind() override;

	// Executes the bound function if one is bound.
	void Execute(Args... args);

	// Executes the bound function without checking if one is bound.
	void ExecuteUnchecked(Args... args);
	
private:
	std::function<void(Args...)> func = nullptr;
};

// Definitions
template <typename ... Args>
void evSingleEvent<Args...>::Bind(std::function<void(Args...)> f)
{
	func = f;
}

template <typename ... Args>
void evSingleEvent<Args...>::Execute(Args... args)
{
	if (IsBound())
		func(args...);
}

template <typename ... Args>
void evSingleEvent<Args...>::ExecuteUnchecked(Args... args)
{
	func(args...);
}

template <typename ... Args>
bool evSingleEvent<Args...>::IsBound()
{
	return func != nullptr;
}

template <typename ... Args>
void evSingleEvent<Args...>::Unbind()
{
	func = nullptr;
}

/*
 * Implementation of an event that can have multiple subscriber functions.
 */
template<typename... Args>
class evBroadcastEvent : public IEvent<Args...>
{
public:
	// Adds a function to the event's subscribers and returns its subscription ID.
	int Add(std::function<void(Args...)> f);

	// Checks if the event has any functions bound to it.
	bool IsBound() override;

	// Unbinds all functions currently subscribed to the event.
	void Unbind() override;

	// Removes a specific subscriber by its subscription ID.
	bool Remove(int id);

	// Broadcasts the event to all subscribers.
	void Broadcast(Args... args);

	// Broadcasts the event to all subscribers without checking for subscription.
	void BroadcastUnchecked(Args... args);
	
private:
	int nextID = 0;
	std::unordered_map<int, std::function<void(Args...)>> funcs;
};

// Definitions
template <typename ... Args>
int evBroadcastEvent<Args...>::Add(std::function<void(Args...)> f)
{
	const int id = nextID;
	funcs[id] = f;
	nextID++;
	return id;
}

template <typename ... Args>
void evBroadcastEvent<Args...>::Broadcast(Args... args)
{
	for (std::pair<const int,std::function<void(Args...)>>& func : funcs)
	{
		if (IsBound())
		{
			func.second(args...);
		}
	}
}

template <typename ... Args>
void evBroadcastEvent<Args...>::BroadcastUnchecked(Args... args)
{
	for (std::pair<const int,std::function<void(Args...)>>& func : funcs)
	{
		func.second(args...);
	}
}

template <typename ... Args>
bool evBroadcastEvent<Args...>::IsBound()
{
	return !funcs.empty();
}

template <typename ... Args>
void evBroadcastEvent<Args...>::Unbind()
{
	funcs.clear();
	nextID = 0;
}

template <typename ... Args>
bool evBroadcastEvent<Args...>::Remove(int id)
{
	auto it = funcs.find(id);
	if (it != funcs.end())
	{
		funcs.erase(it);
		return true;
	}
	return false;
}

#endif // EVENT_H
