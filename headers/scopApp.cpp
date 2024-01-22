#include "scopApp.hpp"

void    scopApp::run () {
	this->initWindow();
	this->initVulkan();
	this->mainLoop();
	this->cleanup();
}

void	scopApp::createInstance() {
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("Validation header on, but not available");
	}

	VkApplicationInfo   appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Scop";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t    glfwExtensionCount = 0;
	const char  **glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
	} else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &this->instance) != VK_SUCCESS) {
		throw std::runtime_error("Instance creation failed");
	}

	uint32_t    extensionCount = 0;
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "Extensions available :" << std::endl;

	for (const auto& extension : extensions) {
		std::cout << '\t' << extension.extensionName << std::endl;
	}
}

void    scopApp::initWindow () {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "Scop", nullptr, nullptr);
}

void    scopApp::initVulkan () {
	this->createInstance();
}

void    scopApp::mainLoop () {
	while (!glfwWindowShouldClose(this->window)) {
		glfwPollEvents();
	}
}

void    scopApp::cleanup () {
	vkDestroyInstance(this->instance, nullptr);

	glfwDestroyWindow(this->window);

	glfwTerminate();
}

bool	scopApp::checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char *layerName : validationLayers) {
		bool layerFound = false;

		for (const auto &layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}