#include "TriangleRenderSystem.hpp"

#include "engine/rendering/shaders/SimpleRenderSystemShader.hpp"

namespace Spyder {
	TriangleRenderSystem::TriangleRenderSystem(Device &device) : BaseRenderSystem(device) {}

	TriangleRenderSystem::~TriangleRenderSystem() = default;

	void TriangleRenderSystem::render(FrameInfo &frameInfo) {
		if (frameInfo.triangleBatch.getCount() == 0) return;
		BaseRenderSystem::render(frameInfo);

		frameInfo.triangleBatch.getDrawable()->bind(frameInfo.commandBuffer);
		frameInfo.triangleBatch.getDrawable()->draw(frameInfo.commandBuffer);
	}

	void TriangleRenderSystem::init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) {
		BaseRenderSystem::init(renderPass, globalSetLayout);
	}

	void TriangleRenderSystem::setShaders(std::vector<uint32_t> &vertShader, std::vector<uint32_t> &fragShader) {
		vertShader = SimpleRenderSystemShader::vert;
		fragShader = SimpleRenderSystemShader::frag;
	}

	void TriangleRenderSystem::setPipelineConfig(PipelineConfigInfo &pipelineLayout) {

	}
} // Spyder