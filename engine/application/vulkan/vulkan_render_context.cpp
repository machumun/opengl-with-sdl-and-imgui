#include "vulkan_render_context.hpp"
#include "vulkan_image_view.hpp"

using hid::VulkanRenderContext;

namespace
{
  hid::VulkanImage createMultiSampleImage(
      const hid::VulkanCommandPool &commandPool,
      const hid::VulkanPhysicalDevice &physicalDevice,
      const hid::VulkanDevice &device,
      const hid::VulkanSwapchain &swapchain)
  {
    const vk::Extent2D &extent{swapchain.getExtent()};

    return hid::VulkanImage{
        commandPool,
        physicalDevice,
        device,
        extent.width,
        extent.height,
        1,
        physicalDevice.getMultiSamplingLevel(),
        swapchain.getColorFormat(),
        vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eColorAttachmentOptimal};
  }

  hid::VulkanImageView createImageView(const hid::VulkanDevice &device,
                                       const hid::VulkanImage &image,
                                       const vk::ImageAspectFlags &aspectFlags)
  {
    return hid::VulkanImageView(device.getDevice(),
                                image.getImage(),
                                image.getFormat(),
                                aspectFlags,
                                image.getMipLevels());
  }

  hid::VulkanImage createDepthImage(const hid::VulkanCommandPool &commandPool,
                                    const hid::VulkanPhysicalDevice &physicalDevice,
                                    const hid::VulkanDevice &device,
                                    const hid::VulkanSwapchain &swapchain)
  {
    const vk::Extent2D &extent{swapchain.getExtent()};

    return hid::VulkanImage(
        commandPool,
        physicalDevice,
        device,
        extent.width,
        extent.height,
        1,
        physicalDevice.getMultiSamplingLevel(),
        physicalDevice.getDepthFormat(),
        vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eDepthStencilAttachment,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eDepthStencilAttachmentOptimal);
  }

  std::vector<vk::UniqueFramebuffer> createFramebuffers(const hid::VulkanDevice &device,
                                                        const hid::VulkanSwapchain &swapchain,
                                                        const hid::VulkanRenderPass &renderPass,
                                                        const hid::VulkanImageView &multiSampleImageView,
                                                        const hid::VulkanImageView &depthImageView)
  {
    std::vector<vk::UniqueFramebuffer> framebuffers;

    const vk::Extent2D &extent{swapchain.getExtent()};

    for (const auto &swapchainImageView : swapchain.getImageViews())
    {
      std::array<vk::ImageView, 3> attachments{
          multiSampleImageView.getImageView(),
          depthImageView.getImageView(),
          swapchainImageView->getImageView()};

      vk::FramebufferCreateInfo info{
          vk::FramebufferCreateFlags(),              // Flags
          renderPass.getRenderPass(),                // Render pass
          static_cast<uint32_t>(attachments.size()), // Attachment count
          attachments.data(),                        // Attachments
          extent.width,                              // Width
          extent.height,                             // Height
          1};                                        // Layers

      framebuffers.push_back(device.getDevice().createFramebufferUnique(info));
    }

    return framebuffers;
  }

  vk::Rect2D createScissor(const hid::VulkanSwapchain &swapchain)
  {
    vk::Offset2D offset{0, 0};

    return vk::Rect2D{
        offset,
        swapchain.getExtent()};
  }

  vk::Viewport createViewport(const hid::VulkanSwapchain &swapchain)
  {
    const vk::Extent2D extent{swapchain.getExtent()};
    const float viewportWidth{static_cast<float>(extent.width)};
    const float viewportHeight{static_cast<float>(extent.height)};

    return vk::Viewport{
        0.0f,           // X
        0.0f,           // Y
        viewportWidth,  // Width
        viewportHeight, // Height
        0.0f,           // Min depth
        1.0f};          // Max depth
  }

  std::array<vk::ClearValue, 2> createClearValues()
  {
    vk::ClearValue color;
    color.color = vk::ClearColorValue(std::array<float, 4>{
        164.0f / 256.0f, // Red
        30.0f / 256.0f,  // Green
        34.0f / 256.0f,  // Blue
        1.0f});          // Alpha

    vk::ClearValue depth;
    depth.depthStencil = vk::ClearDepthStencilValue{1.0f, 0};

    return std::array<vk::ClearValue, 2>{color, depth};
  }

  uint32_t acquireNextImageIndex(const vk::Device &device,
                                 const vk::SwapchainKHR &swapchain,
                                 const vk::Fence &fence,
                                 const vk::Semaphore &semaphore)
  {
    static constexpr uint64_t timeOut{std::numeric_limits<uint64_t>::max()};

    device.waitForFences(
        1,        // Number of fences to wait for
        &fence,   // Fences to wait for
        VK_TRUE,  // Wait for all fences
        timeOut); // Timeout while waiting

    // The fence should now be reset, ready for the next use case.
    device.resetFences(1, &fence);

    vk::ResultValue nextImageIndex{device.acquireNextImageKHR(
        swapchain, // Swapchain to acquire from
        timeOut,   // Timeout while waiting
        semaphore, // Which semaphore to signal
        nullptr)}; // Which fence to signal

    return nextImageIndex.value;
  }
}

