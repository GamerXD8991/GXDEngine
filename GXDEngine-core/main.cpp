// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "src/stdafx.h"
#include "src/graphics/fontManager.h"
#include <thread>
#include <charconv>
#include <array>

static void framerate(unsigned int& frames, GXDEngine::graphics::Label*  fps, bool &running) {
	using namespace std::literals::chrono_literals;
	GXDEngine::Timer time;
	float timer = 0;
	rapidstring strFps;
	std::array<char, 8> txt;
	while (running) {
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			std::to_chars(txt.data(), txt.data() + txt.size(), frames);
			strcat(txt.data()," fps");
			rs_init_w(&strFps, txt.data());
			//fps->setText(std::to_string(frames) + " fps");
			fps->setText(strFps);
			printf("%u fps\n", frames);
			frames = 0;
		}
		std::this_thread::sleep_for(1s);
	}
}

int main() {
	using namespace GXDEngine;
	using namespace GXDEngine::graphics;
	using namespace GXDEngine::maths;

	//Window window("GXDEngine", 1366, 786);
	Window window("GXDEngine", 960, 540);
	//glClearColor(0.5f, 0.8f, 0.2f, 1.0f);

	Shader* shaderTexture = new Shader("src/shaders/basicTexture.vert", "src/shaders/basicTexture.frag");
	GLint texID1s[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	};
	GLint texID2s[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
	};
	mat4 ortho = mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
	
	shaderTexture->enable();
	shaderTexture->setUniform2f("light_pos", vec2(0.0f, 0.0f));
	shaderTexture->setUniformMat4("pr_matrix", ortho);
	shaderTexture->setUniform1iv("textures", 10, texID2s);
	shaderTexture->disable();

	//TileLayer layer(shaderTexture);

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("wall.png"),
		new Texture("t3.png")
	};

	unsigned int colors[] = {
		0xffff0000,
		0xff00ff00,
		0xff0000ff
	};

	for (float y = -9.0f; y < 9.0f; y+=3)
	//for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x+=4)
		//for (float x = -16.0f; x < 16.0f; x++)
		{
				//layer.add(new Sprite(x, y, 3*0.9f, 3*0.9f, textures[rand() % 2]));
				//layer.add(new Sprite(x, y, 3*0.9f, 3*0.9f, colors[rand() % 2]));
		}
	}
	
	Shader* shaderText = new Shader("src/shaders/basicText.vert", "src/shaders/basicText.frag");
	//Shader* shaderText = shaderTexture;


	shaderText->enable();
	shaderText->setUniformMat4("pr_matrix", ortho);
	shaderText->setUniform1iv("text", 32, texID2s);
	shaderText->disable();


	TileLayer layerText(shaderText);

	FontManager::add(new Font("SourceSansPro", "SourceSansPro-Regular.ttf", 32));
	//FontManager::add("SourceSansPro", "SourceSansPro-Regular.ttf", 32);

	Group* g = new Group(mat4::translation(vec3(-15.8f, 7.0f, 0.0f)));
	rapidstring defaultFps;
	rs_init_w_n(&defaultFps, "9999 fps", 8);
	Label* fps = new Label(0.4f, 0.4f, 0xff00ff00, FontManager::get("SourceSansPro"), defaultFps);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x8fe5e5e5));
	g->add(fps);
	layerText.add(g);

	unsigned int frames = 0;
	bool running = true;
	auto fR = std::async(std::launch::async, [&] { framerate(frames, fps, running); });

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shaderTexture->enable();
		shaderTexture->setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		shaderTexture->disable();

		//layer.render();
		layerText.render();

		window.update();
		frames++;
	}
	running = false;
	for (int i = 0; i < 3; i++)
		delete textures[i];

	FontManager::clean();

	return 0;
}