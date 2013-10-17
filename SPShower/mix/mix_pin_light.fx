////////////////////////////////////////////////
// Name: mix_pin_light.mm
// Author:方枫杰
// Date:2012-8-14
// Desc:点光，如果混合色（光源）比50%灰色亮，则替换比混合色暗的像素，而不改变比混合色亮的像素。
// 如果混合色比50%灰色暗，则替换比混合色亮的像素，而不改变比混合色暗的像素。
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

	if(target_tex_color.r < (2 * tex_color.r - 1))
		out_color.r = 2 * tex_color.r - 1; 
	else if(target_tex_color.r > (2 * tex_color.r - 1) && target_tex_color.r < (2 * tex_color.r))
		out_color.r = target_tex_color.r;
	else if(target_tex_color.r > (2 * tex_color.r))
		out_color.r = 2 * tex_color.r;	

	if(target_tex_color.g < (2 * tex_color.g - 1))
		out_color.g = 2 * tex_color.g - 1; 
	else if(target_tex_color.g > (2 * tex_color.g - 1) && target_tex_color.g < (2 * tex_color.g))
		out_color.g = target_tex_color.g;
	else if(target_tex_color.g > (2 * tex_color.g))
		out_color.g = 2 * tex_color.g;
		
	if(target_tex_color.b < (2 * tex_color.b - 1))
		out_color.b = 2 * tex_color.b - 1; 
	else if(target_tex_color.b > (2 * tex_color.b - 1) && target_tex_color.b < (2 * tex_color.b))
		out_color.b = target_tex_color.b;
	else if(target_tex_color.b > (2 * tex_color.b))
		out_color.b = 2 * tex_color.b;
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}