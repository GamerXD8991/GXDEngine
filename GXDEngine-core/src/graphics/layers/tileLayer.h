#pragma once
#pragma optimize( "f", on )

#include "layer.h"

namespace GXDEngine { namespace graphics {

	class TileLayer : public Layer {

	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};

} }