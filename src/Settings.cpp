#include "Settings.h"

#include <map>  // map
#include <utility>  // pair


bool Settings::loadSettings(bool a_dumpParse)
{
	setFileName(FILE_NAME);
	return Json2Settings::Settings::loadSettings(a_dumpParse);
}


decltype(Settings::whiteListedWorldSpaces)	Settings::whiteListedWorldSpaces("whiteListedWorldSpaces", false);
decltype(Settings::worldSpaces)				Settings::worldSpaces;
decltype(Settings::markerHeight)			Settings::markerHeight = 180000.0;
decltype(Settings::enabled)					Settings::enabled = false;
