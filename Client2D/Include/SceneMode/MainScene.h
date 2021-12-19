#pragma once
#include "Scene/SceneMode.h"

class CMainScene    :
    public CSceneMode
{
    friend class CScene;

protected:
    CMainScene();
    virtual ~CMainScene();

private:
    bool m_pGameStart;
    float   m_WaitTime;

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);


private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();

private:
    // Anim 持失
    void CreateMugmanAnim();
    void CreateStepCloudAnim();
    void CreateWeaponAnim();
    void CreateDragonAnim();
    void CreateBackGroundImage();
    void CreateElderKettleAnim();
    void CreateSound();

    
    // Game Object 持失
    void CreateStepCloud();
    void CreateBackGround();
};

