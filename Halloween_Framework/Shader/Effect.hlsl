//Effect.hlsl
cbuffer VS_ViewOrtho : register(b0)
{
	matrix View;
	matrix Projection;
}
cbuffer VS_WORLD : register(b1)
{
	matrix World;
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

