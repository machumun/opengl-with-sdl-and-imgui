#include "vulkan_pipeline.hpp"

#include "vulkan_application.hpp"

using hid::VulkanApplication;
using hid::VulkanPipeline;

namespace
{
    vk::UniqueDescriptorSetLayout createDescripterSetLayout(const hid::VulkanDevice &device)
    {
        vk::DescriptorSetLayoutBinding textureBinding{
            0,                                         // Binding
            vk::DescriptorType::eCombinedImageSampler, // Descriptor type
            1,                                         // Descriptor count
            vk::ShaderStageFlagBits::eFragment,        // Shader stage flags
            nullptr};                                  // Immutable samplers

        vk::DescriptorSetLayoutCreateInfo info{
            vk::DescriptorSetLayoutCreateFlags(), // Flags
            1,                                    // Binding count
            &textureBinding};                     // Bindings

        return device.getDevice().createDescriptorSetLayoutUnique(info);
    }

    vk::UniquePipelineLayout createPipelineLayout(const hid::VulkanDevice &device,
                                                  const vk::DescriptorSetLayout &descriptorSetLayout)
    {
        vk::PushConstantRange pushConstantRange{
            vk::ShaderStageFlagBits::eAllGraphics, // Flags
            0,                                     // Offset
            sizeof(glm::mat4)};                    // Size

        vk::PipelineLayoutCreateInfo info{
            vk::PipelineLayoutCreateFlags(), // Flags
            1,                               // Layout count
            &descriptorSetLayout,            // Layouts,
            1,                               // Push constant range count,
            &pushConstantRange               // Push constant ranges
        };

        return device.getDevice().createPipelineLayoutUnique(info);
    }

