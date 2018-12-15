#include "pch.h"
#include "KeyboardListener.h"

template <class T>
KeyboardListener<T>::KeyboardListener(T* target)
{
	_target = target;
}

template <class T>
void KeyboardListener<T>::registerKey(SDL_Keycode keycode, void(*action)(T*))
{
	_actions[keycode] = action;
}

template <class T>
void KeyboardListener<T>::dispatch(SDL_Keycode keycode)
{
	auto action = _actions.find(keycode);
	if(action != _actions.end())
	{
		action(_target);
	}
}

template <class T>
KeyboardListener<T>::~KeyboardListener()
{
	
}
