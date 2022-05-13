#include "LineRenderSystem.hpp"

#include "engine/rendering/shaders/SimpleRenderSystemShader.hpp"

namespace Spyder {
	LineRenderSystem::LineRenderSystem(Device &device) : BaseRenderSystem(device) {}

	LineRenderSystem::~LineRenderSystem() = default;

	void LineRenderSystem::render(FrameInfo &frameInfo) {
		if (frameInfo.lineBatch.getCount() == 0) return;
		BaseRenderSystem::render(frameInfo);
		frameInfo.lineBatch.getDrawable()->bind(frameInfo.commandBuffer);
		frameInfo.lineBatch.getDrawable()->draw(frameInfo.commandBuffer);
	}

	void LineRenderSystem::init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) {
		BaseRenderSystem::init(renderPass, globalSetLayout);
	}

	void LineRenderSystem::setShaders(std::vector<uint32_t> &vertShader, std::vector<uint32_t> &fragShader) {
		vertShader = SimpleRenderSystemShader::vert;
		fragShader = SimpleRenderSystemShader::frag;
	}

	void LineRenderSystem::setPipelineConfig(PipelineConfigInfo &pipelineLayout) {
		pipelineLayout.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	}
} // Spyder