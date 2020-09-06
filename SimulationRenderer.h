#pragma once
class CSimulator;

class CSimulationRenderer
{
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DCOLOR color;
		D3DXVECTOR2 t;

		Vertex(D3DXVECTOR3&& _pos, D3DXVECTOR2&& _t, D3DCOLOR&& _color = D3DCOLOR_RGBA(0, 0, 255, 255))
		{
			pos = _pos; t = _t; color = _color;
		}

		void SetTexCoord(D3DXVECTOR2&& _t){ t = _t; }
		void SetPosition(D3DXVECTOR3&& _pos) { pos = _pos; }

		enum { FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1) };
	};

	struct Index
	{
		WORD _0, _1, _2;

		void Set(WORD a, WORD b, WORD c){ _0 = a, _1 = b, _2 = c; }

		enum { FVF = (D3DFMT_INDEX16) };
	};

	LPDIRECT3DDEVICE9 m_pdev;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	LPDIRECT3DTEXTURE9	 m_pDiffuseTex;

	CSimulator* m_pSimulator;

public:
	CSimulationRenderer();
	~CSimulationRenderer();

	void Initialize(LPDIRECT3DDEVICE9 pdev, CSimulator* pSimulator);
	void Release();

	void Update();
	void Render();
};

