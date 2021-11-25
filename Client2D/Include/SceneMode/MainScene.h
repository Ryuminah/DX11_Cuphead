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
    // Anim 积己
    void CreateMugmanAnim();
    void CreateStepCloudAnim();
    void CreateWeaponAnim();
    void CreateDragonAnim();
    void CreateBackGroundImage();
    
    // Game Object 积己
    void CreateStepCloud();
    void CreateBackGround();


    // 硅版 积己 付荤墨...?
};

