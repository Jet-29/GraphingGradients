#pragma once

#include "engine/rendering/render systems/BaseRenderSystem.hpp"

namespace Spyder {

	class LineRenderSystem : BaseRenderSystem {
	public:
		explicit LineRenderSystem(Device &device);
		~LineRenderSystem();

		void init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) override;
		void render(FrameInfo &frameInfo) override;

	private:
		void setShaders(std::vector<uint32_t> &vertShader, std::vector<uint32_t> &fragShader) override;
		void setPipelineConfig(PipelineConfigInfo &pipelineLayout) override;

	};

} // Spyder