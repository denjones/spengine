////////////////////////////////////////////////
// Name: effect_spacial_laplace.ef
// Author:����
// Date:2012-08-13
// Desc:��������㣬Ȼ������˲���Ȩ�أ����ۼӵó����������ɫ,�ó�laplace�任Ч��
///////////////////////////////////////////////

sampler tex : register(S0);
sampler effectTex : register(S1);
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);
float level : register(C3);


float4 dip_filter(float3x3 _filter ,sampler tex , float2 _xy )
{
    //�������������ƫ��
     float2 _filter_pos_delta[3][3] = 
     {
        { float2( -1.0 , -1.0 ) , float2( 0.0,-1.0 ), float2( 1.0 , -1.0 ) },
        { float2( 0.0 , -1.0 ) , float2( 0.0, 0.0 ), float2( 1.0 ,  0.0 ) },
        { float2( 1.0 , -1.0 ) , float2( 0.0, 1.0 ), float2( 1.0 ,  1.0 ) },
     };
     //���յ������ɫ
     float4 final_color = float4(0.0,0.0,0.0,0.0);
     //��ͼ�����˲�����
     for( int i = 0 ; i < 3 ; i ++ )
     {
         for( int j = 0 ; j < 3 ; j ++ )
         {
			//��������㣬�õ���ǰ���ظ��������ص�����
            float2 _xy_new = float2( _xy.x + _filter_pos_delta[i][j].x ,
                                    _xy.y + _filter_pos_delta[i][j].y );

			float2 _uv_new = float2( _xy_new.x/width , _xy_new.y/height );
            //�����������˲���Ȩ�أ�Ȼ���ۼ�
            final_color += tex2D( tex , _uv_new ) * _filter[i][j];
         } 
     }
     return final_color;
}

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{

	float pos = transitionPosition;
	float4 tex_color = tex2D(tex, texCoord);
	
	float2  intXY = float2( texCoord.x * width , texCoord.y * height );
	//��������˹
	float3x3 _smooth_fil = float3x3 (-1.0 ,-1.0 , -1.0 ,
                                    -1.0 , 9.0 , -1.0 ,
                                    -1.0 , -1.0 , -1.0 );

	return  ( dip_filter( _smooth_fil , tex , intXY  ) - tex_color ) * pos + tex_color ;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}