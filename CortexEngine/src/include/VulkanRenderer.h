#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#pragma endregion 


const int WIDTH = 800; 
const int HEIGHT = 600;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG 
const bool enableValidationLayers = false; 
#else 
const bool enableValidationLayers = true; 
#endif

namespace CE
{
	namespace Rendering
	{
		struct QueueFamilyIndices {
			int GraphicsFamily = -1;
			int PresentFamily = -1;

			bool IsComplete() {
				return GraphicsFamily >= 0 && PresentFamily >= 0;
			}
		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR Capabilites;
			std::vector<VkSurfaceFormatKHR> Formats;
			std::vector<VkPresentModeKHR> PresentModes;
		};
		class VulkanRenderer
		{
		private: 
			GLFWwindow * m_pWindow;
			VkInstance m_vkInstance;
			VkDebugReportCallbackEXT m_callback;
			VkPhysicalDevice m_physicalDevice;
			VkDevice m_logicalDevice;
			VkQueue m_graphicsQueue;
			VkSurfaceKHR m_surface;
			VkQueue m_presentQueue;
			VkSwapchainKHR m_swapChain;
			std::vector<VkImage> m_swapChainImages;
		public: 
			VulkanRenderer(); 
			~VulkanRenderer(); 
			void Init(); 
			int Run(); 
			void Release();
		private: 
			void InitWindow();
			void Cleanup(); 
			void CreateInstance();
			void InitVulkan();
			void SetupDebugCallback();
			void PickPhysicalDevice(); 
			void CreateLogicalDevice();
			void CreateSurface();
			void CreateSwapChain();

			//Helper functions
			bool CheckValidationLayerSupport();
			std::vector<const char*> GetRequiredExtensions(); 
			bool IsDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
			bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
			VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilites);

			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallBack(
				VkDebugReportFlagsEXT flags,
				VkDebugReportObjectTypeEXT objType,
				uint64_t obj,
				size_t location,
				int32_t code,
				const char* layerPrefix,
				const char* msg,
				void* userData);
			//Proxy functions 
			VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
			static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
		};
	}
}