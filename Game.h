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
	void CreateDeviceAndSwapChain();

	void CreateRenderTargetView();

private:
	HWND WindowHandle;

	uint32 Width;

	uint32 Height;

	Microsoft::WRL::ComPtr<ID3D11Device> Device;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;
};

