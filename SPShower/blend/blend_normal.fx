////////////////////////////////////////////////
// Name: mix_normal.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:正常，使用时用当前图层像素的颜色覆盖下层颜色，做α混合。
///////////////////////////////////////////////

sampler tex : register(S0);
texture Tex1;
float width;
float height;
float twidth;
float theight;
float cx;
float cy;
float px;
float py;
float4x4 MatrixTransform;

sampler targetTex = sampler_state
{
	Texture = (Tex1);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 CalTargetColor(float2 texCoord)
{
	float4 tex_Coord = float4(texCoord.x * width + cx + px, texCoord.y * height + cy + py, 0, 1);
	float4 target_tex_Coord = mul(tex_Coord, MatrixTransform);
	//target_tex_Coord.x += cx + px;
	//target_tex_Coord.y += cy + py;
	float2 targetTexCoord = float2(target_tex_Coord.x / twidth, target_tex_Coord.y / theight);
	float4 target_tex_color = tex2D(targetTex, targetTexCoord);
	
	return target_tex_color;
}

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 tex_color = tex2D(tex, texCoord);
	float4 target_tex_color = CalTargetColor(texCoord);
	tex_color = tex_color * color;

	float4 out_color = target_tex_color;

	//if(tex_color.a > target_tex_color.a)
	//	out_color.a = tex_color.a;
	//else
	//	out_color.a = target_tex_color.a;

	//out_color.r = (tex_color.a * tex_color.r + (1 - target_tex_color.a) * target_tex_color.r) / out_color.a;
	//out_color.g = (tex_color.a * tex_color.g + (1 - target_tex_color.a) * target_tex_color.g) / out_color.a;
	//out_color.b = (tex_color.a * tex_color.b + (1 - target_tex_color.a) * target_tex_color.b) / out_color.a;
	//out_color.a = tex_color.a + target_tex_color.a;

	float sa = tex_color.a;
	float ta = (1 - tex_color.a) * target_tex_color.a;
	//out_color.rgb = tex_color.rgb * sa * target_tex_color.rgb * ta;
	out_color.a = sa + ta;
	out_color.r = sa * tex_color.r + ta * target_tex_color.r;
	out_color.g = sa * tex_color.g + ta * target_tex_color.g;
	out_color.b = sa * tex_color.b + ta * target_tex_color.b;

	if(	   out_color.a > 1 )
	{
		out_color.a = 1;
	}

	return out_color;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}