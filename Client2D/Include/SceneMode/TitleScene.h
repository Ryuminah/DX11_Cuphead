#pragma once
#include "Scene\SceneMode.h"

class CTitleScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CTitleScene();
    virtual ~CTitleScene();

private:
    void CreateTitleSceneAnim();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

};
