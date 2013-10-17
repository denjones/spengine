////////////////////////////////////////////////
// Name: effect_posure.ef
// Author:邱俊威
// Date:2012-08-13
// Desc:通过参数ex和灰度值来确定图像的曝光效果，ex的范围由0-2
///////////////////////////////////////////////

sampler tex : register(S0);
sampler effectTex : register(S1);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);
float level : register(C3);

float4  posure(float4 _color , float gray , float ex)
{
	//重新调整场景的亮度
	float b = ( 4 * ex -  1 );
    float a = 1 - b;
    float f = gray * ( a * gray + b ); 
    return   f * _color;
} 

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	
	float pos = 1 - transitionPosition;
	float4 tex_color = tex2D(tex, texCoord);

    float _lum = 0.3 * tex_color.r + 0.59 * tex_color.g + 0.11* tex_color.b;
    float4 _fColor = tex2D(tex , texCoord);
    //对最终颜色进行修正
    return posure(_fColor , _lum , 2 * pos  );
	
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}