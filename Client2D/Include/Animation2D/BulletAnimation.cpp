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

	//ChangeAnimation("Bullet_Loop_R");
	//SetSequencePlayRate("Mugman_Dash_R", 2.0);
	//SetSequencePlayRate("Mugman_Dash_L", 2.0);

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
