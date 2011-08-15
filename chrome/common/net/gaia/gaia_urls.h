// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_NET_GAIA_GAIA_URLS_H_
#define CHROME_COMMON_NET_GAIA_GAIA_URLS_H_
#pragma once

#include <string>

#include "base/memory/singleton.h"

// A signleton that provides all the URLs that are used for connecting to GAIA.
class GaiaUrls {
 public:
  static GaiaUrls* GetInstance();

  // The URLs for different calls in the Google Accounts programmatic login API.
  const std::string& captcha_url_prefix();
  const std::string& client_login_url();
  const std::string& issue_auth_token_url();
  const std::string& get_user_info_url();
  const std::string& token_auth_url();
  const std::string& merge_session_url();

 private:
  GaiaUrls();
  ~GaiaUrls();

  friend struct DefaultSingletonTraits<GaiaUrls>;

  std::string host_base_;
  std::string captcha_url_prefix_;
  std::string client_login_url_;
  std::string issue_auth_token_url_;
  std::string get_user_info_url_;
  std::string token_auth_url_;
  std::string merge_session_url_;

  DISALLOW_COPY_AND_ASSIGN(GaiaUrls);
};

#endif  // CHROME_COMMON_NET_GAIA_GAIA_URLS_H_
