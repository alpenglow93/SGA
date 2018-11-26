cbuffer VS_World : register(b0)
{
	matrix World;
}

Texture2D RenderTexture : register(t0);
SamplerState Sampler : register(s0);

struct VS_INPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	output.position = mul(input.position, World);
	output.uv = input.uv;

	return output;
}

float4 PS(PS_INPUT input) : SV_TARGET
{
	return RenderTexture.Sample(Sampler, input.uv);
}