////////////////////////////////////////////////
// Name: effect_mosaicAll.ef
// Author:����
// Date:2012-08-13
// Desc:ͨ������mosaicSize��8.8����ȫͼ����������Ч�����������˾����Խ��Խ����󿴲���ԭͼ������
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

	float2 mosaicSize = float2(100 * pos, 100 * pos );
	//�õ���ǰ�����������ͼ���С����ֵ��
    float2  intXY = float2(texCoord.x * width , texCoord.y * height);
    

	//���������˿��С����ȡ����
    float2  XYMosaic   = float2(int(intXY.x/mosaicSize.x) * mosaicSize.x,   
				int(intXY.y/mosaicSize.y) * mosaicSize.y ) + 0.5 * mosaicSize;
    //����������ת���������������

    float2  delXY = XYMosaic - intXY;
	float  delL  = length(delXY);
	float2  UVMosaic   = float2(XYMosaic.x/width , XYMosaic.y/height);
	float4  _finalColor = tex2D( tex, UVMosaic );
    
	return  _finalColor ;
	
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}
