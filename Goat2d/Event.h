#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include<list>
#include"SDL.h"

#define ZERO_STATE static_cast<void*>(nullptr)
namespace Goat2d
{
namespace framework
{
	typedef std::function<bool(void* event)> predicat_t;
	typedef std::function<void(void* state)> simple_callback_t;

	enum class EventType:unsigned short
	{
		nonconditional,
		conditional,
		keyboard
	};

	/*
	  Event is another core idea of the Goat2d framework.
	  It combines condition(it can be fn-> true, that means always return true)
	  and action applied to this condition, so you don't need to write
	  bunch of if-elses, just create event inside the scene and pass it to 
	  the event manager.
	*/

	//Every event must inherit this class
	//T is predicat class, F is action class E is class of event
	template<class T, class F>
	class BaseEvent
	{
	protected:
		T predicat;
		F fn;
		EventType type;

		//outer data that is changed by event
		//(it can be nullptr, so event doesn't change anything)
		void* state; 
	public:
		BaseEvent(const T& predicat, 
				  const F& fn, 
				  void* state,
				  EventType type):predicat(predicat),fn(fn),state(state),type(type)
		{}
		virtual ~BaseEvent() {}

		 virtual void process(void* event) = 0;
		 virtual void process() = 0;

		EventType get_type()const { return type; }
	};


	/*
	 This class represents every event connected to keyboard
	*/
	typedef std::function<bool(const SDL_Event& e)> keyboard_pred_t;
	class KeyboardEvent :public BaseEvent<keyboard_pred_t, simple_callback_t>
	{	
	public:
		//constructor for events working with outer state
		KeyboardEvent(const keyboard_pred_t& pred, const simple_callback_t& fn, void* state):
			BaseEvent<keyboard_pred_t,simple_callback_t>(pred,fn,state,EventType::keyboard){}

		//constructor for events that can be described as pure functions
		//because they don't change/require any outer state, so state is just nullptr
		KeyboardEvent(const keyboard_pred_t& pred, const simple_callback_t& fn):
			BaseEvent<keyboard_pred_t,simple_callback_t>(pred,fn,ZERO_STATE,EventType::keyboard){}
		~KeyboardEvent(){}

		void process(void* e)override
		{
			if (predicat(*static_cast<SDL_Event*>(e)))
				fn(state);
		}

		//isn't used
		void process()override { return; }
	};

	/*
	  This class represents common events of game.
	  However, it can be used to program anything that happens in game.
	*/
	class SimpleEvent : public BaseEvent<predicat_t, simple_callback_t>
	{
	private:
		//some outer data passed to predicat
		//it can be nullptr
		void* predicat_event_to_check = nullptr; 
	public:

		//state and predicat_condition are variables
		//that a passed from another places.
		
		//most situation doesn't force you to pass
		//these arguments, so you can use second constructor
		SimpleEvent(const predicat_t& pred, 
					const simple_callback_t& fn, 
					EventType type, 
					void* state,
					void* predicat_condition):
			BaseEvent<predicat_t, simple_callback_t>(pred,fn,state,type)
		{
			predicat_event_to_check = predicat_condition;
		}

		// constructor for events that doesn't require outer state to compute predicat value
		SimpleEvent(const predicat_t& pred,
					const simple_callback_t& fn,
					EventType type)
			:BaseEvent<predicat_t,simple_callback_t>(pred,fn,ZERO_STATE,type)
		{
			//predicat_event_to_check stay nullptr
		}
		~SimpleEvent(){}

		void process()override
		{
			if (type == EventType::nonconditional)
				fn(state);
			else
			{
				if (predicat(predicat_event_to_check))
					fn(state);
			}
		}
		
		//this function isn't used by this class
		void process(void* e)override { return; }
	};

	//sort and store events by their type
	class EventManager
	{
		std::list<KeyboardEvent*> keyboard_events;
		std::list<SimpleEvent*> nonconditional_events, conditional_events;
	public:
		EventManager(){}
		~EventManager(){}

		void add_event(KeyboardEvent* event)
		{
			keyboard_events.push_back(event);
		}
		void add_event(SimpleEvent* event)
		{
			if (event->get_type() == EventType::conditional)
				conditional_events.push_back(event);
			if (event->get_type() == EventType::nonconditional)
				nonconditional_events.push_back(event);
		}

		std::list<KeyboardEvent*>& get_keyboard_events(){ return keyboard_events; }
		std::list<SimpleEvent*>& get_nonconditional_events() { return nonconditional_events; }
		std::list<SimpleEvent*>& get_conditional_events() { return conditional_events; }
	};



	//use this functions in your keyboard predicats
	static inline bool is_key_released(const SDL_Event& e, int key)
	{
		return e.type == SDL_KEYUP and e.key.keysym.sym == key;
	}
	static inline bool is_key_pressed(const SDL_Event& e, int key)
	{
		return e.type == SDL_KEYDOWN and e.key.keysym.sym == key;
	}
};
};

#endif