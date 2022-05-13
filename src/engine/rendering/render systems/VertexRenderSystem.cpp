#include "VertexRenderSystem.hpp"

#include "engine/rendering/shaders/SimpleRenderSystemShader.hpp"

namespace Spyder {
	VertexRenderSystem::VertexRenderSystem(Device &device) : BaseRenderSystem(device) {}

	VertexRenderSystem::~VertexRenderSystem() = default;

	void VertexRenderSystem::render(FrameInfo &frameInfo) {
		if (frameInfo.vertexBatch.getCount() == 0) return;
		BaseRenderSystem::render(frameInfo);
		frameInfo.vertexBatch.getDrawable()->bind(frameInfo.commandBuffer);
		frameInfo.vertexBatch.getDrawable()->draw(frameInfo.commandBuffer);

	}

	void VertexRenderSystem::init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) {
		BaseRenderSystem::init(renderPass, globalSetLayout);
	}

	void VertexRenderSystem::setShaders(std::vector<uint32_t> &vertShader, std::vector<uint32_t> &fragShader) {
		vertShader = SimpleRenderSystemShader::vert;
		fragShader = SimpleRenderSystemShader::frag;
	}

	void VertexRenderSystem::setPipelineConfig(PipelineConfigInfo &pipelineLayout) {
		pipelineLayout.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
	}
} // Spyder