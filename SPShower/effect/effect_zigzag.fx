//////////////////////////////////////////////////////////////////////////
/// @file		水波效果
/// @author		
/// @version	
/// @date	
//未实现	
//////////////////////////////////////////////////////////////////////////// 

sampler tex : register(S0);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);

float level : register(C3); //量化的bit数 ，取值2－6比较适合
float waterPower; //表示扩展力度，单位为象素
sampler noiseTexture; // 噪声纹理


float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 tex_color = tex2D(tex, texCoord);
    
    return tex_color;                    
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}