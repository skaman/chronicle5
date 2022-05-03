// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "enums.h"

namespace chr::renderer {

auto internal::GetErrorDescriptionsMap()
    -> std::unordered_map<chr::renderer::Error, std::string_view> {
  return {
      {chr::renderer::Error::kOutOfHostMemory,
       "A host memory allocation has failed."},
      {chr::renderer::Error::kOutOfDeviceMemory,
       "A device memory allocation has failed."},
      {chr::renderer::Error::kInitializationFailed,
       "Initialization of an object could not be completed for "
       "implementation-specific reasons."},
      {chr::renderer::Error::kDeviceLost,
       "The logical or physical device has been lost."},
      {chr::renderer::Error::kMemoryMapFailed,
       "Mapping of a memory object has failed."},
      {chr::renderer::Error::kLayerNotPresent,
       "A requested layer is not present or could not be loaded."},
      {chr::renderer::Error::kExtensionNotPresent,
       "A requested extension is not supported."},
      {chr::renderer::Error::kFeatureNotPresent,
       "A requested feature is not supported."},
      {chr::renderer::Error::kIncompatibleDriver,
       "The requested version of Vulkan is not supported by the driver or is "
       "otherwise incompatible for implementation-specific reasons."},
      {chr::renderer::Error::kTooManyObjects,
       "Too many objects of the type have already been created."},
      {chr::renderer::Error::kFormatNotSupported,
       "A requested format is not supported on this device."},
      {chr::renderer::Error::kFragmentedPool,
       "A pool allocation has failed due to fragmentation of the pool's "
       "memory. This must only be returned if no attempt to allocate host or "
       "device memory was made to accommodate the new allocation."},
      {chr::renderer::Error::kOutOfPoolMemory,
       "A pool memory allocation has failed. This must only be returned if no "
       "attempt to allocate host or device memory was made to accommodate the "
       "new allocation."},
      {chr::renderer::Error::kInvalidExternalHandle,
       "An external handle is not a valid handle of the specified type."},
      {chr::renderer::Error::kFragmentation,
       "A descriptor pool creation has failed due to fragmentation."},
      {chr::renderer::Error::kInvalidOpaqueCaptureAddress,
       "A buffer creation or memory allocation failed because the requested "
       "address is not available."},
      {chr::renderer::Error::kSurfaceLostKhr,
       " A surface is no longer available."},
      {chr::renderer::Error::kNativeWindowInUse,
       "The requested window is already in use by another API in a manner "
       "which prevents it from being used again."},
      {chr::renderer::Error::kOutOfDate,
       "A surface has changed in such a way that it is no longer compatible "
       "with the swapchain, and further presentation requests using the "
       "swapchain will fail."},
      {chr::renderer::Error::kIncompatibleDisplayKhr,
       "The display used by a swapchain does not use the same presentable "
       "image layout, or is incompatible in a way that prevents sharing an "
       "image."},
      {chr::renderer::Error::kValidationFailedExt,
       "Cannot validate given data structure."},
      {chr::renderer::Error::kInvalidShader,
       "One or more shaders failed to compile or link."},
      {chr::renderer::Error::kInvalidDrmFormat, "Invalid DRM format."},
      {chr::renderer::Error::kNotPermitted, "Operation not permitted."},
      {chr::renderer::Error::kFullScreenExclusiveModeLost,
       "An operation on a swapchain created in exclusive full screen mode "
       "failed as it did not have exlusive full-screen access."},
      {chr::renderer::Error::kUnknown, "kUnknown"}};
}

auto GetErrorDescription(Error error) -> std::string_view {
  if (auto map = internal::GetErrorDescriptionsMap(); map.contains(error)) {
    return map.at(error);
  }

  return {};
}

}  // namespace chr::renderer
