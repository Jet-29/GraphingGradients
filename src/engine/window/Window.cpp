#include "Window.hpp"

namespace Spyder {
	Window::Window() = default;

	void Window::init(int w, int h, const char *t) {
		if (window) return;
		windowExtent.width = w;
		windowExtent.height = h;
		title = t;
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

		window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, frameBufferResizedCallback);
	}

	Window::~Window() = default;

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(window);
	}

	const VkExtent2D &Window::getWindowExtent() const {
		return windowExtent;
	}

	bool Window::wasWindowResized() const {
		return frameBufferResized;
	}

	GLFWwindow *Window::getWindow() {
		return window;
	}

	void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface");
		}
	}

	void Window::frameBufferResizedCallback(GLFWwindow *openWindow, int width, int height) {
		auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(openWindow));
		window->frameBufferResized = true;
		window->windowExtent.width = width;
		window->windowExtent.height = height;
	}

	void Window::setBackground(VkClearColorValue newColor) {
		backgroundColor = newColor;
	}

	VkClearColorValue &Window::getBackgroundColor() {
		return backgroundColor;
	}

	void Window::resetWindowResizedFlag() {
		frameBufferResized = false;
	}

} // Spyder