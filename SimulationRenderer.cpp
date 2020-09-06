#include "stdafx.h"
#include "SimulationRenderer.h"
#include "Simulator.h"
#include "ConnectionPt.h"

CSimulationRenderer::CSimulationRenderer()
{
}


CSimulationRenderer::~CSimulationRenderer()
{
}

void CSimulationRenderer::Initialize(LPDIRECT3DDEVICE9 pdev, CSimulator* pSimulator)
{
	m_pdev = pdev;
	m_pSimulator = pSimulator;

	int iOneLineVertexCount = m_pSimulator->GetOneLinePtCount();

	m_pdev->CreateVertexBuffer(iOneLineVertexCount*iOneLineVertexCount*sizeof(Vertex), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL);
	m_pdev->CreateIndexBuffer((iOneLineVertexCount - 1) *(iOneLineVertexCount - 1) * 2 * sizeof(Index), D3DUSAGE_WRITEONLY, (D3DFORMAT)Index::FVF, D3DPOOL_DEFAULT, &m_pIB, NULL);

	std::vector<CConnectionPt*>& connectionPtList = m_pSimulator->GetConnectionPtList();

	Vertex* pVertices;
	m_pVB->Lock(0, iOneLineVertexCount*iOneLineVertexCount*sizeof(Vertex), (void**)&pVertices, 0);

	for (size_t i = 0; i < connectionPtList.size(); i++)
		pVertices[i].SetTexCoord(D3DXVECTOR2((float)(i % iOneLineVertexCount) / (float)iOneLineVertexCount, (float)(i / iOneLineVertexCount) / (float)iOneLineVertexCount));

	m_pVB->Unlock();

	Index* pIndices;
	m_pIB->Lock(0, (iOneLineVertexCount - 1) *(iOneLineVertexCount - 1) * 2 * sizeof(Index), (void**)&pIndices, 0);

	for (int i = 0; i < iOneLineVertexCount - 1; i++)
	{
		for (int j = 0; j < iOneLineVertexCount - 1; j++)
		{
			pIndices->Set(iOneLineVertexCount*i + j, iOneLineVertexCount*i + j + 1, iOneLineVertexCount*(i + 1) + j);
			pIndices++;
			pIndices->Set(iOneLineVertexCount*(i + 1) + j, iOneLineVertexCount*i + j + 1, iOneLineVertexCount*(i + 1) + j + 1);
			pIndices++;
		}
	}
	
	m_pIB->Unlock();

	D3DXCreateTextureFromFile(m_pdev, _T("windows10.jpg"), &m_pDiffuseTex);
}

void CSimulationRenderer::Release()
{

}

void CSimulationRenderer::Update()
{
	int iOneLineVertexCount = m_pSimulator->GetOneLinePtCount();
	std::vector<CConnectionPt*>& connectionPtList = m_pSimulator->GetConnectionPtList();

	Vertex* pVertices;
	m_pVB->Lock(0, iOneLineVertexCount*iOneLineVertexCount*sizeof(Vertex), (void**)&pVertices, 0);

	for (size_t i = 0; i < connectionPtList.size(); i++)
		pVertices[i].SetPosition(connectionPtList[i]->GetPosition());

	m_pVB->Unlock();
}

void CSimulationRenderer::Render()
{
	int iOneLineVertexCount = m_pSimulator->GetOneLinePtCount();

	//m_pdev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pdev->SetTexture(0, m_pDiffuseTex);
	m_pdev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	m_pdev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pdev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	m_pdev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pdev->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
	m_pdev->SetFVF(Vertex::FVF);
	m_pdev->SetIndices(m_pIB);
	m_pdev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, iOneLineVertexCount*iOneLineVertexCount, 0, (iOneLineVertexCount - 1)*(iOneLineVertexCount - 1) * 2);
	m_pdev->SetRenderState(D3DRS_LIGHTING, TRUE);
}
