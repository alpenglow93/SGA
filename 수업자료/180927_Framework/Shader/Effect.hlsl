//Effect.hlsl
cbuffer VS_WVP : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}
struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};
struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);

	output.color = input.color;

	return output;
}
float4 PS(PixelInput input) : SV_TARGET
{
	return input.color;
}

