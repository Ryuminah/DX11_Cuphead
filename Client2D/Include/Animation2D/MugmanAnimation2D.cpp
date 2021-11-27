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
}

void CMugmanAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CMugmanAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("Mugman_Idle_R");
	AddAnimationSequence2D("Mugman_Idle_L");
	AddAnimationSequence2D("Mugman_AimUp_R");
	AddAnimationSequence2D("Mugman_AimUp_L");
	AddAnimationSequence2D("Mugman_Run_Shoot_R");
	AddAnimationSequence2D("Mugman_Run_Shoot_L");
	AddAnimationSequence2D("Mugman_Shoot_R");
	AddAnimationSequence2D("Mugman_Shoot_L");

	AddAnimationSequence2D("Mugman_Jump_R");
	AddAnimationSequence2D("Mugman_Jump_L");
	AddAnimationSequence2D("Mugman_Run_AimUp_R");
	AddAnimationSequence2D("Mugman_Run_AimUp_L");
	AddAnimationSequence2D("Mugman_Dash_R", false);
	AddAnimationSequence2D("Mugman_Dash_L", false);

	SetSequencePlayRate("Mugman_Idle_R", 2.0f);
	SetSequencePlayRate("Mugman_Idle_L", 2.0f);

	SetSequencePlayRate("Mugman_Shoot_R", 6.0f);
	SetSequencePlayRate("Mugman_Shoot_L", 6.0f);

	SetSequencePlayRate("Mugman_Jump_R", 4.0f);
	SetSequencePlayRate("Mugman_Jump_L", 4.0f);

	SetSequencePlayRate("Mugman_Dash_R", 2.0);
	SetSequencePlayRate("Mugman_Dash_L", 2.0);

	

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
