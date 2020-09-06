#include "stdafx.h"
#include "Simulator.h"

#include "ConnectionPt.h"
#include "ConnectionSpring.h"

CSimulator::CSimulator()
{
}


CSimulator::~CSimulator()
{
}

bool CSimulator::Initialize(int iNumOfOneLinePt, float fPtValue, float fSpringConstant, float fSpringLength, float fSpringFrictionConstant, D3DXVECTOR3&& v3Gravitation, float fAirFrictionConstant)
{
	m_iNumOfOneLinePt = iNumOfOneLinePt;
	m_fSpringLength = fSpringLength;
	m_v3Gravitation = v3Gravitation;
	m_fAirFrictionConstant = fAirFrictionConstant;

	m_ConnectionPtList.reserve(iNumOfOneLinePt*iNumOfOneLinePt);

	for (int i = 0; i < iNumOfOneLinePt; i++)
	{
		for (int j = 0; j < iNumOfOneLinePt; j++)
		{
			CConnectionPt* pTempPt = new CConnectionPt(fPtValue);
			m_ConnectionPtList.push_back(pTempPt);

			pTempPt->SetPosition(D3DXVECTOR3(j*fSpringLength - iNumOfOneLinePt / 2 * fSpringLength, -i*fSpringLength + iNumOfOneLinePt / 2 * fSpringLength + 0.3, 0));
			pTempPt->SetVelocity(D3DXVECTOR3(0, 0, 0));
		}
	}

	//수평인 직선 개수
	int iNumOfHorziontalLine = (iNumOfOneLinePt - 1)*iNumOfOneLinePt;
	
	//수직인 직선 개수
	int iNumOfVerticalLine = iNumOfOneLinePt*(iNumOfOneLinePt - 1);

	int iNumOfTotal = iNumOfHorziontalLine + iNumOfVerticalLine;

	m_HConnectionSpringList.reserve(iNumOfHorziontalLine);
	m_VConnectionSpringList.reserve(iNumOfVerticalLine);

	int iHCount = (iNumOfOneLinePt - 1);
	int iVCount = iNumOfOneLinePt;

	//수평인 직선 생성
	for (int i = 0; i < iVCount; i++)
	{
		for (int j = 0; j < iHCount; j++)
		{
			CConnectionSpring* pTempSpring = new CConnectionSpring(m_ConnectionPtList[i*iNumOfOneLinePt + j], m_ConnectionPtList[i*iNumOfOneLinePt + j + 1], fSpringConstant, fSpringLength, fSpringFrictionConstant);
			m_HConnectionSpringList.push_back(pTempSpring);
		}
	}

	iHCount = iNumOfOneLinePt;
	iVCount = (iNumOfOneLinePt - 1);

	//수직인 직선 생성
	for (int i = 0; i < iVCount; i++)
	{
		for (int j = 0; j < iHCount; j++)
		{
			CConnectionSpring* pTempSpring = new CConnectionSpring(m_ConnectionPtList[i*iNumOfOneLinePt + j], m_ConnectionPtList[(i + 1)*iNumOfOneLinePt + j], fSpringConstant, fSpringLength, fSpringFrictionConstant);
			m_VConnectionSpringList.push_back(pTempSpring);
		}
	}

	return true;
}

void CSimulator::Release()
{

}

void CSimulator::Simulate(float fDT)
{
	fDT = 0.0015f;

	for (auto pConnectionPt : m_ConnectionPtList)
		pConnectionPt->SetForce(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	for (auto pConnectionSpring : m_HConnectionSpringList)
		pConnectionSpring->Simulate();
		
	for (auto pConnectionSpring : m_VConnectionSpringList)
		pConnectionSpring->Simulate();
	
	for (auto pConnectionPt : m_ConnectionPtList)
		pConnectionPt->Simulate(fDT, m_v3Gravitation, m_fAirFrictionConstant);

	m_ConnectionPtList[0]->SetPosition(D3DXVECTOR3(-m_iNumOfOneLinePt / 2 * m_fSpringLength, m_iNumOfOneLinePt / 2 * m_fSpringLength + 0.3, 0));
	m_ConnectionPtList[0]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_ConnectionPtList[m_iNumOfOneLinePt - 1]->SetPosition(D3DXVECTOR3(m_iNumOfOneLinePt / 2 * m_fSpringLength, m_iNumOfOneLinePt / 2 * m_fSpringLength + 0.3, 0));
	m_ConnectionPtList[m_iNumOfOneLinePt - 1]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
