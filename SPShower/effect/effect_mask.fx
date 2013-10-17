////////////////////////////////////////////////
// Name: effect_mask_soft.ef
// Author:�˳���
// Date:2012-08-13
// Desc:���ݴ����level��������͸���ĳ̶ȣ����gapΪ0~0.2����ȫ͸���������0.2~0.8�Ͱ�͸����0.8~1��ȫ��͸��
///////////////////////////////////////////////

sampler tex : register(S0);
float width : register(C0);
float height : register(C1);
float transitionPosition : register(C2);
float level : register(C3);

texture Tex1;

sampler effectTex = sampler_state
{
	Texture = (Tex1);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float pos = transitionPosition;

	float gap = 0.5 - level / 10 * 0.5;

	//pos = -1 + gap + pos * (2 - 2 * gap);

	float4 tex_color = tex2D(tex, texCoord);

	float mask_color = tex2D(effectTex, texCoord).r + 1 - gap - pos * ( 2 - 2 * gap);

	if(mask_color > 1 - gap)
	{
		mask_color = 1;
	}
	else if(mask_color <= gap)
	{
		mask_color = 0;
	}
	else
	{
		mask_color = (mask_color - gap) / (1 - 2 * gap);
	}

    return tex_color * mask_color;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}