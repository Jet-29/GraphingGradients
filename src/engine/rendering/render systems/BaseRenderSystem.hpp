#pragma once

#include "engine/device/Device.hpp"
#include "engine/rendering/FrameInfo.hpp"
#include "engine/rendering/Pipeline.hpp"

namespace Spyder {

	class BaseRenderSystem {
	public:
		explicit BaseRenderSystem(Device &device);
		virtual ~BaseRenderSystem();

		virtual void init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);

		BaseRenderSystem(const BaseRenderSystem &) = delete;
		BaseRenderSystem &operator=(const BaseRenderSystem &) = delete;

		virtual void render(FrameInfo &frameInfo);

	private:
		virtual void setPipelineConfig(PipelineConfigInfo &pipelineLayout) = 0;
		virtual void setShaders(std::vector<uint32_t> &vertShader, std::vector<uint32_t> &fragShader) = 0;

		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);

		Device &device;

		std::vector<uint32_t> vertShader{};
		std::vector<uint32_t> fragShader{};

		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout{};
	};

} // Spyder