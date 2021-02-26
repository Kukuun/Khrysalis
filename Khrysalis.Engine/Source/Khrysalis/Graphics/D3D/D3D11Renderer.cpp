#include "KalPch.h"

#include "Khrysalis/Graphics/D3D/D3D11Renderer.h"
#include "Khrysalis/Core/Application.h"
#include "Khrysalis/Debug/Assert.h"
#include "Khrysalis/Maths/Vector2.h"

#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>

namespace Khrysalis {
	void D3D11Renderer::Initialize() {
		uint16_t width = Application::Get().GetWindow().GetWidth();
		uint16_t height = Application::Get().GetWindow().GetHeight();

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferDesc.Width = width;													// Resolution width - setting this to 0 means it'll get it from the window/hwnd handle.
		swapChainDesc.BufferDesc.Height = height;												// Resolution height - setting this to 0 means it'll get it from the window/hwnd handle.
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;						// Use 32-bit colors.
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;									// An unsigned integer value representing the top of the rational number.
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;								// An unsigned integer value representing the bottom of the rational number.
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;													// Multisample anti aliasing : 0 = no MSAA.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;						// How swap chain is to be used - this option is used to draw into the back buffer.
		swapChainDesc.BufferCount = 1;														// One back buffer.
		swapChainDesc.OutputWindow = Application::Get().GetWindow().GetHwndHandle();											// Window to be used.
		swapChainDesc.Windowed = TRUE;														// Windowed mode.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;								// Make driver select the most efficient presentation method.
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		SelectAdapter();

		HRESULT result = D3D11CreateDeviceAndSwapChain(
			_adapter.Get(),				// Graphics card to use - nullptr lets DXGI handle this.
			D3D_DRIVER_TYPE_UNKNOWN,	// Driver type: Use D3D_DRIVER_TYPE_HARDWARE for d3d11 to choose the most appropriate adapter. D3D_DRIVER_TYPE_UNKNOWN if you want to select an adapter yourself.
			nullptr,					// Used if driver type is software.
			0,							// Flags for how D3D runs. Multithreading is on by default.
			nullptr,					// List of feature levels expected to be used in the program.
			0,							// How many feature levels in the list.
			D3D11_SDK_VERSION,			// SDK used.
			&swapChainDesc,				// Reference to the swap chain description struct.
			&_swapChain,				// Pointer to a swap chain pointer that will be populated.
			&_device,					// Pointer to a device pointer that will be populated.
			nullptr,					// Pointer to a feature levels variable.
			&_context				// Pointer to a device context pointer that will be populated.
		);

		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create dx11 device and swap chain.");

		CreateRenderTarget();
		CreateDepthStencilView();

		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());

		D3D11_VIEWPORT viewport;

		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		_context->RSSetViewports(1, &viewport);
	}

	void D3D11Renderer::Clear(float red, float green, float blue) {
		const float colors[] = { red, green, blue, 1.0f };

		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
		_context->ClearRenderTargetView(_renderTargetView.Get(), colors);
		_context->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void D3D11Renderer::Submit(std::vector<float> verticess) {
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

		const Vector2 vertices[] =
		{
			{  0.0f,  0.5f },
			{  0.5f, -0.5f },
			{ -0.5f, -0.5f }
		};

		D3D11_BUFFER_DESC bufferDesc = {};
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.ByteWidth = sizeof(vertices);
		bufferDesc.StructureByteStride = sizeof(Vector2);

		D3D11_SUBRESOURCE_DATA subData = {};
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = &vertices;

		HRESULT result = _device->CreateBuffer(&bufferDesc, &subData, &vertexBuffer);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create vertex buffer.");

		UINT stride = sizeof(Vector2);
		UINT offset = 0;
		_context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

		Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
		result = D3DReadFileToBlob(L"PixelShader.cso", &shaderBlob);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create pixel shader blob.");

		_device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &pixelShader);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create pixel shader.");

		_context->PSSetShader(pixelShader.Get(), nullptr, 0);

		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
		result = D3DReadFileToBlob(L"VertexShader.cso", &shaderBlob);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create vertex shader blob.");

		_device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &vertexShader);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create vertex shader.");

		_context->VSSetShader(vertexShader.Get(), nullptr, 0);


		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
		D3D11_INPUT_ELEMENT_DESC elementDesc[] = {
			{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		result = _device->CreateInputLayout(elementDesc, (UINT)std::size(elementDesc), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), &inputLayout);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create input layout.");

		_context->IASetInputLayout(inputLayout.Get());

		_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

		_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		_context->Draw((UINT)std::size(vertices), 0);
	}

	void D3D11Renderer::SwapBuffers() {
		_swapChain->Present(_isVSync, 0u);
	}

	void D3D11Renderer::Resize(uint16_t width, uint16_t height) {
		_renderTargetView->Release();

		_swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

		CreateRenderTarget();

		D3D11_VIEWPORT viewport;

		viewport.Width = width;
		viewport.Height = height;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		_context->RSSetViewports(1, &viewport);
	}

	void D3D11Renderer::Shutdown() {}

	void D3D11Renderer::CreateRenderTarget() {
		Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;

		HRESULT result = _swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create backbuffer.");

		result = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, &_renderTargetView);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create render target view.");
	}

	void D3D11Renderer::CreateDepthStencilView() {
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.Width = Application::Get().GetWindow().GetWidth();		// Get viewport width.
		depthStencilDesc.Height = Application::Get().GetWindow().GetHeight();	// Get viewport height.
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;		// Must match swap chain MSAA values.
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		HRESULT result = _device->CreateTexture2D(&depthStencilDesc, nullptr, _depthStencilBuffer.GetAddressOf());
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create depth stencil buffer.");

		result = _device->CreateDepthStencilView(_depthStencilBuffer.Get(), nullptr, _depthStencilView.GetAddressOf());
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create depth stencil view.");
	}

	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> D3D11Renderer::GetAdapters() {
		Microsoft::WRL::ComPtr<IDXGIFactory> factory;

		HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), &factory);
		KAL_ENGINE_ASSERT(result == S_OK, "Failed to create dxgi factory.");

		Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
		std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> availableAdapters;
		for (int i = 0; factory->EnumAdapters(i, adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND; ++i) {
			availableAdapters.push_back(adapter.Get());
		}

		KAL_ENGINE_ASSERT(availableAdapters.size() > 0, "No IDXGI adapters found.");

		return availableAdapters;
	}

	void D3D11Renderer::SelectAdapter() {
		std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> adapters = GetAdapters();

		uint64_t availableVideoMemoryAvailable = 0;

		for (Microsoft::WRL::ComPtr<IDXGIAdapter> adapter : adapters) {
			DXGI_ADAPTER_DESC desc = {};
			adapter->GetDesc(&desc);

			if (desc.DedicatedVideoMemory > availableVideoMemoryAvailable) {
				availableVideoMemoryAvailable = desc.DedicatedVideoMemory;
				_adapter = adapter;
			}
		}
	}
}