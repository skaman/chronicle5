// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "filesystem_entry.h"

namespace chr::storage::internal {

static_assert(sizeof(FilesystemEntry) <= kEntrySize);

}  // namespace chr::storage::internal
