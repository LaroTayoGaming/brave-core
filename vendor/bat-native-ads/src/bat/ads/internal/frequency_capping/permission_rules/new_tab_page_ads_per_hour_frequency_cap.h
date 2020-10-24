/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_FREQUENCY_CAPPING_PERMISSION_RULES_NEW_TAB_PAGE_ADS_PER_HOUR_FREQUENCY_CAP_H_  // NOLINT
#define BAT_ADS_INTERNAL_FREQUENCY_CAPPING_PERMISSION_RULES_NEW_TAB_PAGE_ADS_PER_HOUR_FREQUENCY_CAP_H_  // NOLINT

#include <stdint.h>

#include <deque>
#include <string>

#include "bat/ads/ad_history.h"
#include "bat/ads/internal/frequency_capping/permission_rules/permission_rule.h"

namespace ads {

class AdsImpl;

class NewTabPageAdsPerHourFrequencyCap : public PermissionRule {
 public:
  NewTabPageAdsPerHourFrequencyCap(
      const AdsImpl* const ads);

  ~NewTabPageAdsPerHourFrequencyCap() override;

  NewTabPageAdsPerHourFrequencyCap(
      const NewTabPageAdsPerHourFrequencyCap&) = delete;
  NewTabPageAdsPerHourFrequencyCap& operator=(
      const NewTabPageAdsPerHourFrequencyCap&) = delete;

  bool ShouldAllow(
      const AdEventList& ad_events) override;

  std::string get_last_message() const override;

 private:
  const AdsImpl* const ads_;  // NOT OWNED

  std::string last_message_;

  bool DoesRespectCap(
      const std::deque<uint64_t>& history);

  std::deque<uint64_t> FilterHistory(
      const std::deque<AdHistory>& history) const;
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_FREQUENCY_CAPPING_PERMISSION_RULES_NEW_TAB_PAGE_ADS_PER_HOUR_FREQUENCY_CAP_H_  // NOLINT
