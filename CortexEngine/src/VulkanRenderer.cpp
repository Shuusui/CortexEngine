#include "include\VulkanRenderer.h"

CE::Rendering::VulkanRenderer::VulkanRenderer()
	:m_physicalDevice(VK_NULL_HANDLE)
{
}

CE::Rendering::VulkanRenderer::~VulkanRenderer()
{
}

void CE::Rendering::VulkanRenderer::Init()
{
	InitWindow();
	InitVulkan();
}

int CE::Rendering::VulkanRenderer::Run()
{
	glfwPollEvents();
	return glfwWindowShouldClose(m_pWindow);
}

void CE::Rendering::VulkanRenderer::Release()
{
	Cleanup();
}

void CE::Rendering::VulkanRenderer::InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	
	m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, "CortexEngine", nullptr, nullptr);
}

void CE::Rendering::VulkanRenderer::Cleanup()
{
	for (auto imageView : m_swapChainImageViews) {
		vkDestroyImageView(m_logicalDevice, imageView, nullptr);
	}

	vkDestroySwapchainKHR(m_logicalDevice, m_swapChain, nullptr);

	vkDestroyDevice(m_logicalDevice, nullptr);

	if (enableValidationLayers) {
		DestroyDebugReportCallbackEXT(m_vkInstance, m_callback, nullptr);
	}
	
	vkDestroySurfaceKHR(m_vkInstance, m_surface, nullptr);

	vkDestroyInstance(m_vkInstance, nullptr);

	glfwDestroyWindow(m_pWindow); 

	glfwTerminate();
}

void CE::Rendering::VulkanRenderer::CreateInstance()
{
	if (enableValidationLayers && !CheckValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but no available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; 
	appInfo.pApplicationName = "Cortex Engine"; 
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine"; 
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size()); 
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create Instance");
	}
}

void CE::Rendering::VulkanRenderer::InitVulkan()
{
	CreateInstance();
	SetupDebugCallback();
	CreateSurface();
	PickPhysicalDevice();
	CreateLogicalDevice();
	CreateSwapChain(); 
	CreateImageViews(); 
	CreateGraphicsPipeline();
}

void CE::Rendering::VulkanRenderer::SetupDebugCallback()
{
	if (!enableValidationLayers) return;

	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT; 
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = DebugCallBack;

	if (CreateDebugReportCallbackEXT(m_vkInstance, &createInfo, nullptr, &m_callback) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug callback!");
	}
}

void CE::Rendering::VulkanRenderer::PickPhysicalDevice()
{
	uint32_t deviceCount = 0; 
	vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPU's with vulkan support!");
	}
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, devices.data());
	for (const auto& device : devices) {
		if (IsDeviceSuitable(device)) {
			m_physicalDevice = device; 
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

void CE::Rendering::VulkanRenderer::CreateLogicalDevice()
{
	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice); 

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO; 
	queueCreateInfo.queueFamilyIndex = indices.GraphicsFamily; 
	queueCreateInfo.queueCount = 1; 

	float queuePriority = 1.0f; 
	queueCreateInfo.pQueuePriorities = &queuePriority; 

	VkPhysicalDeviceFeatures physicalDeviceFeatures;

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueFamilies = { indices.GraphicsFamily, indices.PresentFamily };

	for (int queueFamily : uniqueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}
	
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1; 

	createInfo.pEnabledFeatures = &physicalDeviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()); 
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(m_logicalDevice, indices.GraphicsFamily, 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_logicalDevice, indices.PresentFamily, 0, &m_presentQueue);
}

