#include "Settings.h"


bool Settings::LoadSettings(bool a_dumpParse)
{
	auto [log, success] = Json2Settings::load_settings(FILE_NAME, a_dumpParse);
	if (!log.empty()) {
		_ERROR("%s", log.c_str());
	}

	if (success) {
		for (auto& elem : *whiteListedWorldSpaces) {
			worldSpaces[elem.editorID] = std::make_pair(elem.enabled, elem.markerHeight);
		}
		whiteListedWorldSpaces->clear();
		whiteListedWorldSpaces->shrink_to_fit();
	}

	return success;
}


decltype(Settings::whiteListedWorldSpaces) Settings::whiteListedWorldSpaces("whiteListedWorldSpaces");
decltype(Settings::worldSpaces) Settings::worldSpaces;
