#pragma region Internal includes
#pragma endregion
#pragma region External includes
#include <Windows.h>
#include <cstdint>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#pragma endregion
namespace CE
{
	namespace DX
	{
		class __declspec(dllexport) DX11
		{
		private:
			HINSTANCE m_hInstance{ 0 };
			HWND m_hMainWnd{ 0 };
			D3D11_VIEWPORT m_viewPort{ 0 };
			bool m_paused;
			bool m_minimized;
			bool m_maximized;
			bool m_resizing;
			uint32_t m_4xMsaaQuality;
			uint32_t m_resX;
			uint32_t m_resY;
			int64_t m_time;
			int64_t m_ticksPerSecond;
			std::wstring m_MainWindowCaption;
			bool enalbe4xMsaa;

			IDXGISwapChain* m_pSwapChain;
			ID3D11Device* m_pDevice;
			ID3D11DeviceContext* m_pDevCon;
			ID3D11RenderTargetView* m_pRenderTargetView;
			ID3D11Texture2D* m_pDepthStencilBuffer;
			ID3D11DepthStencilView* m_pDepthStencilView;
			ID3D11Device* m_pBaseDevice;

		public:
			DX11(const HINSTANCE& hInstance, const HWND& hwnd);
			bool Init();

			int32_t Run();
			void DrawScene();
			bool BuildShader(const std::string& filePath); //TODO: use shader class here instead of the bool as return
			bool SetShader(/*Shaderplaceholder*/); //TODO: set shader here instead of the placeholder
			virtual ~DX11();
		private:
			template<typename T> void SafeRelease(T*& aPointer)
			{
				if (aPointer != nullptr)
				{
					aPointer->Release();
					aPointer = nullptr;
				}
			}
			//
			// Function to release DX11
			//
			void Release();
			bool Failed(HRESULT aResult);
			HRESULT CreateDeviceD3D();
			void InvalidateDeviceObjects();
			void CleanupRenderTarget();
			void CreateRenderTarget();
			void CleanupDeviceD3D();
		};
	}
}