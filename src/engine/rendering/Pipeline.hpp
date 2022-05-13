#pragma once

#include "../device/Device.hpp"

namespace Spyder {

	struct PipelineConfigInfo {
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo &) = delete;
		PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

		std::vector<VkVertexInputBindingDescription> bindingDescriptions{};
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
		VkPipelineViewportStateCreateInfo viewportInfo{};
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
		VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo multisampleInfo{};
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
		std::vector<VkDynamicState> dynamicsStateEnables{};
		VkPipelineDynamicStateCreateInfo dynamicStateInfo{};
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class Pipeline {
	public:
		Pipeline(Device &device, const std::vector<uint32_t> &vertShaderArray, const std::vector<uint32_t> &fragShaderArray, const PipelineConfigInfo &configInfo);
		~Pipeline();

		Pipeline(const Pipeline &) = delete;
		Pipeline &operator=(const Pipeline &) = delete;

		void bind(VkCommandBuffer commandBuffer);
		static void defaultPipelineConfigInfo(PipelineConfigInfo &configInfo);
		static void enableAlphaBlending(PipelineConfigInfo &configInfo);

	private:
		void createGraphicsPipeline(const std::vector<uint32_t> &vertShaderArray, const std::vector<uint32_t> &fragShaderArray, const PipelineConfigInfo &configInfo);

		void createShaderModule(const std::vector<uint32_t> &code, VkShaderModule *shaderModule);

		Device &device;
		VkPipeline graphicsPipeline{};
		VkShaderModule vertShaderModule{};
		VkShaderModule fragShaderModule{};
	};

} // Spyder