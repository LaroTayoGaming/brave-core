/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
#define BRAVE_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_

#include "url/gurl.h"

class Profile;

namespace base {
class Value;
}  // namespace base

namespace content {
class BrowserContext;
}  // namespace content

namespace brave {

enum NewTabPageShowsOptions {
  DASHBOARD,
  HOMEPAGE,
  BLANKPAGE
};

GURL GetNewTabPageURL(Profile* profile);
base::Value GetNewTabShowsOptionsList(Profile* profile);
bool ShouldUseNewTabURLForNewTab(Profile* profile);
bool HandleNewTabPageURLRewrite(GURL* url,
                                content::BrowserContext* browser_context);

}  // namespace brave

#endif  // BRAVE_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
