#pragma once

#include "Thread.h"

class CLoadingThread :
    public CThread
{
public:
	CLoadingThread();
	~CLoadingThread();

private:
	bool m_bIsTutorialScene;
	bool m_bIsMainScene;

public:
	virtual void Run();

public:
	void SetTutorialScene(bool IsTutorialScene)
	{
		m_bIsMainScene = false;
		m_bIsTutorialScene = IsTutorialScene;
	}

	void SetMainScene(bool IsMainScene)
	{
		m_bIsTutorialScene = false;
		m_bIsMainScene = IsMainScene;
	}

	bool GetIsTutorialScene()
	{
		return m_bIsTutorialScene;
	}

	bool GetIsMainScene()
	{
		return m_bIsMainScene;
	}
};


