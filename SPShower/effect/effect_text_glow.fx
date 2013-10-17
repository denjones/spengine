sampler tex : register(S0);
texture Tex1;
float width:register(C1);
float height:register(C2);
float transitionPosition:register(C3);
float level:register(C4);
float opacity:register(C5);

//////////////////////////////////////////////////////////////////////////

// Default vertex shader for shader model 3.0

float4x4 MatrixTransform;
void SpriteVertexShader(
	inout float4 vColor : COLOR0, 
	inout float2 texCoord : TEXCOORD0,
	inout float4 position : POSITION0)
{
    position = mul(position, MatrixTransform);
}
//////////////////////////////////////////////////////////////////////////

sampler effectTex = sampler_state
{
	Texture = (Tex1);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

//////////////////////////////////////////////////////////////////////////

// 2.0

float4 BlurVertical( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0.0f;

    float iy = 1.0 / height;

	float a = 1.19683f / level;
	float e = 2.71828f;

	Color = tex2D(tex, Tex) * a;

	[unroll(5)]
	for(int num = 0; num < level; num++)
	{
		float factor = a * pow(e, -4.5f * (num / level) * (num / level));
		Color += tex2D(tex, float2(Tex.x, Tex.y - num * iy)) * factor;
		Color += tex2D(tex, float2(Tex.x, Tex.y + num * iy)) * factor;
	}

    return Color;
}

float4 BlurHorizontal( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0.0f;

	float ix = 1.0 / width;
	
	float a = 1.19683f / level;
	float e = 2.71828f;

	Color = tex2D(tex, Tex) * a;

	[unroll(5)]
	for(int num = 0; num < level; num++)
	{
		float factor = a * pow(e, -4.5f * (num / level) * (num / level));
		Color += tex2D(tex, float2(Tex.x - num * ix, Tex.y)) * factor;
		Color += tex2D(tex, float2(Tex.x + num * ix, Tex.y)) * factor;
	}

    return Color;
}

float4 PS_Horizontal(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{	
	float4 Color = tex2D(tex, texCoord);

	return BlurHorizontal(texCoord);
}

float4 PS_Vertical(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 Color = tex2D(effectTex, texCoord);

	float4 resultColor = BlurVertical(texCoord);

	if(opacity != 0)
	{
		Color.a = resultColor.a * opacity;
	}
	else
	{
		Color.a = resultColor.a;
	}

	if( Color.a > 1)
	{
		Color.a = 1;
	}

	return Color;
}

///////////////////////////////////////////////////////////////////////////

// 3.0

float4 BlurHorizontal3( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0.0f;

	float ix = 1.0 / width;
	
	float a = 1.19683f / level;
	float e = 2.71828f;

	Color = tex2D(tex, Tex) * a;

	[unroll(20)]
	for(int num = 0; num < level; num++)
	{
		float factor = a * pow(e, -4.5f * (num / level) * (num / level));
		Color += tex2Dlod(tex, float4(Tex.x - num * ix, Tex.y, 0, 0)) * factor;
		Color += tex2Dlod(tex, float4(Tex.x + num * ix, Tex.y, 0, 0)) * factor;
	}

    return Color;
}

float4 BlurVertical3( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0.0f;

    float iy = 1.0 / height;

	float a = 1.19683f / level;
	float e = 2.71828f;

	Color = tex2D(tex, Tex) * a;

	[unroll(20)]
	for(int num = 0; num < level; num++)
	{
		float factor = a * pow(e, -4.5f * (num / level) * (num / level));
		Color += tex2Dlod(tex, float4(Tex.x, Tex.y - num * iy, 0, 0)) * factor;
		Color += tex2Dlod(tex, float4(Tex.x, Tex.y + num * iy, 0, 0)) * factor;
	}

    return Color;
}

float4 PS_Stroke3(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{	
	float4 tex_color = tex2D( tex , texCoord);    

	float4 stroke_color = tex2D(effectTex , texCoord);

    float ix = 1.0 / width;
    float iy = 1.0 / height;

	float gap = 0.1;

	if(gap > 1)
	{
		gap = 1;
	}

	float time = level * 0.3;
	if(time > 10)
	{
		time = 10;
	}

	if(time <= 0)
	{
		return tex_color;
	}

	if(tex_color.a < gap)
	{
		for(int x = -time ; x < time; x++)
		{
			for(int y = -time; y < time; y++)
			{
				if((x == -time || x == time) && (y == -time || y == time))
				{
					continue;
				}

				if(tex2Dlod(tex, float4(texCoord + float2(x * ix, y * iy), 0, 0)).a >= gap)
				{
					stroke_color.a = 1 - tex_color.a;
					tex_color = stroke_color; 
					return tex_color; 
				}
			}
		}
	}
	else
	{            
		tex_color = stroke_color;
	}

	return tex_color ;
}

float4 PS_Horizontal3(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{	
	float4 Color = tex2D(tex, texCoord);

	return BlurHorizontal3(texCoord);
}

float4 PS_Vertical3(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 resultColor = BlurVertical3(texCoord);

	//Color.r = Color.r * resultColor.a;
	//Color.g = Color.g * resultColor.a;
	//Color.b = Color.b * resultColor.a;

	resultColor.a *= opacity;

	if( resultColor.a > 1)
	{
		resultColor.a = 1;
	}

	return resultColor;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 PS_Horizontal();
	}

	pass P1
	{
		PixelShader = compile ps_2_0 PS_Vertical();
	}
}

technique T1
{
	pass P0
	{
		VertexShader = compile vs_3_0  SpriteVertexShader();
		PixelShader = compile ps_3_0 PS_Stroke3();
	}

	pass P1
	{
		VertexShader = compile vs_3_0  SpriteVertexShader();
		PixelShader = compile ps_3_0 PS_Horizontal3();
	}

	pass P2
	{
		VertexShader = compile vs_3_0  SpriteVertexShader();
		PixelShader = compile ps_3_0 PS_Vertical3();
	}
}