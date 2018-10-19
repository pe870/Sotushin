#ifndef CRAY_H
#define CRAY_H

#include "CCommon.h"	//共通クラス.

class clsRay : public clsCommon	//共通クラスを継承.
{
	public:

		struct RAYSHADER_CBUFFER
		{
			D3DXMATRIX	mWVP;	//ﾜｰﾙﾄﾞ,ﾋﾞｭｰ,射影の合成変換行列.
			D3DXVECTOR4	vColor;	//ｶﾗｰ(RGBAの型に合わせる).
		};

		//頂点構造体.
		struct RAY_VERTEX
		{
			D3DXVECTOR3 vPos;	//位置.

		};
		//ﾚｲ構造体.
		struct RAY
		{
			D3DXVECTOR3	vPoint[2];	//始点と終点.
			D3DXVECTOR3 vDirection;	//方向.
			D3DXVECTOR3 vPos;		//位置;
			FLOAT		Yaw;		//Y軸回転値.
			RAY()
			{
				ZeroMemory(this, sizeof(RAY));
			}
		};


		clsRay();
		~clsRay();

		//初期化.
		HRESULT	Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

		//シェーダ初期化.
		HRESULT InitShader();


		//レイ初期化.
		HRESULT InitModel();

		//描画.
		void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);
		//解放.
		HRESULT Release();
		
		//レイ構造体.
		RAY					m_Ray;

	private:
		ID3D11VertexShader* m_pVertexShader;	//頂点ｼｪｰﾀﾞ.
		ID3D11InputLayout*	m_pVertexLayout;	//頂点ﾚｲｱｳﾄ.
		ID3D11PixelShader*	m_pPixelShader;		//ﾋﾟｸｾﾙｼｪｰﾀﾞ.
		ID3D11Buffer*		m_pConstantBuffer;	//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧ.

		//↓ﾓﾃﾞﾙごとに用意.
		ID3D11Buffer*		m_pVertexBuffer;	//頂点ﾊﾞｯﾌｧ.


};


#endif
