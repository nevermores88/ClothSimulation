#include "stdafx.h"
#include "ConnectionSpring.h"
#include "ConnectionPt.h"

CConnectionSpring::CConnectionSpring(CConnectionPt* pConnectionPt1, CConnectionPt* pConnectionPt2, FLOAT fSpringConstant, FLOAT fSpringLength, FLOAT fFrictionConstant)
{
	m_pConnectionPt1 = pConnectionPt1;
	m_pConnectionPt2 = pConnectionPt2;

	m_fSpringConstant = fSpringConstant;
	m_fSpringLength = fSpringLength;
	m_fFrictionConstant = fFrictionConstant;
}


CConnectionSpring::~CConnectionSpring()
{
}

void CConnectionSpring::Simulate()
{
	D3DXVECTOR3 v3Vector = m_pConnectionPt1->GetPosition() - m_pConnectionPt2->GetPosition();

	float fLength = D3DXVec3Length(&v3Vector);

	D3DXVECTOR3 v3Force = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (fLength != 0)
		v3Force += -(v3Vector / fLength)*(fLength - m_fSpringLength) * m_fSpringConstant;

	v3Force += -(m_pConnectionPt1->GetVelocity() - m_pConnectionPt2->GetVelocity()) * m_fFrictionConstant;

	m_pConnectionPt1->ApplyForce(v3Force);
	m_pConnectionPt2->ApplyForce(-v3Force);
}
