
#include "CollisionSection.h"
#include "../Component/Collider.h"
#include "../Input.h"
#include "../GameObject.h"

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
                    // 이전 충돌 목록에 추가
                    Src->AddPrevCollider(Dest);
                    Dest->AddPrevCollider(Src);

                    // Callback 함수 호출
                    Src->CallCollisionCallback(Collision_State::Begin);
                    Dest->CallCollisionCallback(Collision_State::Begin);
                }

                // 충돌 중 일 경우,
                else
                {
                    // 겹칠때의 함수 실행
                    Src->CallCollisionCallback(Collision_State::Overlap);
                    Dest->CallCollisionCallback(Collision_State::Overlap);

                    // 부딪치는 콜리전이 캐릭터이고, xz충돌을 사용하고, CollisionInteraction이 
                    if (Dest->GetColliderType() == Collider_Type::Character && Dest->GetOwner()->GetUseBlockMovement()
                        && DestProfile->vecChannel[(int)SrcProfile->Channel].Interaction == Collision_Interaction::Block)
                    {
                        // 현재 콜리전의 캐릭터 콜리전의 어느 분면에 위치해있는지 판단
                        Vector3 MovePos = Dest->GetWorldPos() - Dest->GetPrevWorldPos();
                        Vector3 Distance = Src->GetWorldPos() - Dest->GetWorldPos();
                        Vector3 PrevDistance = Src->GetPrevWorldPos() - Dest->GetPrevWorldPos();

                        //Vector2 ComparePivot = { abs(Src->GetMax().x - Src->GetMin().x) *0.5f , abs(Src->GetMax().y- Src->GetMin().y) *0.5f};
                        Vector2 ComparePivot = { Src->GetMax().x - Src->GetWorldPos().x ,Src->GetMax().y - Src->GetWorldPos().y };

                        Vector2 TopRight = { Dest->GetMax().x , Dest->GetMax().y };
                        Vector2 TopLeft = { Dest->GetMin().x , Dest->GetMax().y };
                        Vector2 BottomRight = { Dest->GetMax().x , Dest->GetMin().y };
                        Vector2 BottomLeft = { Dest->GetMin().x , Dest->GetMin().y };

                        Vector2 DestPivot[4] = { TopRight, TopLeft, BottomRight, BottomLeft };
                        Vector2 NearPivot = DestPivot[0];

                        for (size_t i = 0; i < 4; ++i)
                        {
                            Vector2 NearDistance = { Src->GetPrevWorldPos().x - NearPivot.x, Src->GetPrevWorldPos().y - NearPivot.y };
                            Vector2 CheckDistance = { Src->GetPrevWorldPos().x - DestPivot[i].x, Src->GetPrevWorldPos().y - DestPivot[i].y };

                            NearPivot = abs(NearDistance.x) + abs(NearDistance.y) <= abs(CheckDistance.x) + abs(CheckDistance.y) ? NearPivot : DestPivot[i];
                        }
                        NearPivot.x -= (Src->GetWorldPos().x);
                        NearPivot.y -= (Src->GetWorldPos().y);

                        float Vertical = abs(ComparePivot.y) - abs(NearPivot.y);
                        float Horizontal = abs(ComparePivot.x) - abs(NearPivot.x);

                        // 수직으로 무조건 이동할 수 있는 경우
                        if (abs(Vertical) > abs(Horizontal))
                        {
                            // 가로이동 이라면 block 확인
                            if (MovePos.x > 0 || MovePos.x < 0 || MovePos.x == 0)
                            {
                                // 이전 프레임에서 움직인 거리보다 가까워졌다면 박스 방향으로 이동한 것
                                if (abs(PrevDistance.x) > abs(Distance.x))
                                {
                                    Dest->GetOwner()->SetWorldPos(Dest->GetOwner()->GetPrevWorldPos());

                                }
                            }
                        }

                        // 수평으로 이동할 수 있는 경우
                        if (abs(Vertical) < abs(Horizontal))
                        {
                            if (MovePos.y > 0 || MovePos.y < 0)
                            {
                                // 이전 프레임에서 움직인 거리보다 가까워졌다면 박스 방향으로 이동한 것
                                if (abs(PrevDistance.y) > abs(Distance.y))
                                {
                                    Dest->GetOwner()->SetWorldPos(Dest->GetOwner()->GetPrevWorldPos());

                                }
                            }
                        }

                    }
                }
            }

            // 충돌이 아니라면 이전에 충돌되었던 물체인지를 판단한다.
            // 이전에 충돌되었던 물체라면 부딪힌 물체가 지금 떨어진다는 의미이다.
            else if (Src->CheckPrevCollision(Dest))
            {
                // 충돌목록에 없기 때문에 직접 판정결과를 셋팅해주어야 함
                Src->SetHitResult(Dest, Src->GetWorldPos());
                Dest->SetHitResult(Src, Dest->GetWorldPos());

                // Callback 함수 호출
                Src->CallCollisionCallback(Collision_State::End);
                Dest->CallCollisionCallback(Collision_State::End);
                
                
                Src->DeletePrevCollider(Dest);
                Dest->DeletePrevCollider(Src);
            }
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
