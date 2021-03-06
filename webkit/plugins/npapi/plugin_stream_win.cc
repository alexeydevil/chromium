// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webkit/plugins/npapi/plugin_stream.h"

#include "base/logging.h"
#include "webkit/plugins/npapi/plugin_instance.h"

namespace webkit {
namespace npapi {

void PluginStream::ResetTempFilenameAndHandle() {
  temp_file_handle_ = INVALID_HANDLE_VALUE;
  temp_file_name_[0] = '\0';
}

void PluginStream::WriteAsFile() {
  if (requested_plugin_mode_ == NP_ASFILE ||
      requested_plugin_mode_ == NP_ASFILEONLY)
    instance_->NPP_StreamAsFile(&stream_, temp_file_name_);
}

size_t PluginStream::WriteBytes(const char *buf, size_t length) {
  DWORD bytes;

  if (!WriteFile(temp_file_handle_, buf, length, &bytes, 0))
    return 0U;

  return static_cast<size_t>(bytes);
}

bool PluginStream::OpenTempFile() {
  DCHECK_EQ(INVALID_HANDLE_VALUE, temp_file_handle_);

  // The reason for using all the Ascii versions of these filesystem
  // calls is that the filename which we pass back to the plugin
  // via NPAPI is an ascii filename.  Otherwise, we'd use wide-chars.
  //
  // TODO:
  // This is a bug in NPAPI itself, and it needs to be fixed.
  // The case which will fail is if a user has a multibyte name,
  // but has the system locale set to english.  GetTempPathA will
  // return junk in this case, causing us to be unable to open the
  // file.

  char temp_directory[MAX_PATH];
  if (GetTempPathA(MAX_PATH, temp_directory) == 0)
    return false;
  if (GetTempFileNameA(temp_directory, "npstream", 0, temp_file_name_) == 0)
    return false;
  temp_file_handle_ = CreateFileA(temp_file_name_,
                                  FILE_ALL_ACCESS,
                                  FILE_SHARE_READ,
                                  0,
                                  CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL,
                                  0);
  if (temp_file_handle_ == INVALID_HANDLE_VALUE) {
    temp_file_name_[0] = '\0';
    return false;
  }
  return true;
}

void PluginStream::CloseTempFile() {
  if (!TempFileIsValid())
    return;

  CloseHandle(temp_file_handle_);
  DeleteFileA(temp_file_name_);
  ResetTempFilenameAndHandle();
}

bool PluginStream::TempFileIsValid() const {
  return temp_file_handle_ != INVALID_HANDLE_VALUE;
}

}  // namespace npapi
}  // namespace webkit
