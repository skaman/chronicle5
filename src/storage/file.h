// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_STORAGE_FILE_H_
#define CHR_STORAGE_FILE_H_

#include "pch.h"

namespace chr::storage {

enum class SeekDir;

namespace internal {
constexpr size_t kFileSize = 312;

struct FileI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto Open() -> void { this->template invoke<0>(*this); }
    auto IsOpen() const -> bool { return this->template invoke<1>(*this); }
    auto Close() -> void { this->template invoke<2>(*this); }
    auto Seek(size_t offset, SeekDir direction) -> void {
      this->template invoke<3>(*this, offset, direction);
    }
    auto Position() -> size_t { return this->template invoke<4>(*this); }
    auto Read(uint8_t* buffer, size_t size) -> void {
      this->template invoke<5>(*this, buffer, size);
    }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::Open, &Type::IsOpen, &Type::Close,
                                &Type::Seek, &Type::Position, &Type::Read>;
};

template <typename T>
concept ConceptFile = std::is_base_of_v<FileI, T>;

struct FilesystemStorage;
struct FilesystemEntry;
}  // namespace internal

//! @brief File position seek direction.
enum class SeekDir {
  kBegin,   //!< Seek from the begin of the file.
  kCurrent, //!< Seek from the current position.
  kEnd      //!< Seek from the end of the file.
};

//! @brief Handle a file from the storage.
struct File {
  //! @brief The copy constructor is not supported.
  //! @param Object to copy.
  File(const File&) = delete;

  //! @brief Move constructor.
  //! @param other Object to move.
  File(File&& other) noexcept : file_(std::move(other.file_)) {}

  ~File() = default;

  //! @brief The copy assignment operator is not supported.
  //! @param Object to copy.
  //! @return Current object.
  File& operator=(const File&) = delete;

  //! @brief Move assignment operator.
  //! @param other Object to move.
  //! @return Current object.
  File& operator=(File&& other) noexcept {
    std::swap(file_, other.file_);
    return *this;
  }

  //! @brief Open the file for read.
  auto Open() -> void { file_->Open(); }

  //! @brief Check if the file is open.
  //! @return True if it's open, otherwise false.
  auto IsOpen() const -> bool { return file_->IsOpen(); }

  //! @brief Close the file.
  auto Close() -> void { file_->Close(); }

  //! @brief Seek to a new position.
  //! @param offset Seek offset.
  //! @param direction Seek direction.
  auto Seek(size_t offset, SeekDir direction) -> void {
    file_->Seek(offset, direction);
  }

  //! @brief Get the position.
  //! @return Position.
  [[nodiscard]] auto Position() -> size_t { return file_->Position(); }

  //! @brief Read data from the file.
  //! @param buffer The buffer where to load read data.
  //! @param size Size of the data to read.
  auto Read(uint8_t* buffer, size_t size) -> void {
    return file_->Read(buffer, size);
  }

  //! @brief Read all the file content.
  //! @return File content.
  [[nodiscard]] auto ReadAll() -> std::vector<uint8_t> {
    Seek(0, SeekDir::kEnd);
    auto end = Position();
    Seek(0, SeekDir::kBegin);

    auto size = end - Position();
    if (size == 0) {
      return {};
    }

    std::vector<uint8_t> buffer(size);
    Read(buffer.data(), buffer.size());
    return buffer;
  }

 private:
  explicit File() = default;

  template <internal::ConceptFile Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    file_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::FileI, internal::kFileSize> file_{};

  friend struct internal::FilesystemStorage;
  friend struct internal::FilesystemEntry;
};

}  // namespace chr::storage

#endif  // CHR_STORAGE_FILE_H_