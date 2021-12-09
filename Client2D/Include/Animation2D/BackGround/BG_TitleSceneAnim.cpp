#include "BG_TitleSceneAnim.h"
#include "Component/SpriteComponent.h"

BG_TitleSceneAnim::BG_TitleSceneAnim()
{
}

BG_TitleSceneAnim::BG_TitleSceneAnim(const BG_TitleSceneAnim& anim) :
	CAnimation2D(anim)
{

}

BG_TitleSceneAnim::~BG_TitleSceneAnim()
{
}

void BG_TitleSceneAnim::Start()
{
	CAnimation2D::Start();
}

bool BG_TitleSceneAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	// Title BackGround
	AddAnimationSequence2D("BG_TitleScene", false);
	AddAnimationSequence2D("BG_Cuphead", false);

	return true;
}

void BG_TitleSceneAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

BG_TitleSceneAnim* BG_TitleSceneAnim::Clone()
{
	return new BG_TitleSceneAnim(*this);
}
