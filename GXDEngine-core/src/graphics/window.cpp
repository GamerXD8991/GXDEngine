// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "window.h"
#include "../debug.h"

namespace GXDEngine {
	namespace graphics {

		//declare
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		//implement
		Window::Window(const char* title, int width, int height) 
			: m_name(title),	m_Width(width),	m_Height(height) {
			if (!Init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}



		void Window::update() {

			for (int i = 0; i < MAX_KEYS; ++i) {
				m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
			}

			for (int i = 0; i < MAX_BUTTONS; ++i) {
				m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];
			}

			A_memcpy(m_KeyState, m_Keys, MAX_KEYS);
			A_memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);

			const GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		void Window::clear() const  {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if _GXDE_ENABLE_DEBUG
			const GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "glClear Error: " << error << std::endl;
#endif
		}

		bool Window::closed() const  {
			return glfwWindowShouldClose(m_window) == 1;
		}



		int Window::getWidth() const  {
			return m_Width;
		}

		int Window::getHeight() const  {
			return m_Height;
		}

		void Window::setWidth(int width)  {
			m_Width = width;
		}

		void Window::setHeight(int height)  {
			m_Height = height;
		}



		bool Window::isKeyPressed(unsigned int keycode) const  {
			bool res = false;
			if (keycode < MAX_KEYS)
				res = m_Keys[keycode];

			return res;
		}

		bool Window::isKeyTyped(unsigned int keycode) const  {
			bool res = false;
			if (keycode < MAX_KEYS)
				res = m_KeyTyped[keycode];
			return res;
		}



		bool Window::isMouseButtonPressed(unsigned int button) const  {
			bool res = false;
			if (button < MAX_BUTTONS)
				res = m_MouseButtons[button];
			return res;
		}

		bool Window::isMouseButtonClicked(unsigned int button) const  {
			bool res = false;
			if (button < MAX_BUTTONS)
				res = m_MouseClicked[button];
			return res;
		}

		void Window::getMousePosition(double& x, double& y) const  {
			x = m_x;
			y = m_y;
		}



		bool Window::Init() {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_Width, m_Height, m_name, NULL, NULL);
			if (!m_window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);

			glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);

			glfwSwapInterval(0);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			return true;
		}



		void framebuffer_size_callback(GLFWwindow* window, int width, int height)  {
			Window* wind = (Window*)glfwGetWindowUserPointer(window);

			wind->m_Width = width;
			wind->m_Height = height;

			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)  {
			Window* wind = (Window*)glfwGetWindowUserPointer(window);
			if (key < MAX_KEYS) wind->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)  {
			Window* wind = (Window*)glfwGetWindowUserPointer(window);
			if (button < MAX_BUTTONS) wind->m_MouseButtons[button] = action != GLFW_RELEASE;

		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)  {
			Window* wind = (Window*)glfwGetWindowUserPointer(window);
			wind->m_x = xpos;
			wind->m_y = ypos;
		}

} }