#include "src/utils/timer.h"
#include "src/graphics/window.h"

#include "src/graphics/renderables/sprite.h"
#include "src/graphics/renderables/label.h"

#include "src/graphics/layers/tileLayer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"

int main() {
	using namespace GXDEngine;
	using namespace GXDEngine::graphics;
	using namespace GXDEngine::maths;

	//Window window("GXDEngine", 1366, 786);
	Window window("GXDEngine", 960, 540);
	//glClearColor(0.5f, 0.8f, 0.2f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("wall.png"),
		new Texture("t3.png")
	};

			int col = 0xff22ff;
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			//	layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			int r = rand() % 256;

			//if (rand() % 4 == 0)
			//	layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			//else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 2]));
		}
	}

	//Group* g = new Group(mat4::translation(vec3(-15.8f, 7.0f, 0.0f)));
	//Font* font = new Font("SourceSansPro", "SourceSansPro-Light.ttf", 32);
	//Label* fps = new Label(0.4f, 0.4f, 0xffffffff, font,"" );
	//g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	//g->add(fps);

	//layer.add(g);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", 10, texIDs);
	shader.setUniformMat4("pr_matrix", mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;
	while (!window.closed())
	{
		t += 0.001f;
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		//shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render();

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			//fps->setText(frames + " fps");
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	for (int i = 0; i < 3; i++)
		delete textures[i];

	return 0;
}