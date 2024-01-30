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

class	scopApp {
	public:
		void	run();
	private:
        GLFWwindow  *window;
		VkInstance	instance;
		void	createInstance();
        void    initWindow();
		void	initVulkan();
		void	mainLoop();
		void	cleanup ();
		bool	checkValidationLayerSupport();
		std::vector<const char *>	getRequieredExtensions();
		static	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void *pUserData);
};