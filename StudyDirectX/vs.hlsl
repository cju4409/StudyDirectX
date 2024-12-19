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
	// float4(xyz, w) -> w: 1�� ��ġ, 0�� ����. ������ ���� �ϳ�
	// ��ġ(1) - ��ġ(1) = ����(0) �̹Ƿ�
	output.pos = float4(input.pos, 1);
	
	return output;
}