    vk::UniquePipeline createPipeline(const hid::VulkanPhysicalDevice &physicalDevice,
                                      const hid::VulkanDevice &device,
                                      const vk::PipelineLayout &pipelineLayout,
                                      const std::string &shaderName,
                                      const vk::Viewport &viewport,
                                      const vk::Rect2D &scissor,
                                      const vk::RenderPass &renderPass)
    {
        // Create a vertex shader module from asset file.
        vk::UniqueShaderModule vertexShaderModule{
            device.createShaderModule(hid::assets::loadBinaryFile("assets/shaders/spir_v/" + shaderName + ".vert"))};

        // Describe how to use the vertex shader module in the pipeline.
        vk::PipelineShaderStageCreateInfo vertexShaderInfo{
            vk::PipelineShaderStageCreateFlags(), // Flags
            vk::ShaderStageFlagBits::eVertex,     // Shader stage
            vertexShaderModule.get(),             // Shader module
            "main",                               // Name
            nullptr};                             // Specialisation info

        // Define the data format that will be passed into the vertex shader.
        vk::VertexInputBindingDescription vertexBindingDescription{
            0,                           // Binding
            sizeof(hid::Vertex),         // Stride
            vk::VertexInputRate::eVertex // Input rate
        };

        // Define the shape of the vertex position (x, y, z) attribute.
        vk::VertexInputAttributeDescription vertexPositionDescription{
            0,                                // Location
            0,                                // Binding
            vk::Format::eR32G32B32Sfloat,     // Format
            offsetof(hid::Vertex, position)}; // Offset

        // Define the shape of the texture coordinate (u, v) attribute.
        vk::VertexInputAttributeDescription textureCoordinateDescription{
            1,                                // Location
            0,                                // Binding
            vk::Format::eR32G32Sfloat,        // Format
            offsetof(hid::Vertex, texCoord)}; // Offset

        // Collate all the vertex shader attributes that will be used in the pipeline.
        std::array<vk::VertexInputAttributeDescription, 2> vertexAttributeDescriptions{
            vertexPositionDescription,
            textureCoordinateDescription};

        // Bundle up the collated descriptions defining how vertex data will be passed into the shader.
        vk::PipelineVertexInputStateCreateInfo vertexInputState{
            vk::PipelineVertexInputStateCreateFlags(),                 // Flags
            1,                                                         // Vertex binding description count
            &vertexBindingDescription,                                 // Vertex binding description
            static_cast<uint32_t>(vertexAttributeDescriptions.size()), // Vertex attribute descriptions
            vertexAttributeDescriptions.data()};                       // Vertex attribute descriptions

        // Create a fragment shader module from asset file.
        vk::UniqueShaderModule fragmentShaderModule{
            device.createShaderModule(hid::assets::loadBinaryFile("assets/shaders/spir_v/" + shaderName + ".frag"))};

        // Describe how to use the fragment shader module in the pipeline.
        vk::PipelineShaderStageCreateInfo fragmentShaderInfo{
            vk::PipelineShaderStageCreateFlags(), // Flags
            vk::ShaderStageFlagBits::eFragment,   // Shader stage
            fragmentShaderModule.get(),           // Shader module
            "main",                               // Name
            nullptr};                             // Specialisation info

        // Collate both vertex and fragment shaders into the list of pipeline shaders to use.
        std::array<vk::PipelineShaderStageCreateInfo, 2> stages{
            vertexShaderInfo,
            fragmentShaderInfo};

        // Define what variety of data will be sent into the pipeline - for us a triangle list.
        vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState{
            vk::PipelineInputAssemblyStateCreateFlags(), // Flags
            vk::PrimitiveTopology::eTriangleList,        // Topology
            0};                                          // Primitive restart enable

        // Declare the viewport and scissor to apply to the shader output.
        vk::PipelineViewportStateCreateInfo viewportState{
            vk::PipelineViewportStateCreateFlags(), // Flags
            1,                                      // Viewport count
            &viewport,                              // Viewports
            1,                                      // Scissor count
            &scissor};                              // Scissors

        // Define how the pipeline should process output during rendering.
        vk::PipelineRasterizationStateCreateInfo rasterizationState{
            vk::PipelineRasterizationStateCreateFlags(), // Flags
            VK_FALSE,                                    // Depth clamp enable
            VK_FALSE,                                    // Rasterizer discard enable
            vk::PolygonMode::eFill,                      // Polygon mode
            vk::CullModeFlagBits::eBack,                 // Cull mode
            vk::FrontFace::eCounterClockwise,            // Front face
            VK_FALSE,                                    // Depth bias enable
            0.0f,                                        // Depth bias constant factor
            0.0f,                                        // Depth bias clamp
            0.0f,                                        // Depth bias slop factor
            1.0f};                                       // Line width

        // Define how to apply multi sampling to the shader output.
        vk::PipelineMultisampleStateCreateInfo multisampleState{
            vk::PipelineMultisampleStateCreateFlags(), // Flags
            physicalDevice.getMultiSamplingLevel(),    // Rasterization samples
            VK_FALSE,                                  // Sample shading enabled
            0.0f,                                      // Min sample shading
            nullptr,                                   // Sample mask
            VK_FALSE,                                  // Alpha to coverage enable
            VK_FALSE};                                 // Alpha to one enable

        // If our physical device can do multisampling at the shader level, enable it.
        if (physicalDevice.isShaderMultiSamplingSupported())
        {
            multisampleState.sampleShadingEnable = VK_TRUE;
            multisampleState.minSampleShading = 0.2f;
        }

        // Determine the way that depth testing will be performed for the pipeline.
        vk::PipelineDepthStencilStateCreateInfo depthStencilState{
            vk::PipelineDepthStencilStateCreateFlags(), // Flags
            VK_TRUE,                                    // Depth test enable
            VK_TRUE,                                    // Depth write enable
            vk::CompareOp::eLess,                       // Depth compare operation
            VK_FALSE,                                   // Depth bounds test enable
            VK_FALSE,                                   // Stencil test enable
            vk::StencilOpState(),                       // Stencil front operation
            vk::StencilOpState(),                       // Stencil back operation
            0.0f,                                       // Min depth bounds
            0.0f};                                      // Max depth bounds

        // Define how colors should be written during blending.
        vk::ColorComponentFlags colorWriteMask{
            vk::ColorComponentFlagBits::eR |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eA};

        // Define how colors should blend together during rendering.
        vk::PipelineColorBlendAttachmentState colorBlendAttachment{
            VK_TRUE,                            // Blend enable
            vk::BlendFactor::eSrcAlpha,         // Source color blend factor
            vk::BlendFactor::eOneMinusSrcAlpha, // Destination color blend factor
            vk::BlendOp::eAdd,                  // Color blend operation
            vk::BlendFactor::eOne,              // Source alpha blend factor
            vk::BlendFactor::eZero,             // Destination alpha blend factor
            vk::BlendOp::eAdd,                  // Alpha blend operation
            colorWriteMask};                    // Color write mask

        // Take the blending attachment and collate it into a pipeline state definition.
        vk::PipelineColorBlendStateCreateInfo colorBlendState{
            vk::PipelineColorBlendStateCreateFlags(), // Flags
            VK_FALSE,                                 // Logic operation enable
            vk::LogicOp::eClear,                      // Logic operation
            1,                                        // Attachment count
            &colorBlendAttachment,                    // Attachments
            {{0, 0, 0, 0}}};                          // Blend constants

        // Collate all the components into a single graphics pipeline definition.
        vk::GraphicsPipelineCreateInfo pipelineCreateInfo{
            vk::PipelineCreateFlags(),            // Flags
            static_cast<uint32_t>(stages.size()), // Stage count (vertex + fragment)
            stages.data(),                        // Stages
            &vertexInputState,                    // Vertex input state
            &inputAssemblyState,                  // Input assembly state
            nullptr,                              // Tesselation state
            &viewportState,                       // Viewport state
            &rasterizationState,                  // Rasterization state
            &multisampleState,                    // Multi sample state
            &depthStencilState,                   // Depth stencil state
            &colorBlendState,                     // Color blend state
            nullptr,                              // Dynamic state
            pipelineLayout,                       // Pipeline layout
            renderPass,                           // Render pass
            0,                                    // Subpass
            vk::Pipeline(),                       // Base pipeline handle
            0};                                   // Base pipeline index

        return device.getDevice().createGraphicsPipelineUnique(nullptr, pipelineCreateInfo);
    }
}

VulkanPipeline::VulkanPipeline(const hid::VulkanPhysicalDevice &physicalDevice,
                               const hid::VulkanDevice &device,
                               const std::string &shaderName,
                               const vk::Viewport &viewport,
                               const vk::Rect2D &scissor,
                               const vk::RenderPass &renderPass)
    : descriptorSetLayout{::createDescripterSetLayout(device)},
      pipelineLayout{::createPipelineLayout(device, descriptorSetLayout.get())},
      pipeline{::createPipeline(
          physicalDevice,
          device,
          pipelineLayout.get(),
          shaderName,
          viewport,
          scissor,
          renderPass)}
{
}

void VulkanPipeline::render()
{
    VulkanApplication::vulkanAssetManager;
}