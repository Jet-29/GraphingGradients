#pragma once

#include "../window/Window.hpp"
#include "../device/Device.hpp"
#include "SwapChain.hpp"

namespace Spyder {

	class Renderer {
	public:
		Renderer(Window &window, Device &device);
		~Renderer();

		void init();

		Renderer(const Renderer &) = delete;
		Renderer &operator=(const Renderer &) = delete;

		// getters
		[[nodiscard]] VkRenderPass getSwapChainRenderPass() const;
		[[nodiscard]] float getAspectRatio() const;
		[[nodiscard]] bool isFrameInProgress() const;
		[[nodiscard]] VkCommandBuffer getCurrentCommandBuffer() const;
		[[nodiscard]] int getFrameIndex() const;

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer) const;
	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();

		Window &window;
		Device &device;
		std::unique_ptr<SwapChain> swapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex{};
		int currentFrameIndex{0};
		bool isFrameStarted;
	};

} // Spyder