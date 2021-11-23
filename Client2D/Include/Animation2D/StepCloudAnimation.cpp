#include "StepCloudAnimation.h"
#include "Component/SpriteComponent.h"

CStepCloudAnimation::CStepCloudAnimation()
{
}

CStepCloudAnimation::CStepCloudAnimation(const CStepCloudAnimation& anim) :
	CAnimation2D(anim)
{
}

CStepCloudAnimation ::~CStepCloudAnimation()
{
}

void CStepCloudAnimation::Start()
{
	CAnimation2D::Start();
}

bool CStepCloudAnimation::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("Cloud_Down");
	AddAnimationSequence2D("Cloud_Down_Idle");
	AddAnimationSequence2D("Cloud_Idle");
	AddAnimationSequence2D("Cloud_Up",false);

	SetSequencePlayRate("Cloud_Idle", 3.5f);

	SetSequencePlayRate("Cloud_Down_Idle", 3.5f);
	SetSequencePlayRate("Cloud_Up", 3.5f);

	ChangeAnimation("Cloud_Idle");

	return true;
}

void CStepCloudAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CStepCloudAnimation* CStepCloudAnimation::Clone()
{
	return new CStepCloudAnimation(*this);
}
