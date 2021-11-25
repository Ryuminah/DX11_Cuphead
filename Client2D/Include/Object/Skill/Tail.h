#pragma once
#include "../Skill/Skill.h"

class CTail :
    public CSkill
{
	friend class CScene;

protected:
	CTail();
	CTail(const CTail& obj);
	virtual ~CTail();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider;
	CSharedPtr<CSceneComponent>	m_Rotation;
	class CAnimation2D* m_Animation;

private:
	float	m_TailSpeed;
	float	m_WaitTime;			// �� ������ ����
	float	m_MaxY;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTail* Clone();

public:
	virtual void SkillStart(float DeltaTime);
	virtual void SkillActive(float DeltaTime);	// ��ų�� Ȱ��ȭ �Ǿ����� � ������ �ؾ��ϴ���
	//virtual void SkillEnd(float DeltaTime);	// ��ų�� Ȱ��ȭ �Ǿ����� � ������ �ؾ��ϴ���

};

