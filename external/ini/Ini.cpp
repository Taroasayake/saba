
#include <Windows.h>
#include <shlwapi.h>		// Use shlwapi.lib!

#include <stdint.h>
#include <string>
#include <codecvt> 
#include <wchar.h>

#include "Ini.h"

#pragma comment(lib, "shlwapi.lib")

static wchar_t ininame[1025] = { 0 };
static wchar_t ReturnValue[2048];

static void InifileInitFirst(void)
{
	if (ininame[0] == 0)
	{
		GetModuleFileName(NULL, ininame, 1024);
		PathRemoveFileSpec(ininame);
		PathAppend(ininame, L"saba.ini");
	}
}

int LoadIniAppInt(const wchar_t * lpKeyName, const int DefaultValue)
{
	InifileInitFirst();
	int result = GetPrivateProfileInt(L"APPSETTINGS", lpKeyName, DefaultValue, ininame);
	return result;
}
void SaveIniAppInt(const wchar_t* lpKeyName, const int Value)
{
	InifileInitFirst();
	std::wstring setstr = std::to_wstring(Value);
	BOOL result = WritePrivateProfileString(L"APPSETTINGS", lpKeyName, setstr.c_str(), ininame);
}

double LoadIniAppDouble(const wchar_t * lpKeyName, const double DefaultValue)
{
	std::wstring defstr = std::to_wstring(DefaultValue);
	InifileInitFirst();
	int result = GetPrivateProfileString(L"APPSETTINGS", lpKeyName, defstr.c_str(), ReturnValue, sizeof(ReturnValue), ininame);
	std::wstring retstr = ReturnValue;
	double dValue = std::stod(retstr.c_str());
	return dValue;
}
void SaveIniAppDouble(const wchar_t* lpKeyName, const double Value)
{
	InifileInitFirst();
	std::wstring setstr = std::to_wstring(Value);
	BOOL result = WritePrivateProfileString(L"APPSETTINGS", lpKeyName, setstr.c_str(), ininame);
}

wchar_t* LoadIniAppString(const wchar_t* lpKeyName, const const wchar_t* defstr)
{
	InifileInitFirst();
	int result = GetPrivateProfileString(L"APPSETTINGS", lpKeyName, defstr, ReturnValue, sizeof(ReturnValue), ininame);
	return ReturnValue;
}

void SaveIniAppString(const wchar_t* lpKeyName, const const wchar_t* str)
{
	InifileInitFirst();
	BOOL result = WritePrivateProfileString(L"APPSETTINGS", lpKeyName, str, ininame);
}
