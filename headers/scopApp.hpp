#pragma once

#include "header.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char *>	validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
	constexpr bool	enableValidationLayers = false;
#else
	constexpr bool	enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class	scopApp {
	public:
		void	run();
	private:
        GLFWwindow  *window;
		VkInstance	instance;
		VkDebugUtilsMessengerEXT	callback;
		VkPhysicalDevice	physicalDevice;
		VkDevice	device;
		VkQueue	graphicsQueue;
		void	createInstance();
        void    initWindow();
		void	initVulkan();
		void	mainLoop();
		void	cleanup ();
		bool	checkValidationLayerSupport();
		std::vector<const char *>	getRequieredExtensions();
		static	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void *pUserData);
		void setupDebugMessenger();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createLogicalDevice();
};
