#include "FG_LoadingAnim.h"
#include "Component/SpriteComponent.h"

FG_LoadingAnim::FG_LoadingAnim()
{
}

FG_LoadingAnim::FG_LoadingAnim(const FG_LoadingAnim& anim) :
	CAnimation2D(anim)
{

}

FG_LoadingAnim::~FG_LoadingAnim()
{
}

void FG_LoadingAnim::Start()
{
	CAnimation2D::Start();
}

bool FG_LoadingAnim::Init()
{
	if (!CAnimation2D::Init())
		return false;

	// Title BackGround
	AddAnimationSequence2D("Loading");

	return true;
}

void FG_LoadingAnim::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

FG_LoadingAnim* FG_LoadingAnim::Clone()
{
	return new FG_LoadingAnim(*this);
}
