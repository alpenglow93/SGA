//Effect.hlsl
cbuffer VS_WVP : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}
cbuffer PS_COLOR : register(b0)
{
	float4 Color;
}
struct VertexInput
{
	float4 position : POSITION;
};
struct PixelInput
{
	float4 position : SV_POSITION;
};
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);
	return output;
}
float4 PS(PixelInput input) : SV_TARGET
{
	return Color;
}