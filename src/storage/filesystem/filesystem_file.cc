// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "filesystem_file.h"

namespace chr::storage::internal {

static_assert(sizeof(FilesystemFile) <= kFileSize);

constexpr auto GetStdSeekDir(SeekDir direction) -> std::ios_base::seekdir {
  switch (direction) {
    case SeekDir::kBegin:
      return std::ios::beg;
    case SeekDir::kCurrent:
      return std::ios::cur;
    case SeekDir::kEnd:
      return std::ios::end;
    default:
      break;
  }

  debug::Assert(false, "Invalid SeekDir value");

  return std::ios::beg;
}

auto FilesystemFile::Seek(size_t offset, SeekDir direction) -> void {
  file_.seekg(offset, GetStdSeekDir(direction));
}

}  // namespace chr::storage::internal
