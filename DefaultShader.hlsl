struct VS_INPUT
{
    float4 Position : POSITION;
    float4 Color : COLOR;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT VS(VS_INPUT Input)
{
    VS_OUTPUT Output;
    Output.Position = Input.Position;
    Output.Color = Input.Color;

    return Output;
}

float4 PS(VS_OUTPUT Input) : SV_Target
{
    return float4(1.0f, 0.0f, 0.0f, 0.0f);
}