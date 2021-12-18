#pragma once
#include "Scene/SceneMode.h"

class CTutorialScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CTutorialScene();
    virtual ~CTutorialScene();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void CreateTutorialMap();

public:
    void CreateTutorialAnim();
    void CreateMugmanAnim();
    void CreateWeaponAnim();
    void CreateElderKettleAnim();


};

