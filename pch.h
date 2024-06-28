#pragma once
#include "Types.h"
#include "Values.h"
#include "Structs.h"

/** STL */
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

/** Windows */
#include <Windows.h>
#include <assert.h>

/** DirectX */
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>

/** Library */
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex_Release.lib")
#endif