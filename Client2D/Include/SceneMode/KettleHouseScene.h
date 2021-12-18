#pragma once
#include "Scene/SceneMode.h"

class CKettleHouseScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CKettleHouseScene();
    virtual ~CKettleHouseScene();

private:
    bool m_bTutorialOpen;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void CreateKettleHouseAnim();
    void CreateMugmanAnim();
    void CreateWeaponAnim();
    void CreateElderKettleAnim();

public:
    void SetTutorialOpen(bool TutorialOpen);
};

