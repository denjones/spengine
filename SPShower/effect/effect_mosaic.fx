////////////////////////////////////////////////
// Name: effect_mosaic.ef
// Author:邱俊威
// Date:2012-08-13
// Desc:通过矩阵mosaicSize（8.8）对全图进行马赛克效果处理，马赛克矩阵不会变化
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
	//得到当前纹理坐标相对图像大小整数值。
    float2  intXY = float2(texCoord.x * width , texCoord.y * height);

	//马赛克中心不再是左上角，而是中心
	float2  XYMosaic   = float2(int(intXY.x/mosaicSize.x) * mosaicSize.x,   
				int(intXY.y/mosaicSize.y) * mosaicSize.y ) + 0.5 * mosaicSize;
	//求出采样点到马赛克中心的距离
	float2  delXY = XYMosaic - intXY;
	float  delL  = length(delXY);
	float2  UVMosaic   = float2(XYMosaic.x/width , XYMosaic.y/height);
	float4  _finalColor;
	//判断是不是处于马赛克圆中。
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