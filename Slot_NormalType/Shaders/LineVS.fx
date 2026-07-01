cbuffer TransformCB : register(b0)
{
    row_major float4x4 world;
};

cbuffer CameraCB : register(b1)
{
    row_major float4x4 viewProj;
};

struct LineVSInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct LineVSOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};


LineVSOutput main(LineVSInput input)
{
    LineVSOutput o;

    float4 p = float4(input.pos, 1.0f);
    p = mul(p, world);
    p = mul(p, viewProj);

    o.pos = p;
    o.color = input.color;
    return o;
}

