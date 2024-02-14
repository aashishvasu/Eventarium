// Aashish Vasudevan

#ifndef EVENT_H
#define EVENT_H

#include "ev/Enums.h"

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
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual EventStatus GetStatus() const = 0;
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

	// Pauses the event. Will not call the subscriber
	void Pause() override;
	
	// Unpauses the event. Will call the subscriber after this is called
	void Resume() override;

	// Get current status of the event
	EventStatus GetStatus() const override;

	// Executes the bound function if one is bound.
	void Execute(Args... args);

	// Executes the bound function without checking if one is bound.
	void ExecuteUnchecked(Args... args);
	
private:
	std::function<void(Args...)> func = nullptr;
	EventStatus status = EventStatus::ES_UNBOUND;
};

// Definitions
template <typename ... Args>
void evSingleEvent<Args...>::Bind(std::function<void(Args...)> f)
{
	func = f;
	status = EventStatus::ES_ACTIVE;
}

template <typename ... Args>
void evSingleEvent<Args...>::Execute(Args... args)
{
	if (IsBound() && status == EventStatus::ES_ACTIVE)
		func(args...);
}

template <typename ... Args>
void evSingleEvent<Args...>::ExecuteUnchecked(Args... args)
{
	if(status == EventStatus::ES_ACTIVE)
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
	status = EventStatus::ES_UNBOUND;
}

template <typename ... Args>
void evSingleEvent<Args...>::Pause()
{
	if (status == IEvent<Args...>::EventStatus::Active)
		status = IEvent<Args...>::EventStatus::Paused;
}

template <typename ... Args>
void evSingleEvent<Args...>::Resume()
{
	if (status == IEvent<Args...>::EventStatus::Paused)
		status = IEvent<Args...>::EventStatus::Active;
}

template <typename ... Args>
EventStatus evSingleEvent<Args...>::GetStatus() const
{
	return status;
}

/*
 * Implementation of an event that can have multiple subscriber functions.
 */
template<typename... Args>
class evBroadcastEvent : public IEvent<Args...>
{
public:
	// Adds a function to the event's subscribers and returns its subscription ID. Also sets event to active
	int Add(std::function<void(Args...)> f);

	// Checks if the event has any functions bound to it.
	bool IsBound() override;

	// Unbinds all functions currently subscribed to the event.
	void Unbind() override;

	// Pauses the event. Will not call the subscribers
	void Pause() override;
	
	// Unpauses the event. Will call the subscribers after this is called
	void Resume() override;

	// Get current status of the event
	EventStatus GetStatus() const override;

	// Removes a specific subscriber by its subscription ID.
	bool Remove(int id);

	// Broadcasts the event to all subscribers.
	void Broadcast(Args... args);

	// Broadcasts the event to all subscribers without checking for subscription.
	void BroadcastUnchecked(Args... args);
	
private:
	int nextID = 0;
	std::unordered_map<int, std::function<void(Args...)>> funcs;
	EventStatus status = EventStatus::ES_UNBOUND;
};

// Definitions
template <typename ... Args>
int evBroadcastEvent<Args...>::Add(std::function<void(Args...)> f)
{
	const int id = nextID;
	funcs[id] = f;
	nextID++;
	status = EventStatus::ES_ACTIVE;
	return id;
}

template <typename ... Args>
void evBroadcastEvent<Args...>::Broadcast(Args... args)
{
	for (std::pair<const int,std::function<void(Args...)>>& func : funcs)
	{
		if (IsBound() && status == EventStatus::ES_ACTIVE)
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
		if(status == EventStatus::ES_ACTIVE)
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
	status = EventStatus::ES_UNBOUND;
}

template <typename ... Args>
void evBroadcastEvent<Args...>::Pause()
{
	if (status == IEvent<Args...>::EventStatus::Active)
		status = IEvent<Args...>::EventStatus::Paused;
}

template <typename ... Args>
void evBroadcastEvent<Args...>::Resume()
{
	if (status == IEvent<Args...>::EventStatus::Paused)
		status = IEvent<Args...>::EventStatus::Active;
}

template <typename ... Args>
EventStatus evBroadcastEvent<Args...>::GetStatus() const
{
	return status;
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
