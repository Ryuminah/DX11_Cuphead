
#include "CollisionSection.h"
#include "../Component/Collider.h"
#include "../Input.h"

CCollisionSection::CCollisionSection()
{
	m_vecCollider.reserve(300);
}

CCollisionSection::~CCollisionSection()
{
}

bool CCollisionSection::Init(int IndexX, int IndexY, int IndexZ, int Index, 
	const Vector3& SectionSize, const Vector3& SectionTotalSize)
{
	m_IndexX = IndexX;
	m_IndexY = IndexY;
	m_IndexZ = IndexZ;
	m_Index = Index;
	m_SectionSize = SectionSize;
	m_SectionTotalSize = SectionTotalSize;

	return true;
}

void CCollisionSection::SetSectionMin(const Vector3& Min)
{
	m_Min = Min;
}

void CCollisionSection::SetSectionMax(const Vector3& Max)
{
	m_Max = Max;
}

void CCollisionSection::AddCollider(CCollider* Collider)
{
	m_vecCollider.push_back(Collider);

	Collider->AddSectionIndex(m_Index);
}

void CCollisionSection::Clear()
{
	m_vecCollider.clear();
}

void CCollisionSection::Collision(float DeltaTime)
{
	size_t	Size = m_vecCollider.size();

	//for (size_t i = 0; i < Size; ++i)
	//{
	//	CCollider* Collider = m_vecCollider[i];

	//	if (Collider->GetCurrentSectionCheck())
	//		continue;

	//	Collider->CurrentSectionCheck();

	//	// 이전 프레임에 충돌되었던 충돌체들을 체크해본다.
	//	Collider->CheckPrevColliderSection();
	//}


	if (Size < 2)
		return;

	for (size_t i = 0; i < Size - 1; ++i)
	{
		CCollider* Src = m_vecCollider[i];

		for (size_t j = i + 1; j < Size; ++j)
		{
			CCollider* Dest = m_vecCollider[j];

			// 현재 프레임에 다른 섹션에서 둘이 충돌처리를 해본적이 있을 경우
			if (Src->CheckCurrentFrameCollision(Dest))
				continue;

			CollisionProfile* SrcProfile = Src->GetProfile();
			CollisionProfile* DestProfile = Dest->GetProfile();

			// 콜리전 반응이 Ignore일 경우 무시한다.
			if (SrcProfile->vecChannel[(int)DestProfile->Channel].Interaction ==
				Collision_Interaction::Ignore ||
				DestProfile->vecChannel[(int)SrcProfile->Channel].Interaction ==
				Collision_Interaction::Ignore)
				continue;

			if (Src->Collision(Dest))
			{
				// 이전에 이 충돌체와 충돌했는지를 판단한다.
				// 이전충돌체에 없다면 지금 막 충돌을 시작한다는 의미이다.
				if (!Src->CheckPrevCollision(Dest))
				{
					Src->AddPrevCollider(Dest);
					Dest->AddPrevCollider(Src);

					// Callback 함수 호출
					Src->CallCollisionCallback(Collision_State::Begin);
					Dest->CallCollisionCallback(Collision_State::Begin);
				}
			}

			// 충돌이 아니라면 이전에 충돌되었던 물체인지를 판단한다.
			// 이전에 충돌되었던 물체라면 부딪힌 물체가 지금 떨어진다는 의미이다.
			else if (Src->CheckPrevCollision(Dest))
			{
				Src->DeletePrevCollider(Dest);
				Dest->DeletePrevCollider(Src);

				// Callback 함수 호출
				Src->CallCollisionCallback(Collision_State::End);
				Dest->CallCollisionCallback(Collision_State::End);
			}

			// 콜리전의 충돌 판정이 전부 끝난 이후.
			
		}
	}
}

CCollider* CCollisionSection::CollisionMouse(bool Is2D, float DeltaTime)
{
	if (Is2D)
	{
		Vector2	MousePos = CInput::GetInst()->GetMouse2DWorldPos();

		size_t	Size = m_vecCollider.size();

		if (Size > 1)
		{
			qsort(&m_vecCollider[0], Size, (size_t)sizeof(CCollider*),
				CCollisionSection::SortY);
		}

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecCollider[i]->CollisionMouse(MousePos))
				return m_vecCollider[i];
		}
	}

	else
	{
	}

	return nullptr;
}

int CCollisionSection::SortY(const void* Src, const void* Dest)
{
	CCollider* SrcCollider = *((CCollider**)Src);
	CCollider* DestCollider = *((CCollider**)Dest);

	float	SrcY = SrcCollider->GetWorldPos().y;
	float	DestY = SrcCollider->GetWorldPos().y;

	if (SrcY < DestY)
		return -1;

	else if (SrcY > DestY)
		return 1;

	return 0;
}

int CCollisionSection::SortZ(const void* Src, const void* Dest)
{
	return 0;
}
