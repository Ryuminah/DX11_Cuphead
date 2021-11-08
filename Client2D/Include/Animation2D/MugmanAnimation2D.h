#pragma once
#include "Resource/Animation2D.h"

class CMugmanAnimation2D :
    public CAnimation2D
{
public:
	CMugmanAnimation2D();
	CMugmanAnimation2D(const CMugmanAnimation2D& anim);
	virtual ~CMugmanAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMugmanAnimation2D* Clone();
};

