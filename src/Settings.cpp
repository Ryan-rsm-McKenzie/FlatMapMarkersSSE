#include "Settings.h"

#include <map>  // map
#include <utility>  // pair


bool Settings::loadSettings(bool a_dumpParse)
{
	setFileName(FILE_NAME);
	return Json2Settings::Settings::loadSettings(a_dumpParse);
}


aSetting<nlohmann::json>							Settings::whiteListedWorldSpaces("whiteListedWorldSpaces", false);
std::map < std::uint32_t, std::pair<bool, float>>	Settings::worldSpaces;
float												Settings::markerHeight = 180000.0;
bool												Settings::enabled = false;
