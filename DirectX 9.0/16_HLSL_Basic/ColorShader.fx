//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = ".\\Sphere.x";

float4x4 WorldMatrix : World;
float4x4 ViewMatrix : View;
float4x4 ProjectionMatrix : Projection;

struct VS_INPUT
{
   float4 position : POSITION;
};

struct VS_OUTPUT
{
   float4 position : POSITION;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main(VS_INPUT input)
{
  VS_OUTPUT output;
  
  output.position = mul(input.position, WorldMatrix);
  output.position = mul(output.position, ViewMatrix);
  output.position = mul(output.position, ProjectionMatrix);
  
  return output; 
}



float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main() : COLOR0
{   
   return( float4( 0.0f, 1.0f, 0.0f, 1.0f ) );
   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

