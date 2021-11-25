#include "BulletAnimation.h"
#include "BackGround_CloudAnim.h"
#include "Component/SpriteComponent.h"

CBackGround_CloudAnim::CBackGround_CloudAnim()
{
}

CBackGround_CloudAnim::CBackGround_CloudAnim(const CBackGround_CloudAnim& anim) :
	CAnimation2D(anim)
{

}

CBackGround_CloudAnim::~CBackGround_CloudAnim()
{
}

void CBackGround_CloudAnim::Start()
{
	CAnimation2D::Start();
}

bool CBackGround_CloudAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	// foreground
	AddAnimationSequence2D("FG_Normal_Cloud1",false);
	AddAnimationSequence2D("FG_Normal_Cloud2", false);
	AddAnimationSequence2D("FG_Normal_Cloud3", false);

	AddAnimationSequence2D("FG_Night_Cloud1", false);
	AddAnimationSequence2D("FG_Night_Cloud2", false);
	AddAnimationSequence2D("FG_Night_Cloud3", false);

	// Background
	AddAnimationSequence2D("BG_Normal_Cloud1", false);
	AddAnimationSequence2D("BG_Normal_Cloud2", false);
	AddAnimationSequence2D("BG_Normal_Cloud3", false);
	AddAnimationSequence2D("BG_Normal_Cloud4", false);
	AddAnimationSequence2D("BG_Normal_Cloud5", false);

	
	AddAnimationSequence2D("BG_Normal_DragonMap", false);

	return true;
}

void CBackGround_CloudAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CBackGround_CloudAnim* CBackGround_CloudAnim::Clone()
{
	return new CBackGround_CloudAnim(*this);
}
