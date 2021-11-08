#pragma once

#include "Scene/SceneMode.h"

class CMainScene    :
    public CSceneMode
{
    friend class CScene;

protected:
    CMainScene();
    virtual ~CMainScene();

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();

private:
    // 局聪皋捞记 积己
    void CreateMugmanAnim();
    void CreateStepCloudAnim();

};

