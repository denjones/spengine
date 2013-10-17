sampler tex : register(S0);
texture Tex1;
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);
float level : register(C3);
float opacity : register(C4);
float quality: register(C5);

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

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 tex_color = tex2D( tex , texCoord);    
	float4 stroke_color =  tex2D(effectTex , texCoord); 
    
    float ix = 1.0 / width;
    float iy = 1.0 / height;
    
	float gap = quality;

	if(gap > 1)
	{
		gap = 1;
	}

	if(tex_color.a < gap)
	{
		if(tex2D(tex, texCoord + float2(0, level * iy)).a >= gap
		|| tex2D(tex, texCoord + float2(0, -level * iy)).a >= gap
		|| tex2D(tex, texCoord + float2(level * ix, 0)).a >= gap
		|| tex2D(tex, texCoord + float2(- level * ix, 0)).a >= gap
		|| tex2D(tex, texCoord + float2(- level * ix,  -level * iy)).a >= gap
		|| tex2D(tex, texCoord + float2(- level * ix,  level * iy)).a >= gap
		|| tex2D(tex, texCoord + float2( level * ix,  level * iy)).a >= gap		
		|| tex2D(tex, texCoord + float2( level * ix,  -level * iy)).a >= gap) 
		{
			stroke_color.a = 1 - tex_color.a;
			tex_color = stroke_color; 
			tex_color.a = opacity;
			return tex_color; 
		}
	}
	else
	{
		float aa = 1 - tex_color.a; 
            
		float4 tempcolor = float4(  ( tex_color * tex_color.a + float4( stroke_color.rgb, tex_color.a) * aa )) ;            
            
		tex_color = tempcolor;
	}

	return tex_color ;
}

float4 PS_Main3( float4 color : COLOR, float2 texCoord : TEXCOORD0 ) : COLOR
{
	float4 tex_color = tex2D( tex , texCoord);    
	float4 stroke_color = tex2D(effectTex , texCoord);

    float ix = 1.0 / width;
    float iy = 1.0 / height;

	float gap = quality;

	if(gap > 1)
	{
		gap = 1;
	}

	float time = level;
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
					tex_color.a = opacity;
					return tex_color; 
				}
			}
		}
	}
	else
	{
		float aa = 1 - tex_color.a; 
            
		float4 tempcolor = tex_color * tex_color.a + stroke_color * aa;            
            
		tex_color = tempcolor;
	}

	return tex_color ;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}

technique T1
{
	pass P0
	{
		VertexShader = compile vs_3_0  SpriteVertexShader();
		PixelShader = compile ps_3_0 PS_Main3();
	}
}