#pragma once
#include "Scene\SceneMode.h"

class CLoadingScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CLoadingScene();
    virtual ~CLoadingScene();

private:
    class CLoadingThread* m_Thread;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void CreateLoadingAnim();

public:
    void SetTutorialScene(bool IsTutorialScene);
    void SetMainScene(bool IsMainScene);

};
