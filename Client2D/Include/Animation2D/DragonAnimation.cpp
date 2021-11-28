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

	AddAnimationSequence2D("Dragon_Peashot_Start",false);
	AddAnimationSequence2D("Dragon_Peashot_Attack");
	AddAnimationSequence2D("Dragon_Peashot_End", false);

	AddAnimationSequence2D("Dragon_Meteor_Start",false);
	AddAnimationSequence2D("Dragon_Meteor_Attack",false);
	AddAnimationSequence2D("Dragon_Meteor_End", false);

	// sfx
	AddAnimationSequence2D("Dragon_Peashot_Ring");
	AddAnimationSequence2D("Dragon_Peashot_Ring_Pink");
	AddAnimationSequence2D("Dragon_Meteor");
	AddAnimationSequence2D("Dragon_Tail");
	AddAnimationSequence2D("Dragon_MeteorSmoke",false);




	SetSequencePlayRate("Dragon_Idle", 1.5f);
	SetSequencePlayRate("Dragon_Peashot_Start", 1.2f);
	SetSequencePlayRate("Dragon_Peashot_Attack", 1.5f);
	SetSequencePlayRate("Dragon_Peashot_End", 1.5f);
	SetSequencePlayRate("Dragon_Meteor", 1.5f);


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
