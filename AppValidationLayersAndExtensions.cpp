#include "AppValidationLayersAndExtensions.h"

AppValidationLayersAndExtensions::AppValidationLayersAndExtensions()
{ }

AppValidationLayersAndExtensions::~AppValidationLayersAndExtensions()
{ }

bool AppValidationLayersAndExtensions::checkValidationLayerSupport()
{
	uint32_t layerCount;

	// Get count of validation layers available
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	// Get the available validation layers names
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : requiredValidationLayers)
	{
		// layers we require
		// boolean to check if the layer was found
		bool layerFound = false;

		for (const auto& layerproperties : availableLayers)
		{
			// if layer is found set the layer found boolean to true
			if (strcmp(layerName, layerproperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		
		if (layerFound == false)
		{
			return false;
		}
		// TODO: ? because only standard here, ```requiredValidationLayers.size() == 1```
		//return true;
	}
	return true;
}

std::vector<const char*> AppValidationLayersAndExtensions::getRequiredExtensions(bool isValidationLayersEnabled)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	// get extensions
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	auto a = glfwExtensions + glfwExtensionCount;
	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);  // ? (const char**) as result ? address offset

	// debug report extension is added.
	if (isValidationLayersEnabled)
	{
		extensions.push_back("VK_EXT_debug_report");
	}

	return extensions;
}

// ? will generate a report message whenever there is an error
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objExt, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
{
	std::cerr << "validation layer: " << msg << std::endl;

	return false;
}

void AppValidationLayersAndExtensions::setupDebugCallback(bool isValidationLayersEnabled, VkInstance instance)
{
	if (!isValidationLayersEnabled)
	{
		return;
	}

	printf("setup callback \n");
	VkDebugReportCallbackCreateInfoEXT info = {};
	info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	info.pfnCallback = debugCallback;

	// vulkan will take care of memory allocation by itself.
	if (createDebugReportCallbackEXT(instance,   &info, nullptr, &callback) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to set debug callback!");
	}
}

void AppValidationLayersAndExtensions::destroy(VkInstance instance, bool isValidationLayersEnabled)
{
	if (!isValidationLayersEnabled)
	{
		return;
	}

	destroyDebugReportCallbackEXT(instance, callback, nullptr);
}
