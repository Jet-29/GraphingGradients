#pragma once

#include "engine/rendering/render systems/BaseRenderSystem.hpp"

namespace Spyder {

	class TriangleRenderSystem : BaseRenderSystem {
	public:
		explicit TriangleRenderSystem(Device &device);
		~TriangleRenderSystem();

		void init(VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) override;
		void render(FrameInfo &frameInfo) override;

	private:
		void setShaders(std::vector<uint32_t> &vertShader, std::vector<uint32_t> &fragShader) override;
		void setPipelineConfig(PipelineConfigInfo &pipelineLayout) override;

	};

} // Spyder