#ifndef CRAY_H
#define CRAY_H

#include "CCommon.h"	//���ʃN���X.

class clsRay : public clsCommon	//���ʃN���X���p��.
{
	public:

		struct SPRITESHADER_CBUFFER
		{
			D3DXMATRIX	mWVP;	//ܰ���,�ޭ�,�ˉe�̍����ϊ��s��.
			D3DXVECTOR4	vColor;	//�װ(RGBA�̌^�ɍ��킹��).
		};

		clsRay(){};
		~clsRay(){};

		//������.
		HRESULT	Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

		//�V�F�[�_������.
		HRESULT InitShader();

	private:
		ID3D11VertexShader* m_pVertexShader;	//���_�����.
		ID3D11InputLayout*	m_pVertexLayout;	//���_ڲ���.
		ID3D11PixelShader*	m_pPixelShader;		//�߸�ټ����.
		ID3D11Buffer*		m_pConstantBuffer;	//�ݽ����ޯ̧.

		//�����ق��Ƃɗp��.
		ID3D11Buffer*		m_pVertexBuffer;	//���_�ޯ̧.

};


#endif