void CE::Rendering::VulkanRenderer::CreateSurface()
{
	if (glfwCreateWindowSurface(m_vkInstance, m_pWindow, nullptr, &m_surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void CE::Rendering::VulkanRenderer::CreateSwapChain()
{
	SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.Formats);
	VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.PresentModes);
	VkExtent2D extent = ChooseSwapExtent(swapChainSupport.Capabilites);

	uint32_t imageCount = swapChainSupport.Capabilites.minImageCount + 1;
	if (swapChainSupport.Capabilites.maxImageCount > 0 && imageCount > swapChainSupport.Capabilites.maxImageCount) {
		imageCount = swapChainSupport.Capabilites.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR; 
	createInfo.surface = m_surface;
	createInfo.minImageCount = imageCount; 
	createInfo.imageFormat = surfaceFormat.format; 
	createInfo.imageColorSpace = surfaceFormat.colorSpace; 
	createInfo.imageExtent = extent; 
	createInfo.imageArrayLayers = 1; 
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; 

	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice); 
	uint32_t queueFamilyIndices[] = { (uint32_t)indices.GraphicsFamily, (uint32_t)indices.PresentFamily };

	if (indices.GraphicsFamily != indices.PresentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT; 
		createInfo.queueFamilyIndexCount = 2; 
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; 
	}
	createInfo.preTransform = swapChainSupport.Capabilites.currentTransform; 
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; 
	createInfo.presentMode = presentMode; 
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(m_logicalDevice, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(m_logicalDevice, m_swapChain, &imageCount, nullptr);
	m_swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(m_logicalDevice, m_swapChain, &imageCount, m_swapChainImages.data());
	m_swapChainImageFormat = surfaceFormat.format;
	m_swapChainExtent = extent;
}

void CE::Rendering::VulkanRenderer::CreateImageViews()
{
	m_swapChainImageViews.resize(m_swapChainImages.size());
	for (size_t i = 0; i < m_swapChainImages.size(); i++) {
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = m_swapChainImages[i];

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_swapChainImageFormat;
		
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY; 
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY; 
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; 
		createInfo.subresourceRange.baseMipLevel = 0; 
		createInfo.subresourceRange.levelCount = 1; 
		createInfo.subresourceRange.baseArrayLayer = 0; 
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(m_logicalDevice, &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image views!");
		}
	}
}

void CE::Rendering::VulkanRenderer::CreateGraphicsPipeline()
{
	auto vertexShaderCode = ReadFile("../assets//shader//vert.spv");
	auto fragShaderCode = ReadFile("../assets//shader//vert.spv");

	VkShaderModule vertShaderModule = CreateShaderModule(vertexShaderCode);
	VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO; 
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {}; 
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT; 
	fragShaderStageInfo.module = fragShaderModule; 
	fragShaderStageInfo.pName = "main"; 

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {}; 
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO; 
	vertexInputInfo.vertexBindingDescriptionCount = 0; 
	vertexInputInfo.vertexAttributeDescriptionCount = 0;

	VkViewport viewport = {}; 
	viewport.x = 0.0f; 
	viewport.y = 0.0f; 
	viewport.width = (float)m_swapChainExtent.width;
	viewport.height = (float)m_swapChainExtent.height; 
	viewport.minDepth = 0.0f; 
	viewport.maxDepth = 1.0f; 

	VkRect2D scissor = {};
	scissor.offset = { 0,0 };
	scissor.extent = m_swapChainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1; 
	viewportState.pViewports = &viewport; 
	viewportState.scissorCount = 1; 
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE; 
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO; 
	multisampling.sampleShadingEnable = VK_FALSE; 
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;


	vkDestroyShaderModule(m_logicalDevice, vertShaderModule, nullptr); 
	vkDestroyShaderModule(m_logicalDevice, fragShaderModule, nullptr);
}

bool CE::Rendering::VulkanRenderer::CheckValidationLayerSupport()
{
	uint32_t layerCount = 0; 
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false; 

		for (const auto& layerProperties : availableLayers) {
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

std::vector<const char*> CE::Rendering::VulkanRenderer::GetRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0; 
	const char** glfwExtensions; 
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); 

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}
	return extensions;
}

bool CE::Rendering::VulkanRenderer::IsDeviceSuitable(VkPhysicalDevice device)
{
	QueueFamilyIndices indices = FindQueueFamilies(device); 

	bool extensionSupported = CheckDeviceExtensionSupport(device);

	bool swapChainAdequate = false; 

	if (extensionSupported) {
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.Formats.empty() && !swapChainSupport.PresentModes.empty();
	}

	return indices.IsComplete() && extensionSupported && swapChainAdequate;
}

CE::Rendering::QueueFamilyIndices CE::Rendering::VulkanRenderer::FindQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices; 

	uint32_t queueFamilyCount = 0; 
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount); 
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0; 
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.GraphicsFamily = i;
		}
		VkBool32 presentSupport = false; 
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport) {
			indices.PresentFamily = i;
		}
		if (indices.IsComplete()) {
			break;
		}
		i++;
	}

	return indices;
}

bool CE::Rendering::VulkanRenderer::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount; 
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}
	return requiredExtensions.empty();
}

CE::Rendering::SwapChainSupportDetails CE::Rendering::VulkanRenderer::QuerySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details; 

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.Capabilites);

	uint32_t formatCount; 
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr); 

	if (formatCount != 0) {
		details.Formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.Formats.data());
	}

	uint32_t presentModeCount; 
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.PresentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.PresentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR CE::Rendering::VulkanRenderer::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}
	
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR CE::Rendering::VulkanRenderer::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}

VkExtent2D CE::Rendering::VulkanRenderer::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilites)
{
	if (capabilites.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilites.currentExtent;
	}
	else {
		VkExtent2D actualExtent = { WIDTH, HEIGHT };

		actualExtent.width = std::max(capabilites.minImageExtent.width, std::min(capabilites.maxImageExtent.width, actualExtent.width)); 
		actualExtent.height = std::max(capabilites.minImageExtent.height, std::min(capabilites.maxImageExtent.height, actualExtent.height));
		return actualExtent;
	}
}

std::vector<char> CE::Rendering::VulkanRenderer::ReadFile(const std::string & fileName)
{
	std::ifstream file(fileName, std::ios::ate | std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("failed to open file");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0); 
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}

VkShaderModule CE::Rendering::VulkanRenderer::CreateShaderModule(const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo = {}; 
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO; 
	createInfo.codeSize = code.size(); 
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data()); 

	VkShaderModule shaderModule; 
	if (vkCreateShaderModule(m_logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module");
	}
	return shaderModule;
}

VKAPI_ATTR VkBool32 VKAPI_CALL CE::Rendering::VulkanRenderer::DebugCallBack(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char * layerPrefix, const char * msg, void * userData)
{
	std::cerr << "validation layer: " << msg << std::endl; 
	return VK_FALSE;
}

VkResult CE::Rendering::VulkanRenderer::CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugReportCallbackEXT * pCallback)
{
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"); 
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void CE::Rendering::VulkanRenderer::DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks * pAllocator)
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}
