#pragma once
#include <SDL.h>
#include <map>

template <class T> class KeyboardListener
{
private:
	std::map<SDL_Keycode, void(*)(T*)> _actions;
	T* _target;
public:
	KeyboardListener(T* target)
	{
		_target = target;
	};
	void registerKey(SDL_Keycode keycode, void(*action)(T*))
	{
		_actions[keycode] = action;
	}
	void dispatch(SDL_Keycode keycode)
	{
		auto action = _actions.find(keycode);
		if (action != _actions.end())
		{
			_actions[keycode](_target);
		}
	}

	~KeyboardListener()
	{
	}
};
