#include "BG_KettleHouseAnim.h"
#include "Component/SpriteComponent.h"

BG_KettleHouseAnim::BG_KettleHouseAnim()
{
}

BG_KettleHouseAnim::BG_KettleHouseAnim(const BG_KettleHouseAnim& anim) :
	CAnimation2D(anim)
{

}

BG_KettleHouseAnim::~BG_KettleHouseAnim()
{
}

void BG_KettleHouseAnim::Start()
{
	CAnimation2D::Start();
}

bool BG_KettleHouseAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	// Title BackGround
	AddAnimationSequence2D("BG_KettleHouse", false);
	AddAnimationSequence2D("FG_KettleHouse", false);

	return true;
}

void BG_KettleHouseAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

BG_KettleHouseAnim* BG_KettleHouseAnim::Clone()
{
	return new BG_KettleHouseAnim(*this);
}
