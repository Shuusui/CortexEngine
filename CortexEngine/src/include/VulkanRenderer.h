#pragma once
#pragma region Internal Includes
#include "MessageEvent.h"
#pragma endregion 
#pragma region External Includes
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>
#include <chrono>
#include <unordered_map>
#pragma endregion 


const int WIDTH = 800; 
const int HEIGHT = 600;


const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG 
const bool enableValidationLayers = false; 
#else 
const bool enableValidationLayers = true; 
#endif

struct Vertex {
	glm::vec3 Pos;
	glm::vec3 Color;
	glm::vec2 TexCoord;

	static VkVertexInputBindingDescription GetBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, Pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, Color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, TexCoord);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other) const {
		return Pos == other.Pos && Color == other.Color && TexCoord == other.TexCoord;
	}
};

namespace std {
	template<> struct hash<Vertex> {
		size_t operator() (Vertex const & vertex) const {
			return ((hash<glm::vec3>()(vertex.Pos) ^
				(hash<glm::vec3>()(vertex.Color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.TexCoord) << 1);
		}
	};
}
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

		struct UniformBufferObject {
			glm::mat4 Model; 
			glm::mat4 View; 
			glm::mat4 Proj;
		};

		class VulkanRenderer
		{
		private: 
			GLFWwindow* m_pWindow;
			VkInstance m_vkInstance;
			VkDebugReportCallbackEXT m_callback;
			VkPhysicalDevice m_physicalDevice;
			VkDevice m_logicalDevice;
			VkQueue m_graphicsQueue;
			VkSurfaceKHR m_surface;
			VkQueue m_presentQueue;
			VkSwapchainKHR m_swapChain;
			std::vector<VkImage> m_swapChainImages;
			std::vector<VkImageView> m_swapChainImageViews;
			VkFormat m_swapChainImageFormat; 
			VkExtent2D m_swapChainExtent;
			VkPipelineLayout m_pipelineLayout;
			VkRenderPass m_renderPass;
			VkPipeline m_graphicsPipeline;
			std::vector<VkFramebuffer> m_swapChainFramebuffers;
			VkCommandPool m_commandPool;
			std::vector<VkCommandBuffer> m_commandBuffers;
			std::vector<VkSemaphore> m_imageAvailableSemaphores; 
			std::vector<VkSemaphore> m_renderFinishedSemaphores;
			std::vector<VkFence> m_inFlightFences;
			size_t m_currentFrame;
			VkDescriptorSetLayout m_descriptorSetLayout;
			VkDescriptorPool m_descriptorPool;
			std::vector<VkDescriptorSet> m_descritorSets;
			VkImage m_depthImage;
			VkDeviceMemory m_depthImageMemory;
			VkImageView m_depthImageView;
			std::vector<VkBuffer> m_vertexBuffers;  //TODO: Not deleted yet
			VkBuffer m_indexBuffer; // TODO: Not deleted yet
			std::vector<uint32_t> m_indices;
			std::vector<VkWriteDescriptorSet> m_descriptorWrites;
			std::vector<VkDescriptorSetLayoutBinding> m_bindings;
		public: 
			VulkanRenderer(); 
			~VulkanRenderer(); 
			void Init(); 
			int Run(); 
			void Release();
			VkDevice GetLogicalDevice() const { return m_logicalDevice; }

			void UpdateDescriptorSets(VkWriteDescriptorSet writeDescriptorSet);
			//Helper functions
			void MapData(void* dstData, void* srcData, VkDeviceMemory& dstMapMemory, VkDeviceSize memorySize);
			void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
			void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
			void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
				VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
			void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
			void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height); 
			void GenerateMipmaps(VkImage image, int32_t texWidth, int32_t teexHeight, uint32_t mipLevels);
			VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
			size_t AddVertexBuffer(VkBuffer vertexBuffer);
			void AddDescriptorLayoutBinding(VkDescriptorSetLayoutBinding binding);
			void RemoveVertexBuffer(size_t index);
			void SetIndices(std::vector<uint32_t> indices);
			void SetIndexBuffer(VkBuffer indexBuffer);
			void InitDevices();
			VkDescriptorPool GetDescriptorPool() const; 
			VkDescriptorSetLayout GetDescriptorLayout() const;
			void AddDescriptorSet(VkDescriptorSet descriptorSet);
			VkExtent2D GetExtent() const;
		private: 
			//Init functions
			void InitWindow();
			void Cleanup(); 
			void CleanupSwapChain();
			void CreateInstance();
			void InitVulkan();
			void SetupDebugCallback();
			void PickPhysicalDevice(); 
			void CreateLogicalDevice();
			void CreateSurface();
			void CreateSwapChain();
			void CreateImageViews();
			void CreateGraphicsPipeline();
			void CreateRenderPass();
			void CreateFramebuffers();
			void CreateCommandPool();
			void CreateSyncObjects();
			void RecreateSwapChain();
			void CreateDescriptorLayout();
			void CreateDescriptorPool();
			void CreateDepthResources();
			void CreateCommandBuffers();

			//Runtime functions
			void DrawFrame();

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
			static std::vector<char> ReadFile(const std::string& fileName);
			VkShaderModule CreateShaderModule(const std::vector<char>& code);
			uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
			VkCommandBuffer BeginSingleTimeCommand(); 
			void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
			VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features); 
			VkFormat FindDepthFormat();
			bool HasStencilComponent(VkFormat format);


			//Statics
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