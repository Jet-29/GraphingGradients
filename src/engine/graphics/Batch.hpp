#pragma once

#include "Drawable.hpp"

namespace std {
	template<>
	struct hash<Spyder::Drawable::Vertex> {
		size_t operator()(Spyder::Drawable::Vertex const &vertex) const;
	};
}

namespace Spyder {

	class Batch {
	public:
		explicit Batch(Device &device);
		void addToBatch(const std::vector<Drawable::Vertex> &newVertices);
		void addToBatch(const Drawable::Vertex &newVertex);
		void clear();

		[[nodiscard]] const std::unique_ptr<Drawable> &getDrawable();

		uint32_t getCount();

	private:
		void recreateDrawable();

		std::unordered_map<Drawable::Vertex, uint32_t> uniqueVertices{};
		std::vector<Drawable::Vertex> vertices{};
		std::vector<uint32_t> indices{};
		Device &device;
		std::unique_ptr<Drawable> drawable{};

		bool updated = false;
	};

} // Spyder