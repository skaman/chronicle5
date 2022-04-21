// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_STORAGE_STORAGE_H_
#define CHR_STORAGE_STORAGE_H_

#include "entry.h"
#include "file.h"
#include "pch.h"

namespace chr::storage {

namespace internal {
constexpr size_t kStorageSize = 40;

struct StorageI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto SetBasePath(std::string_view path) -> void {
      this->template invoke<0>(*this, path);
    }
    auto GetEntries(std::string_view path) const -> std::vector<Entry> {
      return this->template invoke<1>(*this, path);
    }
    auto GetFile(std::string_view path) const -> File {
      return this->template invoke<2>(*this, path);
    }
  };

  template <typename Type>
  using impl =
      entt::value_list<&Type::SetBasePath, &Type::GetEntries, &Type::GetFile>;
};

template <typename T>
concept ConceptStorage = std::is_base_of_v<StorageI, T>;
}  // namespace internal

//! @brief Storage backend type
enum class BackendType {
  kFileSystem  //!< Local file system.
};

//! @brief Handle a storage backend for I/O operations on files
struct Storage {
  //! @brief Construct the storage object for the requested backend type.
  //! @param type Requested backend type
  explicit Storage(BackendType type);

  //! @brief The copy constructor is not supported.
  Storage(const Storage &) = delete;

  //! @brief Move constructor.
  Storage(Storage &&other) noexcept : storage_{std::move(other.storage_)} {}

  ~Storage() = default;

  //! @brief The copy assignment operator is not supported.
  Storage &operator=(const Storage &) = delete;

  //! @brief Move assignment operator.
  Storage &operator=(Storage &&other) noexcept {
    std::swap(storage_, other.storage_);
    return *this;
  }

  //! @brief Set the base path for the storage, the behavior of this method can
  //!        change based on the backend type.
  //!        For local filesystem indicate the root path where the files are
  //!        located.
  //! @param path Base path to set.
  auto SetBasePath(std::string_view path) -> void {
    storage_->SetBasePath(path);
  }

  //! @brief Get all the entries for a given path.
  //! @param path Path to read.
  //! @return All the entries in path.
  auto GetEntries(std::string_view path) const -> std::vector<Entry> {
    return storage_->GetEntries(path);
  }

  //! @brief Get a file from a given path.
  //! @param path File path.
  //! @return File object.
  auto GetFile(std::string_view path) const -> File {
    return storage_->GetFile(path);
  }

 private:
  template <internal::ConceptStorage Type>
  auto GetNativeType() const -> const Type & {
    return *static_cast<const Type *>(storage_.data());
  }

  entt::basic_poly<internal::StorageI, internal::kStorageSize> storage_{};
};

}  // namespace chr::storage

#endif  // CHR_STORAGE_STORAGE_H_