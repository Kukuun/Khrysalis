#include "KalPch.h"

#include "Khrysalis/Graphics/Renderer.h"

namespace Khrysalis {
	std::unique_ptr<RendererAPI> Renderer::_API = RendererAPI::Create();
}