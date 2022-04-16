// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_STORAGE_FILESYSTEM_FILESYSTEM_FILE_H_
#define CHR_STORAGE_FILESYSTEM_FILESYSTEM_FILE_H_

#include <filesystem>
#include <fstream>

#include "file.h"
#include "pch.h"

namespace chr::storage::internal {

struct FilesystemFile : FileI {
  explicit FilesystemFile(std::string_view path) : path_{path} {
    file_.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  };
  ~FilesystemFile() {
    if (IsOpen()) {
      try {
        Close();
      } catch (std::exception e) {
        log::Err("{}", e.what());
      }
    }
  }

  auto Open() -> void { file_.open(path_, std::ios::binary | std::ios::ate); }
  auto IsOpen() const -> bool { return file_.is_open(); }
  auto Close() -> void { file_.close(); }
  auto Seek(size_t offset, SeekDir direction) -> void;
  auto Position() -> size_t { return file_.tellg(); }
  auto Read(uint8_t* buffer, size_t size) -> void { file_.read(buffer, size); }

 private:
  std::filesystem::path path_;
  std::basic_ifstream<uint8_t> file_{};
};

}  // namespace chr::storage::internal

#endif  // CHR_STORAGE_FILESYSTEM_FILESYSTEM_FILE_H_