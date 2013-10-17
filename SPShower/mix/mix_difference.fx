////////////////////////////////////////////////
// Name: mix_difference.mm
// Author:方枫杰
// Date:2012-8-14
// Desc:差值，将要混合图层双方的RGB值中每个值分别进行比较，
// 用高值减去低值作为合成后的颜色,与白色混合将反转基色值，与黑色混合无变化。
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

	out_color.r = abs(target_tex_color.r - tex_color.r);
	out_color.g = abs(target_tex_color.g - tex_color.g);
	out_color.b = abs(target_tex_color.b - tex_color.b);
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}