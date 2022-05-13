#include "Engine.hpp"

#include "utilities/Buffer.hpp"

namespace Spyder {

	void Engine::init(EngineInitParams initParams) {
		// initialization
		window.init(initParams.w, initParams.h, initParams.title);
		device.init();
		renderer.init();
		globalPool = DescriptorPool::Builder(device).setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT).addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT).build();

		// ubo buffers
		std::vector<std::unique_ptr<Buffer>> uboBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);
		for (auto &uboBuffer : uboBuffers) {
			uboBuffer = std::make_unique<Buffer>(device, sizeof(GlobalUbo), 1, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, device.physicalDeviceProperties.limits.minUniformBufferOffsetAlignment);
			uboBuffer->map();
		}

		auto globalSetLayout = DescriptorSetLayout::Builder(device).addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS).build();
		for (int i = 0; i < globalDescriptorSets.size(); ++i) {
			auto bufferInfo = uboBuffers[i]->descriptorInfo();
			DescriptorWriter(*globalSetLayout, *globalPool).writeBuffer(0, &bufferInfo).build(globalDescriptorSets[i]);
		}

		triangleRenderSystem.init(renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout());
		lineRenderSystem.init(renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout());
		vertexRenderSystem.init(renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout());
	}

	Window &Engine::getWindow() {
		return window;
	}

	void Engine::beginFrame() {
		glfwPollEvents();
		timeManagment.stepDeltaTime();
	}

	void Engine::endFrame() {
		if (auto commandBuffer = renderer.beginFrame()) {
			int frameIndex = renderer.getFrameIndex();
			FrameInfo frameInfo{frameIndex, getDeltaTime(), commandBuffer, globalDescriptorSets[frameIndex], triangleBatch, lineBatch, vertexBatch};
			// update

			// render
			renderer.beginSwapChainRenderPass(commandBuffer);

			triangleRenderSystem.render(frameInfo);
			lineRenderSystem.render(frameInfo);
			vertexRenderSystem.render(frameInfo);

			renderer.endSwapChainRenderPass(commandBuffer);
			renderer.endFrame();
		}
	}

	float Engine::getDeltaTime() {
		return timeManagment.getDeltaTime();
	}

	void Engine::close() {
		vkDeviceWaitIdle(device.device());
		triangleBatch.clear();
		lineBatch.clear();
		vertexBatch.clear();
	}
} // Spyder