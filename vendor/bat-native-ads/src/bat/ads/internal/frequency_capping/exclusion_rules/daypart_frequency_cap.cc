/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/exclusion_rules/daypart_frequency_cap.h"

#include "base/strings/stringprintf.h"
#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/internal/frequency_capping/frequency_capping_util.h"

namespace ads {

DaypartFrequencyCap::DaypartFrequencyCap(
    const AdsImpl* const ads)
    : ads_(ads) {
  DCHECK(ads_);
}

DaypartFrequencyCap::~DaypartFrequencyCap() = default;

bool DaypartFrequencyCap::ShouldExclude(
    const CreativeAdInfo& ad,
    const AdEventList& ad_events) {
  if (!DoesRespectCap(ad)) {
    last_message_ = base::StringPrintf("creativeSetId %s excluded as not "
        "within a scheduled time slot", ad.creative_set_id.c_str());

    return true;
  }

  return false;
}

std::string DaypartFrequencyCap::get_last_message() const {
  return last_message_;
}

bool DaypartFrequencyCap::DoesRespectCap(
    const CreativeAdInfo& ad) const {
  if (ad.dayparts.empty()) {
    // Always respect cap if there are no dayparts specified
    return true;
  }

  const base::Time now = base::Time::Now();

  const int local_time_today_as_minutes = ConvertLocalTimeTodayToMinutes(now);

  const std::string local_day_of_week = GetLocalDayOfWeek(now);

  for (const CreativeDaypartInfo& daypart : ad.dayparts) {
    if (!DoesMatchDayOfWeek(daypart, local_day_of_week)) {
      continue;
    }

    if (!DoesMatchTimeSlot(daypart, local_time_today_as_minutes)) {
      continue;
    }

    return true;
  }

  return false;
}

bool DaypartFrequencyCap::DoesMatchDayOfWeek(
    const CreativeDaypartInfo& daypart,
    const std::string& day_of_week) const {
  return daypart.dow.find(day_of_week) != std::string::npos;
}

bool DaypartFrequencyCap::DoesMatchTimeSlot(
    const CreativeDaypartInfo& daypart,
    const int minutes) const {
  if (minutes < daypart.start_minute || minutes > daypart.end_minute) {
    return false;
  }

  return true;
}

}  // namespace ads
