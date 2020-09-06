#pragma once
#include <vector>

class CConnectionPt;
class CConnectionSpring;

class CSimulator
{
	int m_iNumOfOneLinePt;

	std::vector<CConnectionPt*> m_ConnectionPtList;
	std::vector<CConnectionSpring*> m_HConnectionSpringList;
	std::vector<CConnectionSpring*> m_VConnectionSpringList;

	float m_fSpringLength;
	D3DXVECTOR3 m_v3Gravitation;
	float m_fAirFrictionConstant;

public:
	CSimulator();
	~CSimulator();

	bool Initialize(int iNumOfOneLinePt, float fPtValue, float fSpringConstant, float fSpringLength, float fSpringFrictionConstant, D3DXVECTOR3&& v3Gravitation, float fAirFrictionConstant);
	void Release();

	void Simulate(float fDT);

	int GetOneLinePtCount() { return m_iNumOfOneLinePt; }
	std::vector<CConnectionPt*>& GetConnectionPtList(){ return m_ConnectionPtList; }
};

