#include "stdafx.h"
#include "ConnectionPt.h"


CConnectionPt::CConnectionPt(float fValue)
{
	m_fValue = fValue;
}


CConnectionPt::~CConnectionPt()
{
}

void CConnectionPt::Simulate(float fDT, D3DXVECTOR3& fGravitation, float fAirFrictionConstant)
{
	ApplyForce(m_fValue*fGravitation);
	ApplyForce(-m_v3Velocity*fAirFrictionConstant);

	m_v3Velocity += (m_v3Force / m_fValue)*fDT;
	m_v3Pos += m_v3Velocity*fDT;
}
