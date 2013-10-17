////////////////////////////////////////////////
// Name: mix_overlay.mm
// Author:方枫杰
// Date:2012-8-14
// Desc:叠加，根据底层的色彩决定将目标层的哪些像素以相乘模式合成，
// 哪些像素以屏幕模式合成。合成后有些区域图变暗有些区域变亮。
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

	if(target_tex_color.r <= 0.5)
		out_color.r = 2.0 * tex_color.r * target_tex_color.r; 
	else if(target_tex_color.r > 0.5)
		out_color.r = 1 - 2.0 * (1 - tex_color.r) * (1 - target_tex_color.r);
		

	if(target_tex_color.g <= 0.5)
		out_color.g = 2.0 * tex_color.g * target_tex_color.g; 
	else if(target_tex_color.g > 0.5)
		out_color.g = 1 - 2.0 * (1 - tex_color.g) * (1 - target_tex_color.g);
		

	if(target_tex_color.b <= 0.5)
		out_color.b = 2.0 * tex_color.b * target_tex_color.b; 
	else if(target_tex_color.b > 0.5)
		out_color.b = 1 - 2.0 * (1 - tex_color.b) * (1 - target_tex_color.b);
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}