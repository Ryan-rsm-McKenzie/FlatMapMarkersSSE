#pragma once

#include <vector>  // vector
#include <map>  // map
#include <utility>  // pair

#include "FNV1A.h"  // hash_32_fnv1a
#include "json.hpp"  // json
#include "Json2Settings.h"  // Json2Settings


class Settings : public Json2Settings::Settings
{
public:
	Settings() = delete;

	static bool	loadSettings(bool a_dumpParse = false);


	static aSetting<nlohmann::json>								whiteListedWorldSpaces;

	static std::map < std::uint32_t, std::pair<bool, float>>	worldSpaces;
	static float												markerHeight;
	static bool													enabled;

private:
	static constexpr char* FILE_NAME = "Data\\SKSE\\Plugins\\FlatMapMarkersSSE.json";
};


template <>
class aSetting<nlohmann::json> :
	public ISetting,
	public std::vector<nlohmann::json>
{
private:
	using json = nlohmann::json;

public:
	aSetting() = delete;
	aSetting(std::string a_key, bool a_consoleOK, std::initializer_list<json> a_list = {}) :
		ISetting(a_key, a_consoleOK),
		std::vector<json>(a_list)
	{}

	virtual ~aSetting()
	{}

	virtual void assign(json& a_val) override
	{
		clear();
		std::string editorID;
		bool enabled;
		float markerHeight;
		for (auto& val : a_val) {
			emplace_back(val);
			editorID = val.find("editorID").value();
			enabled = val.find("enabled").value();
			markerHeight = val.find("markerHeight").value();
			Settings::worldSpaces.emplace(hash_32_fnv1a(editorID), std::make_pair(enabled, markerHeight));
		}
	}

	virtual void dump() override
	{
		_DMESSAGE("%s: [", _key.c_str());
		for (auto& it = begin(); it != end(); ++it) {
			_DMESSAGE("\t%s", it->dump(4).c_str());
		}
		_DMESSAGE("]");
	}

	virtual std::string	getValueAsString() const override
	{
		std::string str = _key + ": [";
		for (auto& it = begin(); it != end(); ++it) {
			str += "\t" + it->dump(4) + "\n";
		}
		str += "]";
		return str;
	}
};
