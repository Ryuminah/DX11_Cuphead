#include "BulletAnimation.h"
#include "ForeGroundAnim.h"
#include "Component/SpriteComponent.h"

CForeGroundAnim::CForeGroundAnim()
{
}

CForeGroundAnim::CForeGroundAnim(const CForeGroundAnim& anim) :
	CAnimation2D(anim)
{

}

CForeGroundAnim::~CForeGroundAnim()
{
}

void CForeGroundAnim::Start()
{
	CAnimation2D::Start();
}

bool CForeGroundAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("FG_Cloud");

	return true;
}

void CForeGroundAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CForeGroundAnim* CForeGroundAnim::Clone()
{
	return new CForeGroundAnim(*this);
}
