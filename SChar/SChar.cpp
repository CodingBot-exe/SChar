// SChar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include <cassert>
#include <iostream>
#include <string>
#include <Windows.h>

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	_wsetlocale(LC_ALL, L".utf8");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::string inputString;
	std::cout << "Type \"exit\" if you want to exit." << std::endl;

	while (std::getline(std::cin, inputString))
	{
		const char* const rawString = inputString.c_str();
		const int stringLength = static_cast<int>(strlen(rawString) + 1);

		if (strcmp(rawString, "exit") == 0)
			break;

		const int wCharLength = MultiByteToWideChar(CP_UTF8, NULL, rawString, stringLength, nullptr, 0);

		WCHAR* const outputString = new WCHAR[wCharLength];
		const int convertedLength = MultiByteToWideChar(CP_UTF8, NULL, rawString, stringLength, outputString, wCharLength);
		if (convertedLength != wCharLength)
		{
			std::cout << "convert from multibyte to widechar failed" << std::endl;
			delete[] outputString;
			continue;
		}

		for (int i = 0; i < wCharLength; i++)
		{
			std::wcout << outputString[i] << std::endl;
		}

		delete[] outputString;
	}

	return S_OK;
}