#pragma once
#include "Resource/Animation2D.h"

// Tutorial에 필요한 모든 Animation과 이미지를 저장
class CTutorialSceneAnim :
    public CAnimation2D
{
public:
	CTutorialSceneAnim();
	CTutorialSceneAnim(const CTutorialSceneAnim& anim);
	virtual ~CTutorialSceneAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CTutorialSceneAnim* Clone();
};

