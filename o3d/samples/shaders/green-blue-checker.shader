// @@REWRITE(insert shader-copyright)
// The 4x4 world view projection matrix.
float4x4 worldViewProjection : WORLDVIEWPROJECTION;
float4x4 worldInverseTranspose : WORLDINVERSETRANSPOSE;
float4x4 world : WORLD;

// light position
float3 lightWorldPos;
float3 lightColor;

// input parameters for our vertex shader
struct VertexShaderInput {
  float4 position : POSITION;
  float4 normal : NORMAL;
  float2 texcoord : TEXCOORD0;
};

// input parameters for our pixel shader
struct PixelShaderInput {
  float4 position : POSITION;
  float2 texcoord : TEXCOORD0;
  float3 normal : TEXCOORD1;
  float3 worldPosition : TEXCOORD2;
};

// function for getting the checker pattern
float4 checker(float2 uv) {
  float checkSize = 10;
  float fmodResult = fmod(floor(checkSize * uv.x) + floor(checkSize * uv.y),
                          2.0);
  return (fmodResult < 1) ?
      float4(0.4, 0.5, 0.5, 1) :
      float4(0.6, 0.8, 0.8, 1);
}

/**
 * Our vertex shader. In the vertex shader, we calculate the lighting.
 * Then we'll combine it with our checker pattern input the pixel shader.
 */
PixelShaderInput vertexShaderFunction(VertexShaderInput input) {
  PixelShaderInput output;

  // Transform position into clip space.
  output.position = mul(input.position, worldViewProjection);

  // Transform normal into world space, where we can do lighting
  // calculations even if the world transform contains scaling.
  output.normal = mul(input.normal, worldInverseTranspose).xyz;

  // Calculate surface position in world space.
  output.worldPosition = mul(input.position, world).xyz;

  output.texcoord = input.texcoord;

  return output;
}

/**
 * Our pixel shader. We take the lighting color we got from the vertex sahder
 * and combine it with our checker pattern. We only need to use the x
 * coordinate of our input.col because we gave it uniform color
 */
float4 pixelShaderFunction(PixelShaderInput input): COLOR {
  float3 surfaceToLight = normalize(lightWorldPos - input.worldPosition);

  float3 worldNormal = normalize(input.normal);

  // Apply diffuse lighting in world space in case the world transform
  // contains scaling.
  float4 check = checker(input.texcoord);
  float4 directionalIntensity = saturate(dot(worldNormal, surfaceToLight));
  float4 outColor = directionalIntensity * check;
  return float4(outColor.rgb, 1);
}

// Here we tell our effect file *which* functions are
// our vertex and pixel shaders.

// #o3d VertexShaderEntryPoint vertexShaderFunction
// #o3d PixelShaderEntryPoint pixelShaderFunction
// #o3d MatrixLoadOrder RowMajor
