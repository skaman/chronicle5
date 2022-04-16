// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "storage.h"

#include "filesystem/filesystem_storage.h"

namespace chr::storage {

Storage::Storage(BackendType type) {
  if (type == BackendType::kFileSystem) {
    storage_.emplace<internal::FilesystemStorage>();
  } else {
    debug::Assert(false, "Invalid storage backend type");
  }
}

}  // namespace chr::storage
