#pragma once

#include "Khrysalis/Graphics/RendererAPI.h"

namespace Khrysalis {
	class Renderer {
	public:
		static void Initialize() {
			_API->Initialize();
		}

		static void Clear(const float red = 0.0f, const float green = 0.0f, const float blue = 1.0f) {
			_API->Clear(red, green, blue);
		}

		static void Submit(std::vector<float> vertices) {
			_API->Submit(vertices);
		}

		static void Shutdown() {
			_API->Shutdown();
		}

		static void SwapBuffers() {
			_API->SwapBuffers();
		}

		static void SetVsync(bool isVsync) {
			_API->SetVsync(isVsync);
		}

		static void Resize(uint16_t width, uint16_t height) {
			_API->Resize(width, height);
		}

		static RendererAPI* Get() { return _API.get(); }
		static RendererAPI::API GetAPI() { return _API->GetAPI(); }

	private:
		static std::unique_ptr<RendererAPI> _API;
	};
}