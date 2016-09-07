#pragma once

#include <string>
#include "TEB.h"

namespace PEParser
{
	//
	// _RvaToAbsolute
	// Converts an RVA to an absolute VA
	//
	template<typename TPointer>
	__inline TPointer RvaToAbsolute(const void* RVA, const void* BaseAddress);

	//
	// _GetRoutineAddress
	// Returns, if any, the address of the specified structure
	//
	template<typename TProcedure>
	TProcedure GetRoutineAddress(std::string Procedure);
}

template<typename TPointer>
__inline TPointer PEParser::RvaToAbsolute(const void* RVA, const void* BaseAddress)
{
	return reinterpret_cast<TPointer>((long long)BaseAddress + (long long)RVA);
}

template<typename TProcedure>
TProcedure PEParser::GetRoutineAddress(std::string Procedure)
{
	/* Ricava il TEB e il PEB */
	TEB* TEB = NtCurrentTeb();
	PEB* PEB = TEB->ProcessEnvironmentBlock;

	/* Estrai la testa della lista dei moduli mappati in VA */
	LIST_ENTRY* Head = &PEB->Ldr->InMemoryOrderModuleList;
	LIST_ENTRY* Flink;

	for (Flink = Head->Flink; Flink != Head; Flink = Flink->Flink)
	{
		/* Estrai la struttura che rappresenta il modulo */
		LDR_DATA_TABLE_ENTRY* Ldt = reinterpret_cast<LDR_DATA_TABLE_ENTRY*>(Flink);
		/* Estrai l'intestazione DOS del modulo */
		IMAGE_DOS_HEADER* DOS = reinterpret_cast<IMAGE_DOS_HEADER*>(Ldt->DllBase);
		/* Estrai l'intestazione PE del modulo */
		IMAGE_NT_HEADERS* PEH = RvaToAbsolute<IMAGE_NT_HEADERS*>((const void*)DOS->e_lfanew, Ldt->DllBase);

		// std::wcout << "[MODULO]: > " << Ldt->BaseDllName.Buffer << std::endl;
		/* Controlla e sanitizza le intestazioni*/
		if (DOS->e_magic != IMAGE_DOS_SIGNATURE)
		{
			// std::wcout << "\t > [DOS HEADER]: Invalid DOS Signature." << std::endl;
			continue;
		}
		if (PEH->Signature != IMAGE_NT_SIGNATURE)
		{
			// std::wcout << "\t > [PE HEADER]: Invalid NT Signature." << std::endl;
			continue;
		}

		IMAGE_DATA_DIRECTORY* Idd = PEH->OptionalHeader.DataDirectory;
		/* EXPORT TABLE non presente */
		if (!Idd[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
		{
			// std::wcout << "\t  > [PE HEADER]: Export Table not found." << std::endl;
			continue;
		}

		IMAGE_EXPORT_DIRECTORY* Ied = RvaToAbsolute<IMAGE_EXPORT_DIRECTORY*>((const void*)Idd[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, Ldt->DllBase);
		const DWORD* ArrayOfNameRVAs = RvaToAbsolute<DWORD*>((const void*)Ied->AddressOfNames, Ldt->DllBase);

		for (DWORD _offset = 0; _offset < Ied->NumberOfNames; _offset++)
		{
			const char* _name = RvaToAbsolute<const char*>((const void*)(ArrayOfNameRVAs[_offset]), Ldt->DllBase);
			std::string name(_name);

			if (name == Procedure)
			{
				WORD* NameOrdinals = RvaToAbsolute<WORD*>((const void*)Ied->AddressOfNameOrdinals, Ldt->DllBase);
				DWORD* FunctionAddresses = RvaToAbsolute<DWORD*>((const void*)Ied->AddressOfFunctions, Ldt->DllBase);

				return RvaToAbsolute<TProcedure>((const void*)FunctionAddresses[NameOrdinals[_offset]], Ldt->DllBase);
			}
		}
	}

	return nullptr;
}