#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "SceneMode/MainScene.h"
#include "Input.h"
#include "CollisionManager.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "UI/MouseWidget.h"
#include "Resource/ResourceManager.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
}

bool CClientManager::Init()
{
    //CEngine::GetInst()->OnDebugLog();
    //CEngine::GetInst()->OnLogFPS(true);

    // 키 등록
    CInput::GetInst()->CreateKey("MoveUp", VK_UP);
    CInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
    CInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
    CInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
    CInput::GetInst()->CreateKey("Shoot", 'X');
    CInput::GetInst()->CreateKey("Jump", 'Z');
    CInput::GetInst()->CreateKey("Skill1", '1');
    CInput::GetInst()->CreateKey("Skill2", '2');

    CInput::GetInst()->CreateKey("Dash", VK_LSHIFT);
    CInput::GetInst()->SetShiftKey("Dash", true);
    CInput::GetInst()->SetControlKey("Skill2", true);

    // 예제 코드
    CCollisionManager::GetInst()->CreateChannel("Bullet", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateProfile("Bullet", Collision_Channel::Bullet);

    CCollisionManager::GetInst()->SetProfileChannelState("Bullet", Collision_Channel::Player ,Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Bullet", Collision_Channel::Bullet, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Bullet", Collision_Channel::Static, Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Bullet, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Bullet, Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Static, Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Static", Collision_Channel::Player, Collision_Interaction::Block);


    
    CCollisionManager::GetInst()->SetProfileChannelState("Monster", Collision_Channel::Bullet, Collision_Interaction::Block);



    CSceneManager::GetInst()->SetSceneMode<CMainScene>();

    //CreateMouse();

    return true;
}

void CClientManager::CreateMouse()
{
    // 마우스 애니메이션 시퀀스 생성
    CResourceManager::GetInst()->CreateAnimationSequence2D("MouseDefault");

    std::vector<const TCHAR*> vecFileName;

    vecFileName.push_back(TEXT("Mouse/Default/0.png"));
    vecFileName.push_back(TEXT("Mouse/Default/1.png"));
    vecFileName.push_back(TEXT("Mouse/Default/2.png"));
    vecFileName.push_back(TEXT("Mouse/Default/3.png"));
    vecFileName.push_back(TEXT("Mouse/Default/4.png"));
    vecFileName.push_back(TEXT("Mouse/Default/5.png"));
    vecFileName.push_back(TEXT("Mouse/Default/6.png"));
    vecFileName.push_back(TEXT("Mouse/Default/7.png"));
    vecFileName.push_back(TEXT("Mouse/Default/8.png"));
    vecFileName.push_back(TEXT("Mouse/Default/9.png"));
    vecFileName.push_back(TEXT("Mouse/Default/10.png"));
    vecFileName.push_back(TEXT("Mouse/Default/11.png"));
    vecFileName.push_back(TEXT("Mouse/Default/12.png"));

    CResourceManager::GetInst()->SetAnimationSequence2DTexture("MouseDefault",
        "MouseDefault", vecFileName);

    CResourceManager::GetInst()->AddAnimationSequence2DFrame("MouseDefault",
        Vector2(0.f, 0.f), Vector2(32.f, 31.f), 13);

    CMouseWidget* Mouse = CEngine::GetInst()->CreateMouseWidget<CMouseWidget>("Mouse");

    Mouse->SetSize(32.f, 31.f);

    Mouse->CreateAnimation2D<CAnimation2D>();

    CAnimation2D* MouseAnim = Mouse->GetAnimation2D();

    MouseAnim->AddAnimationSequence2D("MouseDefault");
}
