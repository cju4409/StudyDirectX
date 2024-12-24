struct PS_INPUT
{
	float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

// 텍스쳐슬롯과 샘플러슬롯은 항상 세트로 있음 t0:텍스쳐0번슬롯, s0:샘플러0번슬롯
Texture2D tex : TEXTURE : register(t0);
SamplerState sam : SAMPLER : register(s0);

float4 ps(PS_INPUT input) : SV_TARGET
{
    float4 color = tex.Sample(sam, input.uv);
    //컬러값은 0-1 이므로 곱하는게 일반적임. 최대치가 1을 넘어서 안되므로
	return color * input.color;
};