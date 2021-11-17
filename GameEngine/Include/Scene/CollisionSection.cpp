
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

    //	// ���� �����ӿ� �浹�Ǿ��� �浹ü���� üũ�غ���.
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

            // ���� �����ӿ� �ٸ� ���ǿ��� ���� �浹ó���� �غ����� ���� ���
            if (Src->CheckCurrentFrameCollision(Dest))
                continue;

            CollisionProfile* SrcProfile = Src->GetProfile();
            CollisionProfile* DestProfile = Dest->GetProfile();

            // �ݸ��� ������ Ignore�� ��� �����Ѵ�.
            if (SrcProfile->vecChannel[(int)DestProfile->Channel].Interaction ==
                Collision_Interaction::Ignore ||
                DestProfile->vecChannel[(int)SrcProfile->Channel].Interaction ==
                Collision_Interaction::Ignore)
                continue;

            if (Src->Collision(Dest))
            {
                // ������ �� �浹ü�� �浹�ߴ����� �Ǵ��Ѵ�.
                // �����浹ü�� ���ٸ� ���� �� �浹�� �����Ѵٴ� �ǹ��̴�.
                if (!Src->CheckPrevCollision(Dest))
                {
                    // ���� �浹 ��Ͽ� �߰�
                    Src->AddPrevCollider(Dest);
                    Dest->AddPrevCollider(Src);

                    // Callback �Լ� ȣ��
                    Src->CallCollisionCallback(Collision_State::Begin);
                    Dest->CallCollisionCallback(Collision_State::Begin);
                }

                // �浹 �� �� ���,
                else
                {
                    // ��ĥ���� �Լ� ����
                    Src->CallCollisionCallback(Collision_State::Overlap);
                    Dest->CallCollisionCallback(Collision_State::Overlap);

                    // �ε�ġ�� �ݸ����� ĳ�����̰�, xz�浹�� ����ϰ�, CollisionInteraction�� 
                    if (Dest->GetColliderType() == Collider_Type::Character && Dest->GetOwner()->GetUseBlockMovement()
                        && DestProfile->vecChannel[(int)SrcProfile->Channel].Interaction == Collision_Interaction::Block)
                    {
                        // ���� �ݸ����� ĳ���� �ݸ����� ��� �и鿡 ��ġ���ִ��� �Ǵ�
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

                        // �������� ������ �̵��� �� �ִ� ���
                        if (abs(Vertical) > abs(Horizontal))
                        {
                            // �����̵� �̶�� block Ȯ��
                            if (MovePos.x > 0 || MovePos.x < 0 || MovePos.x == 0)
                            {
                                // ���� �����ӿ��� ������ �Ÿ����� ��������ٸ� �ڽ� �������� �̵��� ��
                                if (abs(PrevDistance.x) > abs(Distance.x))
                                {
                                    Dest->GetOwner()->SetWorldPos(Dest->GetOwner()->GetPrevWorldPos());

                                }
                            }
                        }

                        // �������� �̵��� �� �ִ� ���
                        if (abs(Vertical) < abs(Horizontal))
                        {
                            if (MovePos.y > 0 || MovePos.y < 0)
                            {
                                // ���� �����ӿ��� ������ �Ÿ����� ��������ٸ� �ڽ� �������� �̵��� ��
                                if (abs(PrevDistance.y) > abs(Distance.y))
                                {
                                    Dest->GetOwner()->SetWorldPos(Dest->GetOwner()->GetPrevWorldPos());

                                }
                            }
                        }

                    }
                }
            }

            // �浹�� �ƴ϶�� ������ �浹�Ǿ��� ��ü������ �Ǵ��Ѵ�.
            // ������ �浹�Ǿ��� ��ü��� �ε��� ��ü�� ���� �������ٴ� �ǹ��̴�.
            else if (Src->CheckPrevCollision(Dest))
            {
                // �浹��Ͽ� ���� ������ ���� ��������� �������־�� ��
                Src->SetHitResult(Dest, Src->GetWorldPos());
                Dest->SetHitResult(Src, Dest->GetWorldPos());

                // Callback �Լ� ȣ��
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
