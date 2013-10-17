////////////////////////////////////////////////
// Name: mix_hard.mm
// Author:方枫杰
// Date:2012-8-14
// Desc:实色混合，当混合两个图层以后结果是：亮色更加亮了，暗色更加暗了，
// 降低填充不透明度建立多色调分色或者阈值，降低填充不透明度能使混合结果变得柔和。
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

	if(tex_color.r < (1 - target_tex_color.r))
		out_color.r = 0; 
	else if(tex_color.r > (1 - target_tex_color.r))
		out_color.r = 1;	

	if(tex_color.g < (1 - target_tex_color.g))
		out_color.g = 0; 
	else if(tex_color.g > (1 - target_tex_color.g))
		out_color.g = 1;
		
	if(tex_color.b < (1 - target_tex_color.b))
		out_color.b = 0; 
	else if(tex_color.b > (1 - target_tex_color.b))
		out_color.b = 1;
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}