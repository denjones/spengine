////////////////////////////////////////////////
// Name: mix_screen.mm
// Author:�����
// Date:2012-8-14
// Desc:��ɫ(��Ļ)���鿴ÿ��ͨ������ɫ��Ϣ�����ɫ�Ļ���ɫ���ɫ��ϡ�
// ���ɫ���ǽ�������ɫ���ú�ɫ����ʱ��ɫ���ֲ��䣬�ð�ɫ���˽�������ɫ��
///////////////////////////////////////////////

sampler tex : register(S0);
texture Tex1;

sampler targetTex = sampler_state
{
	Texture = (Tex1);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 tex_color = tex2D(tex, texCoord);
	float4 target_tex_color = tex2D(targetTex, texCoord);

    return (1 - (1 - tex_color) * (1 - target_tex_color));
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}