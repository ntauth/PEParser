#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include "PEParser.h"

using namespace PEParser;
using NtLoadDriverT = NTSTATUS(NTAPI*) (__in PUNICODE_STRING DriverServiceName);

int _tmain(int argc, _TCHAR** argv)
{
	std::string procedure = "NtLoadDriver";
	
	auto Routine = GetRoutineAddress<NtLoadDriverT>(procedure);
	
	if (Routine != nullptr)
	{
		std::cout << "[Address]: 0x" << Routine << std::endl;
		MessageBeep(0x40);
	}
	else
	{
		std::cout << "No address found." << std::endl;
		MessageBeep(0x10);
	}

	std::cin.get();

	return 0;
}
