////////////////////////////////////////////////
// Name: mix_linear_light.mm
// Author:�����
// Date:2012-8-14
// Desc:���ι⣬����ϲ���ɫ����Դ�����ȸ������Իң�50%�ң���
// �����������ȵķ�����ʹ�û����������֮�ý������ȵķ�����ʹ����䰵��
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

	float4 out_color = target_tex_color;

	out_color.r = target_tex_color.r + 2 * tex_color.r - 1;
	out_color.g = target_tex_color.g + 2 * tex_color.g - 1;
	out_color.b = target_tex_color.b + 2 * tex_color.b - 1;
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}