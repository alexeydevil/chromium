// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_SYNC_ONE_CLICK_SIGNIN_HISTOGRAM_H_
#define CHROME_BROWSER_UI_SYNC_ONE_CLICK_SIGNIN_HISTOGRAM_H_
#pragma once

namespace one_click_signin {

// Enum values used for use with "AutoLogin.Reverse" histograms.
enum {
  // The infobar was shown to the user.
  HISTOGRAM_SHOWN,

  // The user pressed the accept button to perform the suggested action.
  HISTOGRAM_ACCEPTED,

  // The user pressed the reject to turn off the feature.
  HISTOGRAM_REJECTED,

  // The user pressed the X button to dismiss the infobar this time.
  HISTOGRAM_DISMISSED,

  // The user completely ignored the infoar.  Either they navigated away, or
  // they used the page as is.
  HISTOGRAM_IGNORED,

  // The user clicked on the learn more link in the infobar.
  HISTOGRAM_LEARN_MORE,

  // The sync was started with default settings.
  HISTOGRAM_WITH_DEFAULTS,

  // The sync was started with advanced settings.
  HISTOGRAM_WITH_ADVANCED,

  HISTOGRAM_MAX
};

}

#endif  // CHROME_BROWSER_UI_SYNC_ONE_CLICK_SIGNIN_HISTOGRAM_H_
