////////////////////////////////////////////////
// Name: effect_watercolor.ef
// Author:邱俊威
// Date:2012-8-13
// Desc:从noiseTexture的r、g通道得到一个值作为对纹理坐标的波动值，形成扩散效果
///////////////////////////////////////////////

sampler tex : register(S0);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);

float level : register(C3); //量化的bit数 ，取值2－6比较适合
float waterPower; //表示扩展力度，单位为象素
sampler noiseTexture; // 噪声纹理

//量化图像的颜色值，形成色块
float4  quant(float4 _cl , float n)
{
	//该函数对颜色的四个分量进行量化
    _cl.x = int(_cl.x * 255 / n) * n /255;
    _cl.y = int(_cl.y * 255 / n) * n /255;
    _cl.z = int(_cl.z * 255 / n) * n /255;
    return _cl;
}

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
    float4 noiseColor = waterPower * tex2D(noiseTexture , texCoord);
    float2 newUV  = float2(texCoord.x + (noiseColor.x) / width , 
						   texCoord.y + (noiseColor.y) / height);
    float4 _fColor = tex2D(tex , newUV);
    
    return quant(_fColor , 255/pow(2, level) );                    
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}