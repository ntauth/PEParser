#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include "PEParser.h"

typedef void* (WINAPI *GETPROCADDRESS) (
	__in HMODULE hModulem,
	__in LPCSTR  lProcName
);

int _tmain(int argc, _TCHAR** argv)
{
	std::string procedure;

	std::cout << "<< Procedure Name: ";
	std::cin  >> procedure;

	auto Routine = PEParser::GetRoutineAddress<void*>(procedure);

	if (Routine != nullptr)
	{
		std::cout << "\t  > [Address]: 0x" << Routine << std::endl;
		MessageBeep(0x40);
	}
	else
	{
		std::wcout << "No address found." << std::endl;
		MessageBeep(0x10);
	}

	std::wcin.get();
	std::wcin.get();

	return 0;
}
