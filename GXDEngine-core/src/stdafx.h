#pragma once
#pragma optimize( "f", on )
//std
#include <iostream>
#include <string>
#include <vector>
#include <deque>

//dependencies
#include <asmlib.h>

#include <GL/glew.h>
#include <gl/wglew.h>

#include <GLFW/glfw3.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <FreeImage.h>

#include <FreeType-GL/opengl.h>
#include <FreeType-GL/freetype-gl.h>

//own header
#include "utils/FileUtils.h"
#include "utils/Timer.h"
#include "utils/ImgLoad.h"

#include "maths/maths.h"
#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/vec4.h"
#include "maths/mat4.h"

#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexArray.h"

//main .cpp includes
#include <future>
#include "graphics/window.h"

#include "graphics/renderables/sprite.h"
#include "graphics/renderables/label.h"

#include "graphics/layers/tileLayer.h"
#include "graphics/layers/group.h"

#include "graphics/texture.h"