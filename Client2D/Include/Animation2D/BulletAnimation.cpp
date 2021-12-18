#include "BulletAnimation.h"
#include "Component/SpriteComponent.h"

CBulletAnimation::CBulletAnimation()
{
}

CBulletAnimation::CBulletAnimation(const CBulletAnimation& anim) :
	CAnimation2D(anim)
{

}

CBulletAnimation::~CBulletAnimation()
{
}

void CBulletAnimation::Start()
{
	CAnimation2D::Start();
}

bool CBulletAnimation::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("Bullet_Loop_R");
	AddAnimationSequence2D("Bullet_Loop_L");
	AddAnimationSequence2D("Bullet_Spawn", false);
	AddAnimationSequence2D("Bullet_Death", false);

	SetSequencePlayRate("Bullet_Spawn", 4.0f);
	SetSequencePlayRate("Bullet_Death", 4.0f);


	return true;
}

void CBulletAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CBulletAnimation* CBulletAnimation::Clone()
{
	return new CBulletAnimation(*this);
}
