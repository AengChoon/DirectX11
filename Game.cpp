#include "pch.h"
#include "Game.h"

CGame::CGame()
	: WindowHandle(nullptr), Width(0), Height(0), Viewport()
{
}

CGame::~CGame()
{
}

void CGame::Init(const HWND InWindowHandle)
{
	WindowHandle = InWindowHandle;
	Width = GWindowSizeX;
	Height = GWindowSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

void CGame::Update()
{
}

void CGame::Render()
{
	BeginRender();
	EndRender();
}

void CGame::BeginRender()
{
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), nullptr);

	constexpr std::array ClearColor {0.0f, 0.0f, 0.0f, 0.0f};
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), ClearColor.data());

	DeviceContext->RSSetViewports(1, &Viewport);
}

void CGame::EndRender()
{
	const HRESULT Result = SwapChain->Present(1, 0);
	Check(Result);
}

void CGame::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));

	SwapChainDesc.BufferDesc.Width = Width;
	SwapChainDesc.BufferDesc.Height = Height;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	const HRESULT Result = ::D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		SwapChain.GetAddressOf(),
		Device.GetAddressOf(),
		nullptr,
		DeviceContext.GetAddressOf()
	);

	Check(Result);
}

void CGame::CreateRenderTargetView()
{
	HRESULT Result;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;

	Result = SwapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(BackBuffer.GetAddressOf())
	);
	Check(Result);

	Result = Device->CreateRenderTargetView
	(
		BackBuffer.Get(),
		nullptr,
		RenderTargetView.GetAddressOf()
	);
	Check(Result);
}

void CGame::SetViewport()
{
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	Viewport.Width = static_cast<float>(Width);
	Viewport.Height = static_cast<float>(Height);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
}
