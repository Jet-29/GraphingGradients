#pragma once

#include "../device/Device.hpp"
#include "../utilities/Buffer.hpp"

#include <glm/glm.hpp>

namespace Spyder {

	class Drawable {
	public:
		struct Vertex {
			glm::vec2 position;
			glm::vec4 color;
			float pointSize = 1.0f;

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex &other) const;
		};

		explicit Drawable(Device &device);
		~Drawable() = default;

		void init(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

		Drawable(const Drawable &) = delete;
		Drawable &operator=(const Drawable &) = delete;

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer) const;

	private:
		void createVertexBuffers(const std::vector<Vertex> &vertices);
		void createIndexBuffers(const std::vector<uint32_t> &indices);

		Device &device;

		std::unique_ptr<Buffer> vertexBuffer;
		uint32_t vertexCount{};

		bool hasIndexBuffer = false;

		std::unique_ptr<Buffer> indexBuffer;
		uint32_t indexCount{};
	};

} // Spyder