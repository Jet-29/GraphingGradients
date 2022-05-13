#pragma once

#include "../../device/Device.hpp"
#include "DescriptorSetLayout.hpp"
#include "DescriptorPool.hpp"

namespace Spyder {

	class DescriptorWriter {
	public:
		DescriptorWriter(DescriptorSetLayout &setLayout, DescriptorPool &pool);

		DescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);
		DescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);

		bool build(VkDescriptorSet &set);
		void overwrite(VkDescriptorSet &set);

	private:
		DescriptorSetLayout &setLayout;
		DescriptorPool &pool;
		std::vector<VkWriteDescriptorSet> writes;
	};

} // Spyder