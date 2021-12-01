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


	// Phase1
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

	//Phase2
	AddAnimationSequence2D("Dragon_Dash");
	AddAnimationSequence2D("Dragon_Idle2");
	AddAnimationSequence2D("Dragon_Tounge_Start", false);
	AddAnimationSequence2D("Dragon_Tounge_Loop");
	AddAnimationSequence2D("Dragon_Tounge_Start", false);
	AddAnimationSequence2D("Dragon_Tounge_Loop");
	AddAnimationSequence2D("Fireboy_Idle");
	AddAnimationSequence2D("Fireboy_Cast", false);
	AddAnimationSequence2D("Fireboy_Cast_Loop");
	AddAnimationSequence2D("Fireboy_Jump_Start", false);
	AddAnimationSequence2D("Fireboy_Jump_Loop_L");
	AddAnimationSequence2D("Fireboy_Jump_Loop_R");




	// Set Anim Play Speed
	SetSequencePlayRate("Dragon_Idle2", 1.5f);
	SetSequencePlayRate("Dragon_Peashot_Start", 1.5f);
	SetSequencePlayRate("Dragon_Peashot_Attack", 1.5f);
	SetSequencePlayRate("Dragon_Peashot_End", 1.5f);
	SetSequencePlayRate("Dragon_Meteor", 1.5f);
	SetSequencePlayRate("Dragon_Meteor_Attack", 1.5f);
	SetSequencePlayRate("Dragon_Tounge_Loop", 1.5f);

	SetSequencePlayRate("Fireboy_Cast", 5.0f);
	SetSequencePlayRate("Fireboy_Cast_Loop", 5.0f);
	SetSequencePlayRate("Fireboy_Idle", 1.5f);
	SetSequencePlayRate("Fireboy_Jump_Start", 5.0f);
	SetSequencePlayRate("Fireboy_Jump_Loop_L", 4.0f);
	SetSequencePlayRate("Fireboy_Jump_Loop_R", 4.0f);


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
