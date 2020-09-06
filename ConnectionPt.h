#pragma once
class CConnectionPt
{
	float m_fValue;

	D3DXVECTOR3 m_v3Pos;
	D3DXVECTOR3 m_v3Velocity;
	D3DXVECTOR3 m_v3Force;

public:
	CConnectionPt(float fValue);
	~CConnectionPt();

	void ApplyForce(D3DXVECTOR3& v3Force){ m_v3Force += v3Force; };
	void Simulate(float fDT, D3DXVECTOR3& fGravitation, float fAirFrictionConstant);

	void SetForce(D3DXVECTOR3&& v3Force){ m_v3Force = v3Force; };
	void SetPosition(D3DXVECTOR3&& v3Pos){ m_v3Pos = v3Pos; }
	void SetVelocity(D3DXVECTOR3&& v3Velocity){ m_v3Velocity = v3Velocity; }

	D3DXVECTOR3 GetPosition(){ return m_v3Pos; }
	D3DXVECTOR3 GetVelocity(){ return m_v3Velocity; }
};

