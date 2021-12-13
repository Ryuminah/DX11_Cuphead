#pragma once
#include "Resource/Animation2D.h"

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

