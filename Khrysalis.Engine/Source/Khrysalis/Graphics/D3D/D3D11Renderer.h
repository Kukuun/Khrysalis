#pragma once

#include "Khrysalis/Graphics/RendererAPI.h"

#include <wrl.h>

struct GLFWwindow;
struct ID3D11Device;
struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
struct IDXGIAdapter;

namespace Khrysalis {
	class D3D11Renderer : public RendererAPI {
	public:
		virtual void Initialize() override;
		virtual void Clear(float red = 1.0f, float green = 1.0f, float blue = 1.0f) override;
		virtual void Submit(std::vector<float> vertices) override;
		virtual void SwapBuffers() override;
		virtual void Resize(uint16_t width, uint16_t height) override;
		virtual void Shutdown() override;

		virtual void SetVsync(bool isVsync) override { _isVSync = isVsync; }

		inline ID3D11Device* GetDevice() const { return _device.Get(); }
		inline IDXGISwapChain* GetSwapChain() const { return _swapChain.Get(); }
		inline ID3D11DeviceContext* GetDeviceContext() const { return _context.Get(); }
		inline ID3D11RenderTargetView* GetRenderTargetView() const { return _renderTargetView.Get(); }
		inline ID3D11DepthStencilView* GetDepthStencilView() const { return _depthStencilView.Get(); }

	private:
		void CreateRenderTarget();
		void CreateDepthStencilView();
		std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> GetAdapters();
		void SelectAdapter();

	private:
		HWND _windowHandle = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Device> _device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;

		Microsoft::WRL::ComPtr<IDXGIAdapter> _adapter;

		bool _isVSync = true;
	};
}