#pragma once

#include "../GameEngine.h"

class CSceneMode
{
    friend class CScene;

protected:
    CSceneMode();
    virtual ~CSceneMode();

protected:
    class CScene* m_pScene;


public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

