#include "Settings.h"


bool Settings::loadSettings(bool a_dumpParse)
{
	return Json2Settings::Settings::loadSettings(FILE_NAME, false, a_dumpParse);
}


decltype(Settings::whiteListedWorldSpaces)	Settings::whiteListedWorldSpaces("whiteListedWorldSpaces", false);
decltype(Settings::worldSpaces)				Settings::worldSpaces;
decltype(Settings::markerHeight)			Settings::markerHeight = 180000.0;
decltype(Settings::enabled)					Settings::enabled = false;
