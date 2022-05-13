#include "BaseRenderSystem.hpp"

namespace Spyder {
	BaseRenderSystem::BaseRenderSystem(Device &device) : device{device} {}

	BaseRenderSystem::~BaseRenderSystem() {
		vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
	}

	void BaseRenderSystem::init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) {
		createPipelineLayout(globalSetLayout);
		createPipeline(renderPass);
	}

	void BaseRenderSystem::render(FrameInfo &frameInfo) {
		pipeline->bind(frameInfo.commandBuffer);
		vkCmdBindDescriptorSets(frameInfo.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &frameInfo.globalDescriptorSet, 0, nullptr);
	}

	void BaseRenderSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
		// Todo: push constants
//		VkPushConstantRange pushConstantRange{};
//		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
//		pushConstantRange.offset = 0;
//		pushConstantRange.size = sizeof(SimplePushConstantData);

		std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout};

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
		pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr; // Todo: push constants

		if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout");
		}
	}

	void BaseRenderSystem::createPipeline(VkRenderPass renderPass) {
		assert(pipelineLayout != nullptr && "cant create pipeline before pipeline layout");
		PipelineConfigInfo pipelineConfig{};
		Pipeline::defaultPipelineConfigInfo(pipelineConfig);
		setPipelineConfig(pipelineConfig);
		setShaders(vertShader, fragShader);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;

		pipeline = std::make_unique<Pipeline>(device, vertShader, fragShader, pipelineConfig);

	}
} // Spyder