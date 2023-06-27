#pragma once

#include <vulkan/vulkan.h>
#include "AppValidationLayersAndExtensions.h"

class VulkanInstance
{
public:
	VulkanInstance();
	~VulkanInstance();

	VkInstance vkInstance;
	void createAppAndVkInstance(bool enableValidationLayers, AppValidationLayersAndExtensions* valLayersAndExtensions);
};

