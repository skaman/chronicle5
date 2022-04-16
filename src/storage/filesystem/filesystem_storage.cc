// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "filesystem_storage.h"

#include "filesystem_entry.h"
#include "filesystem_file.h"

namespace chr::storage::internal {

static_assert(sizeof(FilesystemStorage) <= kStorageSize);

auto FilesystemStorage::GetEntries(std::string_view path) const
    -> std::vector<Entry> {
  std::vector<Entry> entries{};
  std::filesystem::path current_path{base_path_};
  current_path.concat(path);

  for (auto const& dir_entry :
       std::filesystem::directory_iterator{current_path}) {
    Entry entry{};
    entry.Emplace<FilesystemEntry>(dir_entry);
    entries.emplace_back(std::move(entry));
  }

  return entries;
}

auto FilesystemStorage::GetFile(std::string_view path) const -> File {
  std::filesystem::path current_path{base_path_};
  current_path.concat(path);

  File file{};
  file.Emplace<FilesystemFile>(current_path.string());
  return file;
}

}  // namespace chr::storage::internal
