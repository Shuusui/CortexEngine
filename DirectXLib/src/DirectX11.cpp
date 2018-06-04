#include "../include/DirectX11.h"

CE::DX::DX11::DX11(const HINSTANCE & hInstance, const HWND& hwnd)
	:m_pSwapChain(nullptr)
	,m_pDevice(nullptr)
	,m_pDevCon(nullptr)
	,m_pRenderTargetView(nullptr)
	,m_pDepthStencilBuffer(nullptr)
	,m_pDepthStencilView(nullptr)
	,m_pBaseDevice(nullptr)
	,m_hMainWnd(hwnd)
	,m_hInstance(hInstance)
{
}

HWND CE::DX::DX11::GetMainWnd() const
{
	return HWND();
}

int32_t CE::DX::DX11::Run()
{
	return int32_t();
}

void CE::DX::DX11::DrawScene()
{
}

CE::DX::DX11::~DX11()
{
}

void CE::DX::DX11::Release()
{
}

bool CE::DX::DX11::Init()
{
	if (CreateDeviceD3D() < 0)
	{
		CleanupDeviceD3D(); 
		return false; 
	}
	return true;
}

bool CE::DX::DX11::Failed(HRESULT aResult)
{
	if (FAILED(aResult))
	{
		LPTSTR buffer; 
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)aResult, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

		MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR); 
		LocalFree(buffer); 
		return true;
	}
	return false;
}

HRESULT CE::DX::DX11::CreateDeviceD3D()
{
	DXGI_SWAP_CHAIN_DESC sd{ 0 };
	sd.BufferCount = 2; 
	sd.BufferDesc.Width = 0; 
	sd.BufferDesc.Height = 0; 
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hMainWnd;
	sd.SampleDesc.Count = 1; 
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
#if defined (DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; 
#endif
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, }; 
	if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION,
		&sd, &m_pSwapChain, &m_pDevice, &featureLevel, &m_pDevCon) != S_OK)
		return E_FAIL; 
	CreateRenderTarget();

	return S_OK;
}

void CE::DX::DX11::InvalidateDeviceObjects()
{
}

void CE::DX::DX11::CleanupRenderTarget()
{
}

void CE::DX::DX11::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer; 
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_pBaseDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
	pBackBuffer->Release();
}

void CE::DX::DX11::CleanupDeviceD3D()
{
	SafeRelease(m_pSwapChain); 
	SafeRelease(m_pDevice); 
	SafeRelease(m_pDevCon);
	SafeRelease(m_pBaseDevice);
}
