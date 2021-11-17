#include "DragonAnimation.h"
#include "Component/SpriteComponent.h"

CDragonAnimation::CDragonAnimation()
{
}

CDragonAnimation::CDragonAnimation(const CDragonAnimation& anim) :
	CAnimation2D(anim)
{
}

CDragonAnimation ::~CDragonAnimation()
{
}

void CDragonAnimation::Start()
{
	CAnimation2D::Start();
}

bool CDragonAnimation::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("Dragon_Idle");

	ChangeAnimation("Dragon_Idle");

	return true;
}

void CDragonAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CDragonAnimation* CDragonAnimation::Clone()
{
	return new CDragonAnimation(*this);
}
