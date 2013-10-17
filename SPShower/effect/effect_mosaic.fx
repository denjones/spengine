////////////////////////////////////////////////
// Name: effect_mosaic.ef
// Author:����
// Date:2012-08-13
// Desc:ͨ������mosaicSize��8.8����ȫͼ����������Ч�����������˾��󲻻�仯
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

	float2 mosaicSize = float2(8,8);
	//�õ���ǰ�����������ͼ���С����ֵ��
    float2  intXY = float2(texCoord.x * width , texCoord.y * height);

	//���������Ĳ��������Ͻǣ���������
	float2  XYMosaic   = float2(int(intXY.x/mosaicSize.x) * mosaicSize.x,   
				int(intXY.y/mosaicSize.y) * mosaicSize.y ) + 0.5 * mosaicSize;
	//��������㵽���������ĵľ���
	float2  delXY = XYMosaic - intXY;
	float  delL  = length(delXY);
	float2  UVMosaic   = float2(XYMosaic.x/width , XYMosaic.y/height);
	float4  _finalColor;
	//�ж��ǲ��Ǵ���������Բ�С�
	if(delL< 0.5 * mosaicSize.x)
		_finalColor = tex2D( tex, UVMosaic );
	else
		_finalColor = tex2D( tex, texCoord );
	
	return  ( _finalColor - tex_color ) * pos + tex_color ;
	
	
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}