#pragma once

#include "engine/device/Device.hpp"

namespace Spyder {

	class SwapChain {
	public:
		static constexpr int MAX_FRAMES_IN_FLIGHT = 3;

		SwapChain(Device &device, VkExtent2D windowExtent);
		SwapChain(Device &device, VkExtent2D windowExtent, std::shared_ptr<SwapChain> previous);
		~SwapChain();

		SwapChain(const SwapChain &) = delete;
		SwapChain &operator=(const SwapChain &) = delete;

		// getters
		VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }

		VkRenderPass getRenderPass() { return renderPass; }

		VkImageView getImageView(int index) { return swapChainImageViews[index]; }

		size_t imageCount() { return swapChainImages.size(); }

		VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }

		VkExtent2D getSwapChainExtent() { return swapChainExtent; }

		[[nodiscard]] uint32_t width() const { return swapChainExtent.width; }

		[[nodiscard]] uint32_t height() const { return swapChainExtent.height; }

		[[nodiscard]] float extentAspectRatio() const {
			return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
		}


		VkFormat findDepthFormat();
		VkResult acquireNextImage(uint32_t *imageIndex);
		VkResult submitCommandBuffers(const VkCommandBuffer *buffers, const uint32_t *imageIndex);
		[[nodiscard]] bool compareSwapFormats(const SwapChain &swapChainToCompare) const;

	private:
		void init();
		void createSwapChain();
		void createImageViews();
		void createDepthResources();
		void createRenderPass();
		void createFramebuffers();
		void createSyncObjects();

		// Helper functions
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		VkFormat swapChainImageFormat{};
		VkFormat swapChainDepthFormat{};
		VkExtent2D swapChainExtent{};

		std::vector<VkFramebuffer> swapChainFramebuffers{};
		VkRenderPass renderPass{};

		std::vector<VkImage> depthImages{};
		std::vector<VkDeviceMemory> depthImageMemorys{};
		std::vector<VkImageView> depthImageViews{};
		std::vector<VkImage> swapChainImages{};
		std::vector<VkImageView> swapChainImageViews{};

		Device &device;
		VkExtent2D windowExtent{};

		VkSwapchainKHR swapChain{};
		std::shared_ptr<SwapChain> oldSwapChain{};

		std::vector<VkSemaphore> imageAvailableSemaphores{};
		std::vector<VkSemaphore> renderFinishedSemaphores{};
		std::vector<VkFence> inFlightFences{};
		std::vector<VkFence> imagesInFlight{};
		size_t currentFrame = 0;
	};

} // Spyder