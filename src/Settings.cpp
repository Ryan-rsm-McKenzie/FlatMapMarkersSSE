#include "Settings.h"


bool Settings::loadSettings(bool a_dumpParse)
{
	setFileName(FILE_NAME);
	return Json2Settings::Settings::loadSettings(a_dumpParse);
}


fSetting Settings::markerHeight("markerHeight", true, 180000.0);
