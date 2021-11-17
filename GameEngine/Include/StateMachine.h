#pragma once
#include "GameEngine.h"
#include <assert.h>

template <typename T>
class FSMState
{
private:
	T* m_pOwner;
	std::function<void(T::* m_StartFunc(float)>> ();
	std::function<void(T::* m_StaytFunc(float)>> ();
	std::function<void(T::* m_EndFunc(float)>> ();


public:
	void Start()
	{
		if (m_Start)
		{

		}
	}

	void Update()
	{

	}

	void End()
	{

	}

};

template <typename T>
class CStateMachine
{
private:
	std::unordered_map<std::string, class FSMState*>	m_mapFSMState;
	class FSMState* m_CurrentState;

public:
	void Update()
	{
		if (nullptr == m_currentState)
		{
			assert("nullptr == m_currentState");
		}

		m_currentState->Update();
	}

public:
	void CreateState(std::string StateName, T* TargetObject,
		std::function<void(T::* StartFunc(float)> ,
		std::function<void(T::* StayFunc(float) >= nullptr,
		std::function<void(T::* EndFunc(float) >= nullptr);

public:
	StateMachine() : m_CurrentState(nullptr)
	{

	}

	~StateMachine()
	{
		m_State.clear();
	}
};

