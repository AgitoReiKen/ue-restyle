#include "WireShaders.h"

IMPLEMENT_SHADER_TYPE(, FRestyleVertexShader, TEXT("/Plugin/Restyle/Private/WireShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FRestylePixelShader, TEXT("/Plugin/Restyle/Private/WireShader.usf"), TEXT("MainPS"), SF_Pixel);