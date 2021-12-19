#pragma once
#include "Resource/Animation2D.h"

class CScreenFXAnim :
    public CAnimation2D
{
public:
	CScreenFXAnim();
	CScreenFXAnim(const CScreenFXAnim& anim);
	virtual ~CScreenFXAnim();


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CScreenFXAnim* Clone();
};

