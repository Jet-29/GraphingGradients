#pragma once

#include <vulkan/vulkan.hpp>
#include "engine/graphics/Batch.hpp"

namespace Spyder {

	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		VkDescriptorSet globalDescriptorSet;
		Batch &triangleBatch;
		Batch &lineBatch;
		Batch &vertexBatch;
	};

	struct GlobalUbo {
		int star = 0;
	};
}