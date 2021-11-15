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
    // Anim ����
    void CreateMugmanAnim();
    void CreateStepCloudAnim();
    void CreateWeaponAnim();
    
    // Game Object ����
    void CreateStepCloud();
};

