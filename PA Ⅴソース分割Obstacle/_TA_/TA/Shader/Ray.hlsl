//グローバル変数.
cbuffer global
{
	matrix	g_mWVP;		//World,View,Projの変換行列.
	float4	g_vColor;	//色.
};

//バーテックスシェーダ.
float4 VS_Main(float4 Pos:POSITION) :SV_Position
{
	Pos = mul(Pos, g_mWVP);
	return Pos;
}

//ピクセルシェーダ.
float4 PS_Main(float4 Pos:SV_POSITION) :SV_Target
{
	return g_vColor;
}
