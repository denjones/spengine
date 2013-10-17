////////////////////////////////////////////////
// Name: effect_grayvalue.ef
// Author:邱俊威
// Date:2012-08-13
// Desc:取得该点的颜色值，然后通过计算h=r*0.3+g*0.59+b*0.11,再将其RGB的值改为h即可
///////////////////////////////////////////////

sampler tex : register(S0);
sampler effectTex : register(S1);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);
float level : register(C3);

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{

	float pos = transitionPosition;

	float4 tex_color = tex2D(tex, texCoord);	

	float h = tex_color.r * 0.3 + tex_color.g * 0.59 + tex_color.b * 0.11;

	float4 _outColor = float4( h, h, h, tex_color.a );

	

    return  (_outColor - tex_color) * pos + tex_color ;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}