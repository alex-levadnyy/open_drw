#pragma once

#include <fstream>
#include <stdio.h>
#include <wchar.h>
#include <vector>

/*-------------------------- Pro/Toolkit includes ---------------------------*/
#include <ProToolkit.h>
#include <ProMenu.h>
#include <ProMenuBar.h>
#include <ProUtil.h>

#include <pfcWindow.h>
#include <pfcSession.h>
#include <wfcSession.h>
#include <pfcGlobal.h>
#include <pfcExceptions.h>
#include <xstring.h>
#include <wfcGlobal.h>
#include <stdcols.h>
#include <pfcProToolkit.h>

struct Settings
{
	bool subdir = true;
	xstring suff_sp = "_SP";
};

Settings LoadSettings();
void SaveSettings(bool recursive_search, xstring syffix);