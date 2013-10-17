////////////////////////////////////////////////
// Name: mix_darken.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:变暗，将两像素的RGB值进行比较后，取低值成为混合后的颜色，
// 因而总的颜色灰度级降低，造成变暗的效果。
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

	if(tex_color.r < target_tex_color.r)
		target_tex_color.r = tex_color.r;

	if(tex_color.g < target_tex_color.g)
		target_tex_color.g = tex_color.g;
	
	if(tex_color.b < target_tex_color.b)
		target_tex_color.b = tex_color.b;
	
	return target_tex_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}