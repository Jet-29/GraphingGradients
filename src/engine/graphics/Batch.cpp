#include "Batch.hpp"

//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "engine/utilities/HashCombine.cpp"

size_t std::hash<Spyder::Drawable::Vertex>::operator()(const Spyder::Drawable::Vertex &vertex) const {
	size_t seed = 0;
	Spyder::Utilities::hashCombine(seed, vertex.position, vertex.color);
	return seed;
}

namespace Spyder {
	Batch::Batch(Device &device) : device{device} {
		drawable = std::make_unique<Drawable>(device);
	}

	void Batch::addToBatch(std::vector<Drawable::Vertex> &newVertices) {
		for (Drawable::Vertex &vertex : newVertices) {
			addToBatch(vertex);
		}
	}

	void Batch::addToBatch(Drawable::Vertex &newVertex) {
		if (uniqueVertices.count(newVertex) == 0) {
			uniqueVertices[newVertex] = static_cast<uint32_t>(vertices.size());
			vertices.push_back(newVertex);
		}
		indices.push_back(uniqueVertices[newVertex]);
		updated = true;
	}

	void Batch::clear() {
		uniqueVertices.clear();
		vertices.clear();
		indices.clear();
		drawable.reset();
		updated = true;
	}

	void Batch::recreateDrawable() {
		drawable = std::make_unique<Drawable>(device);
		drawable->init(vertices, indices);
	}

	const std::unique_ptr<Drawable> &Batch::getDrawable() {
		if (updated) {
			recreateDrawable();
			updated = false;
		}
		return drawable;
	}

	uint32_t Batch::getCount() {
		return vertices.size();
	}
} // Spyder