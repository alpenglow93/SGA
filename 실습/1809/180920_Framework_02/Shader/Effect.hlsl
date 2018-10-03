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
	output.position = input.position;
	return output;
}
float4 PS(PixelInput input) : SV_TARGET
{
	return float4(0, 0, 0, 1);
}