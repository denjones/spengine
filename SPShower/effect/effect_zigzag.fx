//////////////////////////////////////////////////////////////////////////
/// @file		ˮ��Ч��
/// @author		
/// @version	
/// @date	
//δʵ��	
//////////////////////////////////////////////////////////////////////////// 

sampler tex : register(S0);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);

float level : register(C3); //������bit�� ��ȡֵ2��6�Ƚ��ʺ�
float waterPower; //��ʾ��չ���ȣ���λΪ����
sampler noiseTexture; // ��������


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