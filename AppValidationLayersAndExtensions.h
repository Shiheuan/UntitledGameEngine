#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class AppValidationLayersAndExtensions
{
public:
	AppValidationLayersAndExtensions();
	~AppValidationLayersAndExtensions();

	const std::vector<const char*> requiredValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions(bool isValidationLayersEnabled);

	// debug callback
	VkDebugReportCallbackEXT callback;
	void setupDebugCallback(bool isValidationLayersEnabled, VkInstance instance);
	void destroy(VkInstance instance, bool isValidationLayersEnabled);

	// callback
	VkResult createDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
	{
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr)
		{
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr)
		{
			func(instance, callback, pAllocator);
		}
	}
};

