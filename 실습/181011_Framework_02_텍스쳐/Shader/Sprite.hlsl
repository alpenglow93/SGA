//Sprite.hlsl
cbuffer VS_WVP : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}
//PS_Color ����
struct VertexInput
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;	//�߰�
};
struct PixelInput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;	//�߰�
};
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);

	output.texCoord = input.texCoord;

	return output;
}

SamplerState Sampler : register(s0);
//SamplerState -> �̹����� ����
Texture2D Texture : register(t0);	//�̹��� ����

float4 PS(PixelInput input) : SV_TARGET
{
	return Texture.Sample(Sampler, input.texCoord);
	
}