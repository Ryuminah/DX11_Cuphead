#pragma once
#include "Scene\SceneMode.h"
#include "../Editor.h"
class CEditorScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CEditorScene();
    virtual ~CEditorScene();

private:
    class CTileMapWindow* m_TileMapWindow;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);

private:
    void AimUp(float DeltaTime);
    void Duck(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void MouseLButton(float DeltaTime);

private:
    void EditTileType();
    void EditTileImage();
};

