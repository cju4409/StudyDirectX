struct PS_INPUT
{
	float4 pos : SV_Position;
};
float4 ps(PS_INPUT input) : SV_TARGET
{
	return float4(1, 1, 1, 1);
};