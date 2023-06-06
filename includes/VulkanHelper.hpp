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
		VkDebugUtilsMessengerEXT	debugMessenger;

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

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData)
		{
			if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
				std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
			return VK_FALSE;
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

		std::vector<const char*> getRequiredExtensions() {
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

			if (VALIDATIONLAYER)
				extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			return extensions;
		}

		void createInstance() {
			if (VALIDATIONLAYER && !checkValidationLayersupport())
				throw std::runtime_error("Validation layers requested but not available!");
			VkApplicationInfo	appInfo {};
			VkInstanceCreateInfo	createInfo {};
			std::vector<const char *>	extensions = getRequiredExtensions();

			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hello Triangle";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			createInfo.pApplicationInfo = &appInfo;
			createInfo.enabledExtensionCount = extensions.size();
			createInfo.ppEnabledExtensionNames = extensions.data();

			if (VALIDATIONLAYER)
			{
				createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
				createInfo.ppEnabledLayerNames = validationLayers.data();
				createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			}
			else
				createInfo.enabledLayerCount = 0;

			VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
			if (result != VK_SUCCESS)
				throw std::runtime_error("Failed to create instance!");
			else if (result == VK_SUCCESS)
				std::cout << "Successfully created instance" << std::endl;


			uint32_t	instanceExtensionsCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionsCount, nullptr);
			std::vector<VkExtensionProperties>	instanceExtensions(instanceExtensionsCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionsCount, instanceExtensions.data());

			std::cout << "Available instance extensions: " + instanceExtensionsCount << std::endl;
			for (std::vector<VkExtensionProperties>::iterator it = instanceExtensions.begin(); it != instanceExtensions.end(); it++)
				std::cout << '\t' << C_BLUE << (*it).extensionName << C_END << std::endl;
			std::cout << C_WHITE << "GLFW extensions: " << C_END << std::endl;
			for (std::vector<const char *>::const_iterator cit = extensions.begin(); cit != extensions.end(); cit++)
				std::cout << "\t" << C_GREEN << (*cit) << C_END << std::endl;
		}

		//void setupDebugMessenger() {
		//	if (!VALIDATIONLAYER) return;
		//}
		void initVulkan() {
			createInstance();
			//setupDebugMessenger();
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