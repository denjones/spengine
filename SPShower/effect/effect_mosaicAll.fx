////////////////////////////////////////////////
// Name: effect_mosaicAll.ef
// Author:邱俊威
// Date:2012-08-13
// Desc:通过矩阵mosaicSize（8.8）对全图进行马赛克效果处理，马赛克矩阵会越来越大，最后看不见原图的样子
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
	//得到当前纹理坐标相对图像大小整数值。
    float2  intXY = float2(texCoord.x * width , texCoord.y * height);
    

	//根据马赛克块大小进行取整。
    float2  XYMosaic   = float2(int(intXY.x/mosaicSize.x) * mosaicSize.x,   
				int(intXY.y/mosaicSize.y) * mosaicSize.y ) + 0.5 * mosaicSize;
    //把整数坐标转换回纹理采样坐标

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
