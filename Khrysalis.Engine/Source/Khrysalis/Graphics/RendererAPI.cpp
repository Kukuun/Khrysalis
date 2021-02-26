#include "KalPch.h"

#include "Khrysalis/Graphics/RendererAPI.h"
#include "Khrysalis/Graphics/D3D/D3D11Renderer.h"

#include <d3d11.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")

namespace Khrysalis {
	RendererAPI::API RendererAPI::_API = RendererAPI::API::D3D11;

	std::unique_ptr<RendererAPI> RendererAPI::Create() {
		switch (_API) {
			case RendererAPI::API::None:    KAL_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
			case RendererAPI::API::D3D11:  return std::make_unique<D3D11Renderer>();
		}

		KAL_ENGINE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}