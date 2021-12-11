#pragma once
#include "Resource/Animation2D.h"

class BG_KettleHouseAnim :
    public CAnimation2D
{
public:
	BG_KettleHouseAnim();
	BG_KettleHouseAnim(const BG_KettleHouseAnim& anim);
	virtual ~BG_KettleHouseAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual BG_KettleHouseAnim* Clone();
};

