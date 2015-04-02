/////////////
// DEFINES //
/////////////
#define NUM_LIGHTS 4

/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
};

cbuffer LightPositionBuffer
{
	float4 lightPosition[NUM_LIGHTS];
};

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInputType
{
	float3 world_pos : POSITION0;
	//world position of the pixel
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : POSITION1;

	float3 lightPosition1 : TEXCOORD1;
	float3 lightPosition2 : TEXCOORD2;
	float3 lightPosition3 : TEXCOORD3;
	float3 lightPosition4 : TEXCOORD4;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType PhongVertexShader(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;
    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	float4 normal_ = float4(input.normal, 0.0f);
	output.normal = (mul(input.normal, worldMatrix)).xyz;
    //output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	
    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);

	//Position which is in the same space as light coordinates
	output.world_pos = mul(input.position, worldMatrix);
	//output.world_pos = mul(output.world_pos, viewMatrix);

	//LightPositions
	output.lightPosition1 = lightPosition[0]; 
	output.lightPosition2 = lightPosition[1];
	output.lightPosition3 = lightPosition[2];
	output.lightPosition4 = lightPosition[3];


    return output;
}
