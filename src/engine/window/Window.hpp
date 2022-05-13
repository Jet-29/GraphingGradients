#pragma once

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace Spyder {

	class Window {
	public:
		Window();
		~Window();

		void init(int w, int h, const char *t);

		Window(const Window &) = delete;
		Window &operator=(const Window &) = delete;

		[[nodiscard]] bool shouldClose() const;
		[[nodiscard]] const VkExtent2D &getWindowExtent() const;
		[[nodiscard]] bool wasWindowResized() const;
		[[nodiscard]] GLFWwindow *getWindow();
		void resetWindowResizedFlag();
		void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
		void setBackground(VkClearColorValue newColor);
		[[nodiscard]] VkClearColorValue &getBackgroundColor();

	private:
		static void frameBufferResizedCallback(GLFWwindow *window, int width, int height);

		GLFWwindow *window = nullptr;
		VkExtent2D windowExtent{};
		bool frameBufferResized = false;
		VkClearColorValue backgroundColor{};

		const char *title{};

	};

} // Spyder