VulkanRenderContext::VulkanRenderContext(
    const hid::SDLWindow &window,
    const hid::VulkanPhysicalDevice &physicalDevice,
    const hid::VulkanDevice &device,
    const hid::VulkanSurface &surface,
    const hid::VulkanCommandPool &commandPool,
    const vk::SwapchainKHR &oldSwapchain)
    : swapchain{hid::VulkanSwapchain(window, physicalDevice, device, surface, oldSwapchain)},
      renderPass{hid::VulkanRenderPass(physicalDevice, device, swapchain)},
      multiSampleImage{::createMultiSampleImage(commandPool, physicalDevice, device, swapchain)},
      multiSampleImageView{::createImageView(device,
                                             multiSampleImage,
                                             vk::ImageAspectFlagBits::eColor)},
      depthImage{::createDepthImage(commandPool, physicalDevice, device, swapchain)},
      depthImageView{::createImageView(device, depthImage, vk::ImageAspectFlagBits::eDepth)},
      framebuffers{::createFramebuffers(device,
                                        swapchain,
                                        renderPass,
                                        multiSampleImageView,
                                        depthImageView)},
      graphicsSemaphores{device.createSemaphores(maxRenderFrames)},
      presentationSemaphores{device.createSemaphores(maxRenderFrames)},
      graphicsFences{device.createFences(maxRenderFrames)},
      scissor{::createScissor(swapchain)},
      viewport{::createViewport(swapchain)},
      clearValues{::createClearValues()},
      commandBuffers{commandPool.createCommandBuffers(device, swapchain.getImageCount())}
{
}

bool VulkanRenderContext::renderBegin(const hid::VulkanDevice &device)
{
  const vk::Fence &graphicsFence{graphicsFences[currentFrameIndex].get()};
  const vk::Semaphore &graphicsSemaphore{graphicsSemaphores[currentFrameIndex].get()};

  try
  {
    currentSwapchainImageIndex = ::acquireNextImageIndex(device.getDevice(),
                                                         swapchain.getSwapchain(),
                                                         graphicsFence,
                                                         graphicsSemaphore);
  }
  catch (vk::OutOfDateKHRError outOfDateError)
  {
    return false;
  }

  const vk::CommandBuffer &commandBuffer{commandBuffers[currentSwapchainImageIndex].get()};

  commandBuffer.reset(vk::CommandBufferResetFlagBits::eReleaseResources);

  vk::CommandBufferBeginInfo commandBufferBeginInfo{vk::CommandBufferUsageFlagBits::eOneTimeSubmit, nullptr};
  commandBuffer.begin(&commandBufferBeginInfo);

  commandBuffer.setScissor(
      0,         // Which scissor to start at
      1,         // How many scissors to apply
      &scissor); // Scissor data

  commandBuffer.setViewport(
      0,          // Which viewport to start at
      1,          // How many viewports to apply
      &viewport); // Viewport data
                  // Define the render pass attributes to apply.
  vk::RenderPassBeginInfo renderPassBeginInfo{
      renderPass.getRenderPass(),                     // Render pass to use
      framebuffers[currentSwapchainImageIndex].get(), // Current frame buffer
      scissor,                                        // Render area
      2,                                              // Clear value count
      clearValues.data()};                            // Clear values

  commandBuffer.beginRenderPass(&renderPassBeginInfo, vk::SubpassContents::eInline);
  return true;
}

bool VulkanRenderContext::renderEnd(const hid::VulkanDevice &device)
{
  const vk::CommandBuffer &commandBuffer{commandBuffers[currentSwapchainImageIndex].get()};

  commandBuffer.endRenderPass();
  commandBuffer.end();

  const vk::Fence &graphicsFence{graphicsFences[currentFrameIndex].get()};
  const vk::Semaphore &graphicsSemaphore{graphicsSemaphores[currentFrameIndex].get()};
  const vk::Semaphore &presentationSemaphore{presentationSemaphores[currentFrameIndex].get()};
  const vk::PipelineStageFlags pipelineStageFlags{vk::PipelineStageFlagBits::eColorAttachmentOutput};

  vk::SubmitInfo submitInfo{
      1,                       // Wait semaphore count
      &graphicsSemaphore,      // Wait semaphores
      &pipelineStageFlags,     // Pipeline stage flags
      1,                       // Command buffer count
      &commandBuffer,          // Command buffer
      1,                       // Signal semaphore count
      &presentationSemaphore}; // Signal semaphores

  device.getGraphicsQueue().submit(1, &submitInfo, graphicsFence);

  vk::PresentInfoKHR presentationInfo{
      1,                           // Semaphore count
      &presentationSemaphore,      // Wait semaphore
      1,                           // Swapchain count
      &swapchain.getSwapchain(),   // Swapchain
      &currentSwapchainImageIndex, // Image indices
      nullptr};                    // Results

  try
  {

    if (device.getPresentationQueue().presentKHR(presentationInfo) == vk::Result::eSuboptimalKHR)
    {
      return false;
    }
  }
  catch (vk::OutOfDateKHRError outOfDateError)
  {
    return false;
  }

  device.getPresentationQueue().waitIdle();

  currentFrameIndex = (currentFrameIndex + 1) % maxRenderFrames;

  return true;
}

std::unique_ptr<hid::VulkanRenderContext> VulkanRenderContext::recreate(const hid::SDLWindow &window,
                                                                        const hid::VulkanPhysicalDevice &physicalDevice,
                                                                        const hid::VulkanDevice &device,
                                                                        const hid::VulkanSurface &surface,
                                                                        const hid::VulkanCommandPool &commandPool)
{
  return std::make_unique<hid::VulkanRenderContext>(window,
                                                    physicalDevice,
                                                    device,
                                                    surface,
                                                    commandPool,
                                                    swapchain.getSwapchain());
}

const vk::Viewport &VulkanRenderContext::getViewport() const
{
  return viewport;
}

const vk::Rect2D &VulkanRenderContext::getScissor() const
{
  return scissor;
}

const vk::RenderPass &VulkanRenderContext::getRenderPass() const
{
  return renderPass.getRenderPass();
}