#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"

namespace GXDEngine { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


	class Window
	{	
	private:
		GLFWwindow* m_window;
		const char* m_name;
		int m_Width, m_Height;
			
		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];

		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		double m_x;
		double m_y;

	public:
		Window(const char* title, int width, int height);
		~Window();

		void update();
		void clear() const;
		bool closed() const;

		int getWidth() const;
		int getHeight() const;
		void setWidth(int height);
		void setHeight(int height);
		
		bool isKeyPressed(unsigned int keycode) const;
		bool isKeyTyped(unsigned int keycode) const;

		bool isMouseButtonPressed(unsigned int keycode) const;
		bool isMouseButtonClicked(unsigned int keycode) const;
		void getMousePosition(double& x, double& y) const;

	private:
		bool Init();

		friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
} }