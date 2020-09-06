#pragma once

class CConnectionPt;

class CConnectionSpring
{
	CConnectionPt* m_pConnectionPt1;
	CConnectionPt* m_pConnectionPt2;

	float m_fSpringConstant;
	float m_fSpringLength;
	float m_fFrictionConstant;

public:
	CConnectionSpring(CConnectionPt* pConnectionPt1, CConnectionPt* pConnectionPt2, FLOAT fSpringConstant, FLOAT fSpringLength, FLOAT fFrictionConstant);
	~CConnectionSpring();

	void Simulate();
};

