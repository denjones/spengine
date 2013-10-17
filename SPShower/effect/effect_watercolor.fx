////////////////////////////////////////////////
// Name: effect_watercolor.ef
// Author:����
// Date:2012-8-13
// Desc:��noiseTexture��r��gͨ���õ�һ��ֵ��Ϊ����������Ĳ���ֵ���γ���ɢЧ��
///////////////////////////////////////////////

sampler tex : register(S0);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);

float level : register(C3); //������bit�� ��ȡֵ2��6�Ƚ��ʺ�
float waterPower; //��ʾ��չ���ȣ���λΪ����
sampler noiseTexture; // ��������

//����ͼ�����ɫֵ���γ�ɫ��
float4  quant(float4 _cl , float n)
{
	//�ú�������ɫ���ĸ�������������
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