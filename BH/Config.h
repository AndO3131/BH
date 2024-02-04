#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <map>
#include <list>
#include "Common.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::ordered_json;

struct Toggle {
	unsigned int hotkey;
	bool isEnabled;
};

struct SettingsInt {
	union {
		int value;
		unsigned int uValue;
	};
	int defValue;
	int minValue;
	int maxValue;
};

struct SettingsFloat {
	float value;
	float defValue;
	float minValue;
	float maxValue;
};

struct SettingsBool {
	bool value;
	bool defValue;
};

struct SettingsString {
	std::wstring value;
	std::wstring defValue;
};

struct SettingsToggle {
	Toggle toggle;
	Toggle defToggle;
};

struct SettingsKey {
	unsigned int hotkey;
	unsigned int defHotkey;
};

struct SettingsArray {
	std::vector<std::wstring> values;
	std::vector<std::wstring> defValues;
};

struct SettingsAssoc {
	std::map<std::wstring, std::wstring> values;
	std::map<std::wstring, std::wstring> defValues;
};

enum ConfigType {
	CTBoolean,
	CTString,
	CTInt,
	CTKey,
	CTToggle,
	CTArray,
	CTAssoc,
	CTAssocInt,
	CTAssocBool
};

class ConfigEntry {
public:
	ConfigType type;
	std::wstring key;
	std::wstring value;
	std::wstring comment;
	int line;
	void* pointer;
	Toggle* toggle;


};

inline bool operator< (const ConfigEntry& lhs, const ConfigEntry& rhs) {
	// std::tuple's lexicographic ordering does all the actual work for you
	// and using std::tie means no actual copies are made
	return std::tie(lhs.value, lhs.key) < std::tie(rhs.value, rhs.key);
}


class Config {
private:
	std::string configName;
	// Only used in lootfilter Parse()
	std::map<std::wstring, ConfigEntry> contents;
	vector<pair<wstring, wstring>> orderedKeyVals;
public:
	void SaveConfig();
	void LoadConfig();
	Config(std::string name) : configName(name) {};

	std::string GetConfigName();
	void SetConfigName(std::string name);

	// Functions to read values from the configuration
	int GetInt(json::json_pointer sectionKey, std::wstring key, SettingsInt def);
	float GetFloat(json::json_pointer sectionKey, std::wstring key, SettingsFloat def);
	bool GetBool(json::json_pointer sectionKey, std::wstring key, SettingsBool def);
	std::wstring GetString(json::json_pointer sectionKey, std::wstring key, SettingsString def);
	Toggle GetToggle(json::json_pointer sectionKey, std::wstring key, SettingsToggle def);
	unsigned int GetKey(json::json_pointer sectionKey, std::wstring key, SettingsKey def);
	std::vector<std::wstring> GetArray(json::json_pointer sectionKey, std::wstring key, SettingsArray def);
	std::map<std::wstring, std::wstring> GetAssoc(json::json_pointer sectionKey, std::wstring key, SettingsAssoc def);

	// Functions to read values from the lootfilter configuration
	bool Parse();
	vector<pair<wstring, wstring>> ReadMapList(std::wstring key, vector<pair<wstring,wstring>>& value);
};