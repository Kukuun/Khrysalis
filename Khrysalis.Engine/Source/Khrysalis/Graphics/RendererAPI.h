#pragma once

#include "Khrysalis/Core/Window.h"

namespace Khrysalis {
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			D3D11 = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Initialize() = 0;
		virtual void Clear(const float red = 1.0f, const float green = 1.0f, const float blue = 1.0f) = 0;
		virtual void Submit(std::vector<float> vertices) = 0;
		virtual void SwapBuffers() = 0;
		virtual void Resize(uint16_t width, uint16_t height) = 0;
		virtual void Shutdown() = 0;

		virtual void SetVsync(bool isVsync) = 0;

		static API GetAPI() { return _API; }
		static std::unique_ptr<RendererAPI> Create();

	private:
		static API _API;
	};
}