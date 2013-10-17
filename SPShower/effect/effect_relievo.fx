////////////////////////////////////////////////
// Name: effect_relievo.ef
// Author:����
// Date:2012-08-13
// Desc:���ȸ����ϵĵ��������õ���ɫ�ȡ��ɫ��ĻҶ�ֵ�ټ�����ɫ��0.5��0.5��0.5��1���Ϳ��Եõ�����Ч��
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

	float2  upLeftUV = float2(texCoord.x - 1.0/width , texCoord.y - 1.0/height);
    float4  bkColor = float4(0.5 , 0.5 , 0.5 , 1.0);
    float4  tex_color =  tex2D( tex, texCoord );
    float4  upLeftColor =  tex2D( tex, upLeftUV );
    //����õ���ɫ�Ĳ�
    float4  delColor = tex_color - upLeftColor;
    //��Ҫ�������ɫ�Ĳ�����

	float  h = 0.3 * delColor.r + 0.59 * delColor.g + 0.11* delColor.b;
    float4  _outColor =  float4(h,h,h,0.0)+ bkColor;

    return (_outColor - tex_color) * pos + tex_color ;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}