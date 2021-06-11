/*
 *  Copyright © 2017-2020 Wellington Wallace
 *
 *  This file is part of EasyEffects.
 *
 *  EasyEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EasyEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EasyEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "autogain_preset.hpp"

AutoGainPreset::AutoGainPreset()
    : input_settings(Gio::Settings::create("com.github.wwmm.easyeffects.autogain",
                                           "/com/github/wwmm/easyeffects/streaminputs/autogain/")),
      output_settings(Gio::Settings::create("com.github.wwmm.easyeffects.autogain",
                                            "/com/github/wwmm/easyeffects/streamoutputs/autogain/")) {}

void AutoGainPreset::save(boost::property_tree::ptree& root,
                          const std::string& section,
                          const Glib::RefPtr<Gio::Settings>& settings) {
  root.put(section + ".autogain.target", settings->get_double("target"));
}

void AutoGainPreset::load(const nlohmann::json& json,
                          const std::string& section,
                          const Glib::RefPtr<Gio::Settings>& settings) {
  update_key<double>(json[section]["autogain"], settings, "target", "target");
}

void AutoGainPreset::write(PresetType preset_type, boost::property_tree::ptree& root) {
  if (preset_type == PresetType::output) {
    save(root, "output", output_settings);
  }
}

void AutoGainPreset::read(PresetType preset_type, const boost::property_tree::ptree& root) {}

void AutoGainPreset::read(PresetType preset_type, const nlohmann::json& json) {
  switch (preset_type) {
    case PresetType::output:
      load(json, "output", output_settings);
      break;
    case PresetType::input:
      load(json, "input", input_settings);
      break;
  }
}
