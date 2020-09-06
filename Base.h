#pragma once
#include "Simulator.h"
#include "SimulationRenderer.h"
//class CSimulator;
//class CSimulationRenderer;

class CBase
{
	LPDIRECT3D9 m_pd3d;
	LPDIRECT3DDEVICE9 m_pdev;
	HWND m_hWnd;

	CSimulator m_Simulator;
	CSimulationRenderer m_SimulationRenderer;

	static CBase* m_pThis;

public:
	CBase();
	~CBase();

	HRESULT  Initialize(HWND hWnd);
	HRESULT InitializeD3D(HWND hWnd);

	void Release();

	void Update();
	void Render();

	static CBase& GetThis() { return *m_pThis; }
};

inline CBase& GetBase(){ return CBase::GetThis(); }