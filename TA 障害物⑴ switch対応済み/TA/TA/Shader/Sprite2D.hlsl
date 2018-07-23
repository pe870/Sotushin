//�O���[�o���ϐ�.
//ø�����ڼ޽�� t(n).
Texture2D		g_texColor	:	register(t0);

//����ׂ�ڼ޽��@s(n).
SamplerState	g_samLiner	:	register(s0);

//�R���X�^���g�o�b�t�@.
cbuffer	global	:	register(b0)
{
	matrix	g_mW			: packoffset(c0);
	float	g_fViewPortW	: packoffset(c4);
	float	g_fViewPortH	: packoffset(c5);
	float	g_fAlpha		: packoffset(c6);
}

//���_�V�F�[�_�̏o�̓p�����[�^.
struct VS_OUTPUT
{
	float4	Pos	:	SV_Position;
	float2	UV  :	TEXCOORD;
};

//���_�V�F�[�_.
VS_OUTPUT VS_Main(float4 Pos : POSITION, float2 UV : TEXCOORD)
{
	//������.
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, g_mW);

	//�X�N���[�����W�ɍ��킹��v�Z.
	output.Pos.x = (output.Pos.x / g_fViewPortW) * 2.0f - 1.0f;
	output.Pos.y = 1.0f - (output.Pos.y / g_fViewPortH) * 2.0f;

	output.UV = UV;

	return output;
}

//�߸�ټ����.
float4 PS_Main(VS_OUTPUT input) : SV_Target
{
	float4 color = g_texColor.Sample(g_samLiner, input.UV);
	color.a *= g_fAlpha;	//�A���t�@�l���|�����킹��(���ߎ��̂�h������).
	return color;
}