#include "TutorialSceneAnim.h"
#include "Component/SpriteComponent.h"

CTutorialSceneAnim::CTutorialSceneAnim()
{
}

CTutorialSceneAnim::CTutorialSceneAnim(const CTutorialSceneAnim& anim) :
	CAnimation2D(anim)
{

}

CTutorialSceneAnim::~CTutorialSceneAnim()
{
}

void CTutorialSceneAnim::Start()
{
	CAnimation2D::Start();
}

bool CTutorialSceneAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	// Tutorial BackGround
	AddAnimationSequence2D("BG_Tutorial", false);
	AddAnimationSequence2D("FG_Tutorial", false);
	AddAnimationSequence2D("Parry_Off", false);
	AddAnimationSequence2D("Parry_On", false);
	AddAnimationSequence2D("Pyramid_Body", false);
	AddAnimationSequence2D("Pyramid_Head", false);
	AddAnimationSequence2D("TutorialMap", false);
	AddAnimationSequence2D("FieryFrolic", false);

	return true;
}

void CTutorialSceneAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CTutorialSceneAnim* CTutorialSceneAnim::Clone()
{
	return new CTutorialSceneAnim(*this);
}
