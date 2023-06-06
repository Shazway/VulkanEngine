#ifndef HELLOTRIANGLEAPPLICATION_HPP
#define HELLOTRIANGLEAPPLICATION_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include "Colors.hpp"
#define W_WIDTH 800
#define W_HEIGHT 600

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
#define VALIDATIONLAYER 1
#else
#define VALIDATIONLAYER 0
#endif

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

		bool checkValidationLayersupport() {
			uint32_t	layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties>	availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
			for (const char *layerName: validationLayers) {
				bool layerFound = false;

				for (const VkLayerProperties& layerProperties : availableLayers)
				{
					if (strcmp(layerName, layerProperties.layerName) == 0)
					{
						layerFound = true;
						break ;
					}
				}
				if (!layerFound)
					return false;
			}
			return true;
		}

		void createInstance() {
			if (VALIDATIONLAYER && !checkValidationLayersupport())
				throw std::runtime_error("Validation layers requested but not available!");
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

			uint32_t	extensionsCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
			std::vector<VkExtensionProperties>	extensions(extensionsCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());
			std::cout << "Available instance extensions:" << std::endl;

			for (std::vector<VkExtensionProperties>::iterator it = extensions.begin(); it != extensions.end(); it++)
				std::cout << '\t' << C_BLUE << (*it).extensionName << C_END << std::endl;
			std::cout << C_WHITE << "GLFW extensions: " << C_END << std::endl;
			for (uint32_t i = 0; i < glfwExtensionCount; i++)
				std::cout << "\t" << C_GREEN << glfWextensions[i] << C_END << std::endl;
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