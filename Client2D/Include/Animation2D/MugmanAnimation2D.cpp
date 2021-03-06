#include "MugmanAnimation2D.h"
#include "Component/SpriteComponent.h"

CMugmanAnimation2D::CMugmanAnimation2D()
{
}

CMugmanAnimation2D::CMugmanAnimation2D(const CMugmanAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CMugmanAnimation2D::~CMugmanAnimation2D()
{
	Active(false);
}

void CMugmanAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CMugmanAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;
	// Idle
	AddAnimationSequence2D("Mugman_Idle_R");
	AddAnimationSequence2D("Mugman_Idle_L");
	AddAnimationSequence2D("Mugman_Intro");


	// Aim
	AddAnimationSequence2D("Mugman_Aim_R");
	AddAnimationSequence2D("Mugman_Aim_L");
	AddAnimationSequence2D("Mugman_AimUp_R");
	AddAnimationSequence2D("Mugman_AimUp_L");
	AddAnimationSequence2D("Mugman_AimDown_R");
	AddAnimationSequence2D("Mugman_AimDown_L");
	AddAnimationSequence2D("Mugman_AimUp_Digonal_R");
	AddAnimationSequence2D("Mugman_AimUp_Digonal_L");
	AddAnimationSequence2D("Mugman_AimDown_Digonal_R");
	AddAnimationSequence2D("Mugman_AimDown_Digonal_L");

	SetSequencePlayRate("Mugman_Aim_R", 2.0f);
	SetSequencePlayRate("Mugman_Aim_L", 2.0f);
	SetSequencePlayRate("Mugman_AimUp_R", 2.0f);
	SetSequencePlayRate("Mugman_AimUp_L", 2.0f);
	SetSequencePlayRate("Mugman_AimDown_R", 2.0f);
	SetSequencePlayRate("Mugman_AimDown_L", 2.0f);
	SetSequencePlayRate("Mugman_AimUp_Digonal_R", 2.0f);
	SetSequencePlayRate("Mugman_AimUp_Digonal_L", 2.0f);
	SetSequencePlayRate("Mugman_AimDown_Digonal_R", 2.0f);
	SetSequencePlayRate("Mugman_AimDown_Digonal_L", 2.0f);

	// Run
	AddAnimationSequence2D("Mugman_Run_Normal_R");
	AddAnimationSequence2D("Mugman_Run_Normal_L");

	// Parry
	AddAnimationSequence2D("Mugman_Parry_R",false);
	AddAnimationSequence2D("Mugman_Parry_L",false);

	// Hit
	AddAnimationSequence2D("Mugman_Hit_R",false);
	AddAnimationSequence2D("Mugman_Hit_L",false);
	AddAnimationSequence2D("Mugman_Death",false);

	// Duck
	AddAnimationSequence2D("Mugman_Duck_R", false);
	AddAnimationSequence2D("Mugman_Duck_L", false);
	AddAnimationSequence2D("Mugman_Duck_Loop_R");
	AddAnimationSequence2D("Mugman_Duck_Loop_L");

	SetSequencePlayRate("Mugman_Duck_R", 2.0f);
	SetSequencePlayRate("Mugman_Duck_L", 2.0f);
	SetSequencePlayRate("Mugman_Duck_Loop_R", 2.0f);
	SetSequencePlayRate("Mugman_Duck_Loop_L", 2.0f);


	// Shoot
	AddAnimationSequence2D("Mugman_Run_Shoot_R");
	AddAnimationSequence2D("Mugman_Run_Shoot_L");
	AddAnimationSequence2D("Mugman_Shoot_R");
	AddAnimationSequence2D("Mugman_Shoot_L");
	AddAnimationSequence2D("Mugman_ShootUp_R");
	AddAnimationSequence2D("Mugman_ShootUp_L");

	AddAnimationSequence2D("Mugman_Jump_R");
	AddAnimationSequence2D("Mugman_Jump_L");
	AddAnimationSequence2D("Mugman_Run_AimUp_R");
	AddAnimationSequence2D("Mugman_Run_AimUp_L");


	AddAnimationSequence2D("Mugman_Dash_R", false);
	AddAnimationSequence2D("Mugman_Dash_L", false);
	SetSequencePlayRate("Mugman_Dash_R", 2.0);
	SetSequencePlayRate("Mugman_Dash_L", 2.0);

	// vfx
	AddAnimationSequence2D("Mugman_Dust",false);


	SetSequencePlayRate("Mugman_Idle_R", 2.0f);
	SetSequencePlayRate("Mugman_Idle_L", 2.0f);

	SetSequencePlayRate("Mugman_Shoot_R", 4.0f);
	SetSequencePlayRate("Mugman_Shoot_L", 4.0f);

	SetSequencePlayRate("Mugman_Jump_R", 2.0f);
	SetSequencePlayRate("Mugman_Jump_L", 2.0f);

	

	SetSequencePlayRate("Mugman_Hit_R", 2.0f);
	SetSequencePlayRate("Mugman_Hit_L", 2.0f);

	SetSequencePlayRate("Mugman_Parry_R", 2.0f);
	SetSequencePlayRate("Mugman_Parry_L", 2.0f);
	
	return true;
}

void CMugmanAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CMugmanAnimation2D* CMugmanAnimation2D::Clone()
{
	return new CMugmanAnimation2D(*this);
}
