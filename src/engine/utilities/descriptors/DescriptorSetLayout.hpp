#pragma once

#include "../../device/Device.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace Spyder {

	class DescriptorSetLayout {
	public:
		class Builder {
		public:
			explicit Builder(Device &device) : device{device} {}

			Builder &addBinding(uint32_t binding, VkDescriptorType descriptorType, VkShaderStageFlags stageFlags, uint32_t count = 1);
			[[nodiscard]] std::unique_ptr<DescriptorSetLayout> build() const;

		private:
			Device &device;
			std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
		};

		DescriptorSetLayout(Device &device, const std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> &bindings);
		~DescriptorSetLayout();

		DescriptorSetLayout(const DescriptorSetLayout &) = delete;
		DescriptorSetLayout &operator=(const DescriptorSetLayout &) = delete;

		[[nodiscard]] VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

		std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
	private:
		Device &device;
		VkDescriptorSetLayout descriptorSetLayout{};

		friend class DescriptorWriter;
	};

} // Spyder