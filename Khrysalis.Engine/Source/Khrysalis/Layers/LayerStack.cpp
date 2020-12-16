#include "KalPch.h"
#include "Khrysalis/Layers/LayerStack.h"

namespace Khrysalis {
	LayerStack::~LayerStack() {
		for (Layer* layer : _layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
		_layerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		_layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto iterator = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);

		if (iterator != _layers.begin() + _layerInsertIndex) {
			layer->OnDetach();
			_layers.erase(iterator);
			_layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto iterator = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);

		if (iterator != _layers.begin() + _layerInsertIndex) {
			overlay->OnDetach();
			_layers.erase(iterator);
		}
	}
}