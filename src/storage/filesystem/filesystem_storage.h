// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_STORAGE_FILESYSTEM_FILESYSTEM_STORAGE_H_
#define CHR_STORAGE_FILESYSTEM_FILESYSTEM_STORAGE_H_

#include <filesystem>

#include "pch.h"
#include "storage.h"

namespace chr::storage::internal {

struct FilesystemStorage : StorageI {
  explicit FilesystemStorage() = default;

  FilesystemStorage(const FilesystemStorage&) = delete;
  FilesystemStorage(FilesystemStorage&& other) noexcept
      : base_path_{std::move(other.base_path_)} {}

  FilesystemStorage& operator=(const FilesystemStorage&) = delete;
  FilesystemStorage& operator=(FilesystemStorage&& other) noexcept = delete;

  auto SetBasePath(std::string_view path) -> void { base_path_ = path; }

  auto GetEntries(std::string_view path) const -> std::vector<Entry>;
  auto GetFile(std::string_view path) const -> File;

 private:
  std::filesystem::path base_path_{};
};

}  // namespace chr::storage::internal

#endif  // CHR_STORAGE_FILESYSTEM_FILESYSTEM_STORAGE_H_