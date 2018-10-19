//�O���[�o���ϐ�.
cbuffer global
{
	matrix	g_mWVP;		//World,View,Proj�̕ϊ��s��.
	float4	g_vColor;	//�F.
};

//�o�[�e�b�N�X�V�F�[�_.
float4 VS_Main(float4 Pos:POSITION) :SV_Position
{
	Pos = mul(Pos, g_mWVP);
	return Pos;
}

//�s�N�Z���V�F�[�_.
float4 PS_Main(float4 Pos:SV_POSITION) :SV_Target
{
	return g_vColor;
}
