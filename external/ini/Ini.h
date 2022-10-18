#pragma once

#include <string>

int LoadIniAppInt(const wchar_t* lpKeyName, const int DefaultValue);
void SaveIniAppInt(const wchar_t* lpKeyName, const int Value);
double LoadIniAppDouble(const wchar_t* lpKeyName, const double DefaultValue);
void SaveIniAppDouble(const wchar_t* lpKeyName, const double Value);
wchar_t* LoadIniAppString(const wchar_t* lpKeyName, const const wchar_t* defstr);
void SaveIniAppString(const wchar_t* lpKeyName, const const wchar_t* str);

