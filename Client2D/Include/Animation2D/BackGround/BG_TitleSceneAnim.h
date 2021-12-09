#pragma once
#include "Resource/Animation2D.h"

class BG_TitleSceneAnim :
    public CAnimation2D
{
public:
	BG_TitleSceneAnim();
	BG_TitleSceneAnim(const BG_TitleSceneAnim& anim);
	virtual ~BG_TitleSceneAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual BG_TitleSceneAnim* Clone();
};

