#pragma once

#include "../../device/Device.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace Spyder {

	class DescriptorPool {

	public:
		class Builder {
		public:
			explicit Builder(Device &device) : device{device} {}

			Builder &addPoolSize(VkDescriptorType descriptorType, uint32_t count);
			Builder &setPoolFlags(VkDescriptorPoolCreateFlags flags);
			Builder &setMaxSets(uint32_t count);
			[[nodiscard]] std::unique_ptr<DescriptorPool> build() const;

		private:
			Device &device;
			std::vector<VkDescriptorPoolSize> poolSizes{};
			uint32_t maxSets = 1000;
			VkDescriptorPoolCreateFlags poolFlags = 0;
		};

		DescriptorPool(Device &device, uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize> &poolSizes);
		~DescriptorPool();

		DescriptorPool(const DescriptorPool &) = delete;
		DescriptorPool &operator=(const DescriptorPool &) = delete;

		bool allocateDescriptor(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;
		void freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const;
		void resetPool();

	private:
		Device &device;
		VkDescriptorPool descriptorPool{};

		friend class DescriptorWriter;
	};

} // Spyder