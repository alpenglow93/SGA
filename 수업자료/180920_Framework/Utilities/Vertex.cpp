#include "stdafx.h"
#include "Vertex.h"

D3D11_INPUT_ELEMENT_DESC VertexPC::desc[] = 
{
	{ "POSITION",0, VERTEX_XYZ, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0},
	{ "COLOR",0, VERTEX_XYZW, 0, 12, D3D11_INPUT_PER_VERTEX_DATA,0 }
};
UINT VertexPC::count = ARRAYSIZE(desc);