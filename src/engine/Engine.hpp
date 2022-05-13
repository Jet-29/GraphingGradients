#pragma once

#include "window/Window.hpp"
#include "engine/device/Device.hpp"
#include "rendering/Renderer.hpp"
#include "engine/rendering/render systems/TriangleRenderSystem.hpp"
#include "engine/rendering/render systems/LineRenderSystem.hpp"
#include "engine/rendering/render systems/VertexRenderSystem.hpp"
#include "utilities/descriptors/DescriptorWriter.hpp"
#include "engine/utilities/TimeManagment.hpp"
#include "engine/graphics/Drawable.hpp"

namespace Spyder {
	struct EngineInitParams {
		int w = 800;
		int h = 800;
		const char *title = "Spyder Engine";
		bool useDeltaTime = true;
	};

	class Engine {
	public:
		Engine() = default;
		~Engine() = default;

		void init(EngineInitParams initParams);

		Engine(const Engine &) = delete;
		Engine &operator=(const Engine &) = delete;
		[[nodiscard]] Window &getWindow();

		void beginFrame();
		void endFrame();
		float getDeltaTime();
		void close();

		// batching
		Batch triangleBatch{device};
		Batch lineBatch{device};
		Batch vertexBatch{device};

	private:

		Window window{};
		Device device{window};
		Renderer renderer{window, device};
		TimeManagment timeManagment{0.5f};

		// render systems
		TriangleRenderSystem triangleRenderSystem{device};
		LineRenderSystem lineRenderSystem{device};
		VertexRenderSystem vertexRenderSystem{device};

		std::vector<VkDescriptorSet> globalDescriptorSets{SwapChain::MAX_FRAMES_IN_FLIGHT};
		std::unique_ptr<DescriptorPool> globalPool{};
	};

} // Spyder