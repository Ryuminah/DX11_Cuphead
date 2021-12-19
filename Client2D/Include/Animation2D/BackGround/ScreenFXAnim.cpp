#include "ScreenFXAnim.h"
#include "Component/SpriteComponent.h"

CScreenFXAnim::CScreenFXAnim()
{
}

CScreenFXAnim::CScreenFXAnim(const CScreenFXAnim& anim) :
	CAnimation2D(anim)
{
}

CScreenFXAnim ::~CScreenFXAnim()
{
}

void CScreenFXAnim::Start()
{
	CAnimation2D::Start();
}

bool CScreenFXAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	// Phase1
	AddAnimationSequence2D("Screenfx");
	ChangeAnimation("Screenfx");

	return true;
}

void CScreenFXAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CScreenFXAnim* CScreenFXAnim::Clone()
{
	return new CScreenFXAnim(*this);
}
