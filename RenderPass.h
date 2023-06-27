#pragma once
#include <vulkan/vulkan.h>
#include <array>

class RenderPass
{
public:
	RenderPass();
	~RenderPass();

	VkRenderPass renderPass;

	void createRenderPass(VkFormat swapChainImageFormat);
	void beginRenderPass(std::array<VkClearValue, 1> clearValues, VkCommandBuffer commandBuffer, VkFramebuffer swapChainFrameBuffer, VkExtent2D swapChainImageExtent);
	void endRenderPass(VkCommandBuffer commandBuffer);

	void destroy();
};

