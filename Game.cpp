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
	CreateGeometry();
	CreateVertexShader();
	CreateInputLayout();
	CreatePixelShader();
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

void CGame::CreateGeometry()
{
	Vertices.resize(3);

	Vertices[0].Position = FVector3{-0.5f, -0.5f, 0.0f};
	Vertices[0].Color = FColor{1.0f, 0.0f, 0.0f, 1.0f};

	Vertices[1].Position = FVector3{0.0f, 0.5f, 0.0f};
	Vertices[1].Color = FColor{1.0f, 0.0f, 0.0f, 1.0f};

	Vertices[2].Position = FVector3{0.5f, -0.5f, 0.0f};
	Vertices[2].Color = FColor{1.0f, 0.0f, 0.0f, 1.0f};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.ByteWidth = static_cast<uint32>(sizeof(FVertex) * Vertices.size());

	D3D11_SUBRESOURCE_DATA SubresourceData;
	ZeroMemory(&SubresourceData, sizeof(SubresourceData));
	SubresourceData.pSysMem = Vertices.data();

	const HRESULT Result = Device->CreateBuffer
	(
		&BufferDesc,
		&SubresourceData,
		VertexBuffer.GetAddressOf()
	);
	Check(Result);
}

void CGame::CreateInputLayout()
{
	std::array InputElementDesc
	{
		D3D11_INPUT_ELEMENT_DESC
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	const HRESULT Result = Device->CreateInputLayout
	(
		InputElementDesc.data(),
		InputElementDesc.size(),
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		InputLayout.GetAddressOf()
	);
	Check(Result);
}

void CGame::CreateVertexShader()
{
	LoadShaderFromFile(L"DefaultShader.hlsl", "VS", "vs_5_0", VertexShaderBlob);

	const HRESULT Result = Device->CreateVertexShader
	(
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		nullptr,
		VertexShader.GetAddressOf()
	);
	Check(Result);
}

void CGame::CreatePixelShader()
{
	LoadShaderFromFile(L"DefaultShader.hlsl", "PS", "ps_5_0", PixelShaderBlob);

	const HRESULT Result = Device->CreatePixelShader
	(
		PixelShaderBlob->GetBufferPointer(),
		PixelShaderBlob->GetBufferSize(),
		nullptr,
		PixelShader.GetAddressOf()
	);
	Check(Result);
}	

void CGame::LoadShaderFromFile(const std::wstring_view Path, const std::string_view Name,
                               const std::string_view Version, Microsoft::WRL::ComPtr<ID3DBlob>& OutBlob)
{
	constexpr uint32 CompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	const HRESULT Result = ::D3DCompileFromFile
	(
		Path.data(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		Name.data(),
		Version.data(),
		CompileFlag,
		0,
		OutBlob.GetAddressOf(),
		nullptr
	);
	Check(Result);
}
