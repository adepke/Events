/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include <functional>
#include <vector>

template <typename... Ts>
class Event
{
public:
	struct Listener
	{
		friend class Event;
		
	private:
		unsigned int ID;

		std::function<void(Ts...)> Functor;

	public:
		template <typename T>
		Listener(T InFunctor) : Functor(InFunctor) {}

		template <typename... ForwardTs>
		void operator()(ForwardTs&&... Args)
		{
			Functor(std::forward<Ts>(Args)...);
		}

		bool operator==(const Listener& Other)
		{
			return ID == Other.ID;
		}
	};

private:
	std::vector<Listener> Listeners;

	unsigned int NextID = 0;

public:
	Listener& operator+=(std::function<void(Ts...)> Function)
	{
		Listener NewListener{ Function };
		NewListener.ID = NextID++;

		Listeners.push_back(NewListener);

		return Listeners.back();
	}

	bool operator-=(const Listener& Handle)
	{
		auto Iter = std::find(Listeners.begin(), Listeners.end(), Handle);
		if (Iter != Listeners.end())
		{
			Listeners.erase(Iter);

			return true;
		}

		return false;
	}

	template <typename... ForwardTs>
	void operator()(ForwardTs&&... Args)
	{
		for (auto& Handle : Listeners)
		{
			Handle(std::forward<Ts>(Args)...);
		}
	}
};
