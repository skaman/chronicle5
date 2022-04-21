// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_STORAGE_FILESYSTEM_FILESYSTEM_ENTRY_H_
#define CHR_STORAGE_FILESYSTEM_FILESYSTEM_ENTRY_H_

#include <filesystem>
#include <fstream>

#include "entry.h"
#include "filesystem_file.h"
#include "pch.h"

namespace chr::storage::internal {

struct FilesystemEntry : EntryI {
  explicit FilesystemEntry(const std::filesystem::directory_entry& dir_entry)
      : dir_entry_{dir_entry} {};

  FilesystemEntry(const FilesystemEntry&) = delete;
  FilesystemEntry(FilesystemEntry&& other) noexcept
      : dir_entry_{std::move(other.dir_entry_)} {}

  FilesystemEntry& operator=(const FilesystemEntry&) = delete;
  FilesystemEntry& operator=(FilesystemEntry&& other) noexcept = delete;

  auto Name() const -> std::string {
    return dir_entry_.path().filename().string();
  };

  auto HaveExtension() const -> bool {
    return dir_entry_.path().has_extension();
  }

  auto Extension() const -> std::string {
    return dir_entry_.path().extension().string();
  };

  auto IsDirectory() const -> bool { return dir_entry_.is_directory(); }

  auto Size() const -> size_t { return dir_entry_.file_size(); }

  auto GetFile() const -> File {
    File file{};
    file.Emplace<FilesystemFile>(dir_entry_.path().string());
    return file;
  }

 private:
  std::filesystem::directory_entry dir_entry_;
};

}  // namespace chr::storage::internal

#endif  // CHR_STORAGE_FILESYSTEM_FILESYSTEM_ENTRY_H_