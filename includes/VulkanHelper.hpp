#ifndef HELLOTRIANGLEAPPLICATION_HPP
#define HELLOTRIANGLEAPPLICATION_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#define W_WIDTH 800
#define W_HEIGHT 600

class VulkanHelper
{
	private:
		GLFWwindow*	window;
		VkInstance	instance;

	public: void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

	private:
		void initWindow() {
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
		}

		void createInstance() {
			VkApplicationInfo	appInfo {};
			VkInstanceCreateInfo	createInfo {};
			uint32_t	glfwExtensionCount = 0;
			const char	**glfWextensions;

			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hello Triangle";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;
			glfWextensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfWextensions;
			createInfo.enabledLayerCount = 0;

			VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to create instance!");
			else if (result == VK_SUCCESS)
				std::cout << "Successfully created instance" << std::endl;

			uint32_t	extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
			std::vector<VkExtensionProperties>	extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
			std::cout << "available extensions:\n";

			for (std::vector<VkExtensionProperties>::iterator it = extensions.begin(); it != extensions.end(); it++)
				std::cout << '\t' << (*it).extensionName << std::endl;
		}

		void initVulkan() {
			createInstance();
		}

		void mainLoop() {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
			}
		}

		void cleanup() {
			vkDestroyInstance(instance, nullptr);

			glfwDestroyWindow(window);

			glfwTerminate();
		}
};

#endif