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
#include "engine/utilities/FpsDisplay.hpp"

namespace Spyder {
	struct EngineInitParams {
		int w = 800;
		int h = 800;
		const char *title = "Spyder Engine";
		bool printFps = false;
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
		EngineInitParams engineInitParams{};

		Window window{};
		Device device{window};
		Renderer renderer{window, device};
		TimeManagment timeManagement{0.5f};
		FpsDisplay fpsDisplay{5.0f, 10.0f};

		// render systems
		TriangleRenderSystem triangleRenderSystem{device};
		LineRenderSystem lineRenderSystem{device};
		VertexRenderSystem vertexRenderSystem{device};

		std::vector<VkDescriptorSet> globalDescriptorSets{SwapChain::MAX_FRAMES_IN_FLIGHT};
		std::unique_ptr<DescriptorPool> globalPool{};
	};

} // Spyder