// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_API_SYNC_ERROR_FACTORY_MOCK_H_
#define CHROME_BROWSER_SYNC_API_SYNC_ERROR_FACTORY_MOCK_H_
#pragma once

#include "chrome/browser/sync/api/sync_error_factory.h"

#include "testing/gmock/include/gmock/gmock.h"

class SyncErrorFactoryMock : public SyncErrorFactory {
 public:
  SyncErrorFactoryMock();
  virtual ~SyncErrorFactoryMock();

  MOCK_METHOD2(CreateAndUploadError, SyncError(
      const tracked_objects::Location& location,
      const std::string& message));
};

#endif  // CHROME_BROWSER_SYNC_API_SYNC_ERROR_FACTORY_MOCK_H_
