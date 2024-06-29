#pragma once

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

private:
	HWND WindowHandle;

	uint32 Width;

	uint32 Height;

	Microsoft::WRL::ComPtr<ID3D11Device> Device;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;

	D3D11_VIEWPORT Viewport;
};

