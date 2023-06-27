#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "AppValidationLayersAndExtensions.h"
#include "VulkanInstance.h"
#include "Device.h"
#include "SwapChain.h"
#include "RenderPass.h"
#include "RenderTarget.h"
#include "DrawCommandBuffer.h"

#ifdef _DEBUG
const bool isValidationLayersEnabled = true;
#else
const bool isValidationLayersEnabled = false;
#endif

class VulkanContext
{
public:
	static VulkanContext* getInstance();
	static VulkanContext* instance;

	~VulkanContext();
	void initVulkan(GLFWwindow* window);

	Device* getDevice();
	SwapChain* getSwapChain();
	RenderPass* getRenderPass();
	VkCommandBuffer getCurrentCommandBuffer();

	void drawBegin();
	void drawEnd();
	void cleanup();
private:
	AppValidationLayersAndExtensions* valLayersAndExt;
	VulkanInstance* vInstance;
	Device* device;

	// surface
	VkSurfaceKHR surface;

	SwapChain* swapChain;
	RenderPass* renderPass;
	RenderTarget* renderTarget;
	DrawCommandBuffer* drawCommandBuffer;

	uint32_t imageIndex = 0;
	VkCommandBuffer currentCommandBuffer;

	const int MAX_FRAMES_IN_FLIGHT = 2;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	std::vector<VkFence> inFlightFences;
};

