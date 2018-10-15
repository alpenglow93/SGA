//Sprite.hlsl
cbuffer VS_WVP : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}
cbuffer VS_UV : register(b1)	//이미지 루프 추가
{
	float2 offset;
	float2 padding;	//간격
}
struct VertexInput
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;	//추가
};
struct PixelInput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;	//추가
};
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);

	output.texCoord = input.texCoord + offset;

	return output;
}

SamplerState Sampler : register(s0);
//SamplerState -> 이미지의 설정
Texture2D Texture : register(t0);	//이미지 색상값

float4 PS(PixelInput input) : SV_TARGET
{
	return Texture.Sample(Sampler, input.texCoord);
	
}