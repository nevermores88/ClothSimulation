#include "stdafx.h"
#include "Base.h"

CBase* CBase::m_pThis = nullptr;
CBase g_Base;

CBase::CBase()
{
	m_pThis = this;
}


CBase::~CBase()
{
}

HRESULT CBase::Initialize(HWND hWnd)
{
	if(FAILED(InitializeD3D(hWnd)))
		return E_FAIL;

	/*m_Simulator.Initialize(31, 0.05f, 10000.0f, 0.05f, 0.2f, D3DXVECTOR3(0.0f, -9.8f, 0), 0.02f);*/
	m_Simulator.Initialize(61, 0.05f, 10000.0f, 0.02f, 0.15f, D3DXVECTOR3(0.0f, -9.8f, 0), 0.02f);
	m_SimulationRenderer.Initialize(m_pdev, &m_Simulator);
	
	return S_OK;
}

HRESULT CBase::InitializeD3D(HWND hWnd)
{
	m_hWnd = hWnd;

	if (NULL == (m_pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = 0;

	D3DCAPS9 caps;
	m_pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	DWORD vp = 0;

	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if (FAILED(m_pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, vp, &d3dpp, &m_pdev)))
	{
		return E_FAIL;
	}

	m_pdev->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pdev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return S_OK;
}


void CBase::Release()
{
	if (m_pdev)
		m_pdev->Release();

	if (m_pd3d)
		m_pd3d->Release();
}

void CBase::Update()
{
	if (m_pdev == nullptr)
		return;

	static float fPreviousTime = (float)timeGetTime() * 0.001f;
	float fCurrentTime = (float)timeGetTime() * 0.001f;

	float fDeltaTime = fCurrentTime - fPreviousTime;
	fPreviousTime = fCurrentTime;

	m_Simulator.Simulate(fDeltaTime);
	m_SimulationRenderer.Update();
}

void CBase::Render()
{
	if (m_pdev == nullptr)
		return;

	m_pdev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 128, 200), 1.0f, 0);

	if (!SUCCEEDED(m_pdev->BeginScene()))
		return;

	m_SimulationRenderer.Render();

	m_pdev->EndScene();

	m_pdev->Present(NULL, NULL, NULL, NULL);
}

