#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanContext.h"
#include "Camera.h"
#include "ObjectRenderer.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "HELLO VULKAN", nullptr, nullptr);

	VulkanContext::getInstance()->initVulkan(window);

	Camera camera;
	camera.init(45.0f, 1280.0f, 720.0f, 0.1f, 10000.0f);
	camera.setCameraPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	ObjectRenderer object;
	object.createObjectRenderer(MeshType::kTriangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f));

	while (!glfwWindowShouldClose(window))
	{
		VulkanContext::getInstance()->drawBegin();
		// draw command 
		object.updateUniformBuffer(camera);
		object.draw();

		VulkanContext::getInstance()->drawEnd();

		glfwPollEvents();
	}

	object.destroy();

	VulkanContext::getInstance()->cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}