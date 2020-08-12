#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "tileLayer.h"
#include "../renderers/batchRenderer2D.h"

namespace GXDEngine { namespace graphics {


	TileLayer::TileLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0, 9.0f, -1.0f, 1.0f)) {
	}
	TileLayer::~TileLayer() {

	}


} }