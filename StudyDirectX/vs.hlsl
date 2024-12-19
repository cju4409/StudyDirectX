struct VS_INPUT
{
	float3 pos : POSITION;
};

struct PS_INPUT
{
	float4 pos : SV_Position;
};

PS_INPUT vs(VS_INPUT input)
{
	PS_INPUT output;
	// float4(xyz, w) -> w: 1은 위치, 0은 방향. 무조건 둘중 하나
	// 위치(1) - 위치(1) = 방향(0) 이므로
	output.pos = float4(input.pos, 1);
	
	return output;
}