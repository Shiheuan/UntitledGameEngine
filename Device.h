#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept> // TODO: ?
#include <iostream>
#include <vector>
#include <set> // TODO: ?

#include "VulkanInstance.h"
#include "AppValidationLayersAndExtensions.h"

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR surfaceCapabilities; // size and images in swapchain
	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool arePresent()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

class Device
{
public:
	Device();
	~Device();

	// +++++++++++++++
	// Physical device
	// +++++++++++++++

	VkPhysicalDevice physicalDevice;
	SwapChainSupportDetails swapchainSupport;
	QueueFamilyIndices queueFamilyIndices;

	std::vector<const char*> deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	void pickPhysicalDevice(VulkanInstance* vInstance, VkSurfaceKHR surface);
	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
	bool checkDeviceExtensionSupported(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
	QueueFamilyIndices getQueueFamiliesIndicesOfCurrentDevice();

	// ++++++++++++++
	// Logical device
	// ++++++++++++++

	void createLogicalDevice(VkSurfaceKHR surface, bool isValidationLayersEnabled, AppValidationLayersAndExtensions* appValLayersAndExtensions);
	VkDevice logicalDevice;

	// handle to the graphics queue from the queue families fo the gpu
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	void destroy();
};

