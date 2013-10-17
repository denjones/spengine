#include "StdAfx.h"
#include "Vertex.h"

using namespace SPEngine::Vertex;

// Vertex
const DWORD Vertex::FVF = D3DFVF_XYZ;
const DWORD ColorVertex::FVF = D3DFVF_COLOR;
const DWORD NormalVertex::FVF = D3DFVF_NORMAL_VERTEX;
const DWORD NormalTexVertex::FVF = D3DFVF_NORMAL_TEX;
const DWORD NormalTexColorVertex::FVF = D3DFVF_NORMAL_TEX_COLOR;	
