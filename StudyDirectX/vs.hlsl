cbuffer Transform : register(b0)
{
    float4x4 viewProj;
}

struct VS_INPUT
{
	float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct PS_INPUT
{
	float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

PS_INPUT vs(VS_INPUT input)
{
	PS_INPUT output;
	
    output.pos = mul(float4(input.pos, 1), viewProj);
	
	// float4(xyz, w) -> w: 1�� ��ġ, 0�� ����. ������ ���� �ϳ�
	// ��ġ(1) - ��ġ(1) = ����(0) �̹Ƿ�
	//output.pos = float4(input.pos, 1);
    output.color = input.color;
    output.uv = input.uv;
	
	return output;
}