#ifndef HELLOTRIANGLEAPPLICATION_HPP
#define HELLOTRIANGLEAPPLICATION_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define W_WIDTH 800
#define W_HEIGHT 600

class VulkanHelper {
	public: void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}
	private:
		GLFWwindow* window;

		void initWindow() {
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
		}
	
		void initVulkan() {

		}

		void mainLoop() {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
			}
		}

		void cleanup() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}
};

#endif