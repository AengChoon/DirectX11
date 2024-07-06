#pragma once
#include <string_view>

class CGame
{
public:
	CGame();

	~CGame();

	void Init(HWND InWindowHandle);

	void Update();

	void Render();

private:
	void BeginRender();

	void EndRender();

	void CreateDeviceAndSwapChain();

	void CreateRenderTargetView();

	void SetViewport();

	void CreateGeometry();

	void CreateInputLayout();

	void CreateVertexShader();

	void CreatePixelShader();

	static void LoadShaderFromFile(std::wstring_view Path, std::string_view Name,
	                               std::string_view Version,Microsoft::WRL::ComPtr<ID3DBlob>& OutBlob);

private:
	HWND WindowHandle;

	uint32 Width;

	uint32 Height;

	/** Device & SwapChain */
	Microsoft::WRL::ComPtr<ID3D11Device> Device;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;

	/** RenderTargetView */
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;

	/** Misc */
	D3D11_VIEWPORT Viewport;

	/** Geometry */
	std::vector<FVertex> Vertices;

	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;

	/** Vertex Shader */
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;

	Microsoft::WRL::ComPtr<ID3DBlob> VertexShaderBlob;

	/** Pixel Shader */
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;

	Microsoft::WRL::ComPtr<ID3DBlob> PixelShaderBlob;
};

