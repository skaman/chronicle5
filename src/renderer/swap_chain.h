// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SWAP_CHAIN_H_
#define CHR_RENDERER_SWAP_CHAIN_H_

#include "common.h"
#include "fence.h"
#include "image_view.h"
#include "semaphore.h"

namespace chr::renderer {

//! @brief Informations used to create a new swapchain.
struct SwapChainCreateInfo {
  //! @brief Dimensions of the swapchain image (normally is the frame buffer
  //!        size).
  glm::u32vec2 image_size{};
};

//! @brief Swapchain provides the ability to present rendering results to a
//!        surface.
struct SwapChainI {
  virtual ~SwapChainI() = default;

  //! @brief Get the image extent.
  //! @return Image extent.
  virtual auto GetExtent() const -> glm::u32vec2 = 0;

  //! @brief The the image format.
  //! @return Image format.
  virtual auto GetFormat() const -> Format = 0;

  //! @brief Get the number of image view available in the spwapchain.
  //! @return Image view count.
  virtual auto GetImageViewCount() const -> uint32_t = 0;

  //! @brief Get an image view.
  //! @param index Image view index.
  //! @return Image view.
  virtual auto GetImageView(uint32_t index) const -> ImageView = 0;

  //! @brief Acquire an available presentable image to use.
  //! @param semaphore Semaphore to signal or nullptr.
  //! @param fence Fence to signal or nullptr.
  //! @return Index of acquired image.
  virtual auto AcquireNextImage(Semaphore semaphore, Fence fence) -> uint32_t = 0;
};

using SwapChain = std::shared_ptr<SwapChainI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SWAP_CHAIN_H_