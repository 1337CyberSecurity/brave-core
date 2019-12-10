/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/conversion_tracking_info.h"

#include "bat/ads/internal/json_helper.h"

namespace ads {

ConversionTrackingInfo::ConversionTrackingInfo() :
    creative_set_id(""),
    type(""),
    url_pattern(""),
    observation_window(0) {}

ConversionTrackingInfo::ConversionTrackingInfo(const ConversionTrackingInfo& info) :
    creative_set_id(info.creative_set_id),
    type(info.type),
    url_pattern(info.url_pattern),
    observation_window(info.observation_window) {}

ConversionTrackingInfo::~ConversionTrackingInfo() = default;

const std::string ConversionTrackingInfo::ToJson() const {
  std::string json;
  SaveToJson(*this, &json);
  return json;
}

Result ConversionTrackingInfo::FromJson(
    const std::string& json,
    std::string* error_description) {
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.HasParseError()) {
    if (error_description) {
      *error_description = helper::JSON::GetLastError(&document);
    }

    return FAILED;
  }

  if (document.HasMember("creative_set_id")) {
    creative_set_id = document["creative_set_id"].GetString();
  }

  if (document.HasMember("type")) {
    type = document["type"].GetString();
  }

  if (document.HasMember("url_pattern")) {
    url_pattern = document["url_pattern"].GetString();
  }

  if (document.HasMember("observation_window")) {
    observation_window = document["observation_window"].GetUint();
  }

  return SUCCESS;
}

void SaveToJson(JsonWriter* writer, const ConversionTrackingInfo& info) {
  writer->StartObject();

  writer->String("creative_set_id");
  writer->String(info.creative_set_id.c_str());

  writer->String("type");
  writer->String(info.type.c_str());

  writer->String("url_pattern");
  writer->String(info.url_pattern.c_str());

  writer->String("observation_window");
  writer->Uint(info.observation_window);

  writer->EndObject();
}

}  // namespace ads
