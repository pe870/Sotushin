#ifndef SPRITE_D_H
#define SPRITE_D_H


#include "cCommon.h"

#define ALIGN16 _declspec(align(16))

struct SPRITE_STATE
{
	float	Width;		//��.
	float	Height;		//����.
	float	U;			//U���W.
	float	V;			//V���W.
};
class clsSprite2D :public clsCommon
{
public://public �O�����籸���\.

	D3DXVECTOR3		m_vPos;	//�ʒu.

	int				m_AnimCount;	//�J�E���^
	bool			m_DispFlag;		//�\���t���O

	float			m_Alpha;		//��̧�l(�ő�l��1.0).

	clsSprite2D();	//�ݽ�׸�.
	~clsSprite2D();	//�޽�׸�.

	HRESULT Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11,
				LPSTR fileName,const SPRITE_STATE& ss);
	HRESULT InitShader();
	HRESULT InitModel(float Width,float Height,float U,float V);
	//�e�N�X�`���쐬.
	HRESULT	CreateTexture(LPSTR fileName, ID3D11ShaderResourceView** pTexture);

	void Render();


	//-----------------------------------------------
	//	�\����.
	//-----------------------------------------------
	//�ݽ����ޯ̧�̱��ؑ��̒�`(Simple.hlsl).
	//������ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
	struct SPRITESHADER_CBUFFER
	{
		ALIGN16 D3DMATRIX	mW;					//���[���h�s��.
		ALIGN16 float		fViewPortWidth;		//�r���[�|�[�g��.
		ALIGN16 float		fViewPortHeight;	//�r���[�|�[�g����
		ALIGN16 float		fAlpha;				//�A���t�@�l(���߂Ŏg�p����).

	};
	//���_�̍\����.
	struct SpriteVertex
	{
		D3DXVECTOR3 vPos;	//�ʒu.
		D3DXVECTOR2 vTex;	//ø������W(UV���W).
	};

private:

	ID3D11VertexShader* m_pVertexShader;	//���_�����.
	ID3D11InputLayout*	m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*	m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*		m_pConstantBuffer;	//�ݽ����ޯ̧.
	ID3D11Buffer*		m_pVertexBuffer;	//���_�ޯ̧.

	ID3D11SamplerState*	m_pSampleLinear;	//ø����̻����.
	// ø����Ɋe��̨����������.
	ID3D11ShaderResourceView* m_pTexture;	//ø���.


};





#endif