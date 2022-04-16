// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_STORAGE_ENTRY_H_
#define CHR_STORAGE_ENTRY_H_

#include "file.h"
#include "pch.h"

namespace chr::storage {

namespace internal {
constexpr size_t kEntrySize = 72;

struct EntryI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto Name() const -> std::string { return this->template invoke<0>(*this); }
    auto HaveExtension() const -> bool {
      return this->template invoke<1>(*this);
    }
    auto Extension() const -> std::string {
      return this->template invoke<2>(*this);
    }
    auto IsDirectory() const -> bool { return this->template invoke<3>(*this); }
    auto Size() const -> size_t { return this->template invoke<4>(*this); }
    auto GetFile() const -> File { return this->template invoke<5>(*this); }
  };

  template <typename Type>
  using impl =
      entt::value_list<&Type::Name, &Type::HaveExtension, &Type::Extension,
                       &Type::IsDirectory, &Type::Size, &Type::GetFile>;
};

template <typename T>
concept ConceptEntry = std::is_base_of_v<EntryI, T>;

struct FilesystemStorage;
}  // namespace internal

//! @brief Handle an entry from the storage.
struct Entry {
  //! @brief The copy constructor is not supported.
  //! @param Object to copy.
  Entry(const Entry&) = delete;

  //! @brief Move constructor.
  //! @param other Object to move.
  Entry(Entry&& other) noexcept : entry_(std::move(other.entry_)) {}

  ~Entry() = default;

  //! @brief The copy assignment operator is not supported.
  //! @param Object to copy.
  //! @return Current object.
  Entry& operator=(const Entry&) = delete;

  //! @brief Move assignment operator.
  //! @param other Object to move.
  //! @return Current object.
  Entry& operator=(Entry&& other) noexcept {
    std::swap(entry_, other.entry_);
    return *this;
  }

  //! @brief Get the entry name.
  //! @return Entry name.
  [[nodiscard]] auto Name() const -> std::string { return entry_->Name(); }

  //! @brief Check if the entry name have an extensions.
  //! @return True if have an extension, otherwise false.
  [[nodiscard]] auto HaveExtension() const -> bool {
    return entry_->HaveExtension();
  }

  //! @brief Get the entry extension.
  //! @return Entry extension.
  [[nodiscard]] auto Extension() const -> std::string {
    return entry_->Extension();
  }

  //! @brief Check if the entry is a directory.
  //! @return True if is a directory, otherwise false.
  [[nodiscard]] auto IsDirectory() const -> bool {
    return entry_->IsDirectory();
  }

  //! @brief Get the entry size.
  //! @return Entry size.
  [[nodiscard]] auto Size() const -> size_t { return entry_->Size(); }

  //! @brief Get the file object for I/O operations.
  //! @return The file object.
  [[nodiscard]] auto GetFile() const -> File { return entry_->GetFile(); }

 private:
  explicit Entry() = default;

  template <internal::ConceptEntry Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    entry_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::EntryI, internal::kEntrySize> entry_{};

  friend struct internal::FilesystemStorage;
};

}  // namespace chr::storage

#endif  // CHR_STORAGE_ENTRY_H_