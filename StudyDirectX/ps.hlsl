struct PS_INPUT
{
	float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

// �ؽ��Ľ��԰� ���÷������� �׻� ��Ʈ�� ���� t0:�ؽ���0������, s0:���÷�0������
Texture2D tex : TEXTURE : register(t0);
SamplerState sam : SAMPLER : register(s0);

float4 ps(PS_INPUT input) : SV_TARGET
{
    float4 color = tex.Sample(sam, input.uv);
    //�÷����� 0-1 �̹Ƿ� ���ϴ°� �Ϲ�����. �ִ�ġ�� 1�� �Ѿ �ȵǹǷ�
	return color * input.color;
};