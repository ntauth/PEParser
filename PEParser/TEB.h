#pragma once

#include <Windows.h>
#include <SubAuth.h>

#define WIN32_LEAN_AND_MEAN

typedef struct _CLIENT_ID {
	/*0x000*/ PVOID UniqueProcess;
	/*0x004*/ PVOID UniqueThread;
} CLIENT_ID, *PCLIENT_ID;


typedef struct _GDI_TEB_BATCH {
	/*0x000*/ DWORD Offset;
	/*0x004*/ DWORD HDC;
	/*0x008*/ DWORD Buffer[310];
} GDI_TEB_BATCH, *PGDI_TEB_BATCH;


typedef struct _ACTIVATION_CONTEXT *PACTIVATION_CONTEXT;
typedef struct _ACTIVATION_CONTEXT_DATA *PACTIVATION_CONTEXT_DATA;
typedef struct _ASSEMBLY_STORAGE_MAP *PASSEMBLY_STORAGE_MAP;
typedef struct _FLS_CALLBACK_INFO *PFLS_CALLBACK_INFO;


typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
	/*0x000*/ struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *Previous;
	/*0x004*/ PACTIVATION_CONTEXT ActivationContext;
	/*0x008*/ DWORD Flags;
} RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;


typedef struct _ACTIVATION_CONTEXT_STACK
{
	/*0x000*/ PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame;
	/*0x004*/ LIST_ENTRY FrameListCache;
	/*0x00c*/ DWORD Flags;
	/*0x010*/ DWORD NextCookieSequenceNumber;
	/*0x014*/ DWORD StackId;
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;


typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
	/*0x000*/ DWORD Flags;
	/*0x004*/ PSTR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;


typedef struct _TEB_ACTIVE_FRAME
{
	/*0x000*/ DWORD Flags;
	/*0x004*/ struct _TEB_ACTIVE_FRAME *Previous;
	/*0x008*/ PTEB_ACTIVE_FRAME_CONTEXT Context;
} TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;


typedef struct _PEB_LDR_DATA {
	/*0x000*/ DWORD Length;
	/*0x004*/ UCHAR Initialized;
	/*0x008*/ PVOID SsHandle;
	/*0x00c*/ LIST_ENTRY InLoadOrderModuleList;
	/*0x014*/ LIST_ENTRY InMemoryOrderModuleList;
	/*0x01c*/ LIST_ENTRY InInitializationOrderModuleList;
	/*0x024*/ PVOID EntryInProgress;
	/*0x028*/ UCHAR ShutdownInProgress;
	/*0x02c*/ PVOID ShutdownThreadId;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;

	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};

	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};

	_ACTIVATION_CONTEXT * EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _CURDIR
{
	/*0x000*/ UNICODE_STRING DosPath;
	/*0x008*/ PVOID Handle;
} CURDIR, *PCURDIR;


typedef struct _RTL_DRIVE_LETTER_CURDIR
{
	/*0x000*/ WORD Flags;
	/*0x002*/ WORD Length;
	/*0x004*/ DWORD TimeStamp;
	/*0x008*/ STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;


typedef struct _RTL_USER_PROCESS_PARAMETERS {
	/*0x000*/ DWORD MaximumLength;
	/*0x004*/ DWORD Length;
	/*0x008*/ DWORD Flags;
	/*0x00c*/ DWORD DebugFlags;
	/*0x010*/ PVOID ConsoleHandle;
	/*0x014*/ DWORD ConsoleFlags;
	/*0x018*/ PVOID StandardInput;
	/*0x01c*/ PVOID StandardOutput;
	/*0x020*/ PVOID StandardError;
	/*0x024*/ CURDIR CurrentDirectory;
	/*0x030*/ UNICODE_STRING DllPath;
	/*0x038*/ UNICODE_STRING ImagePathName;
	/*0x040*/ UNICODE_STRING CommandLine;
	/*0x048*/ PVOID Environment;
	/*0x04c*/ DWORD StartingX;
	/*0x050*/ DWORD StartingY;
	/*0x054*/ DWORD CountX;
	/*0x058*/ DWORD CountY;
	/*0x05c*/ DWORD CountCharsX;
	/*0x060*/ DWORD CountCharsY;
	/*0x064*/ DWORD FillAttribute;
	/*0x068*/ DWORD WindowFlags;
	/*0x06c*/ DWORD ShowWindowFlags;
	/*0x070*/ UNICODE_STRING WindowTitle;
	/*0x078*/ UNICODE_STRING DesktopInfo;
	/*0x080*/ UNICODE_STRING ShellInfo;
	/*0x088*/ UNICODE_STRING RuntimeData;
	/*0x090*/ RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
	/*0x290*/ DWORD EnvironmentSize;
	/*0x294*/ DWORD EnvironmentVersion;
	/*0x298*/ PVOID PackageDependencyData;
	/*0x29c*/ DWORD ProcessGroupId;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;


typedef struct _PEB {
	/*0x000*/ UCHAR InheritedAddressSpace;
	/*0x001*/ UCHAR ReadImageFileExecOptions;
	/*0x002*/ UCHAR BeingDebugged;
	union {
		/*0x003*/ UCHAR BitField;
		struct {
			/*0x003*/ UCHAR ImageUsesLargePages : 1;
			/*0x003*/ UCHAR IsProtectedProcess : 1;
			/*0x003*/ UCHAR IsImageDynamicallyRelocated : 1;
			/*0x003*/ UCHAR SkipPatchingUser32Forwarders : 1;
			/*0x003*/ UCHAR IsPackagedProcess : 1;
			/*0x003*/ UCHAR IsAppContainer : 1;
			/*0x003*/ UCHAR IsProtectedProcessLight : 1;
			/*0x003*/ UCHAR SpareBits : 1;
		};
	};
	/*0x004*/ PVOID Mutant;
	/*0x008*/ PVOID ImageBaseAddress;
	/*0x00c*/ PPEB_LDR_DATA Ldr;
	/*0x010*/ PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	/*0x014*/ PVOID SubSystemData;
	/*0x018*/ PVOID ProcessHeap;
	/*0x01c*/ PRTL_CRITICAL_SECTION FastPebLock;
	/*0x020*/ PVOID AtlThunkSListPtr;
	/*0x024*/ PVOID IFEOKey;
	union {
		/*0x028*/ DWORD CrossProcessFlags;
		struct {
			/*0x028*/ DWORD ProcessInJob : 1;
			/*0x028*/ DWORD ProcessInitializing : 1;
			/*0x028*/ DWORD ProcessUsingVEH : 1;
			/*0x028*/ DWORD ProcessUsingVCH : 1;
			/*0x028*/ DWORD ProcessUsingFTH : 1;
			/*0x028*/ DWORD ReservedBits0 : 27;
		};
	};
	/*0x02c*/ PVOID KernelCallbackTable;
	/*0x02c*/ PVOID UserSharedInfoPtr;
	/*0x030*/ DWORD SystemReserved[1];
	/*0x034*/ DWORD AtlThunkSListPtr32;
	/*0x038*/ PVOID ApiSetMap;
	/*0x03c*/ DWORD TlsExpansionCounter;
	/*0x040*/ PVOID TlsBitmap;
	/*0x044*/ DWORD TlsBitmapBits[2];
	/*0x04c*/ PVOID ReadOnlySharedMemoryBase;
	/*0x050*/ PVOID SparePvoid0;
	/*0x054*/ PVOID *ReadOnlyStaticServerData;
	/*0x058*/ PVOID AnsiCodePageData;
	/*0x05c*/ PVOID OemCodePageData;
	/*0x060*/ PVOID UnicodeCaseTableData;
	/*0x064*/ DWORD NumberOfProcessors;
	/*0x068*/ DWORD NtGlobalFlag;
	/*0x070*/ LARGE_INTEGER CriticalSectionTimeout;
	/*0x078*/ DWORD HeapSegmentReserve;
	/*0x07c*/ DWORD HeapSegmentCommit;
	/*0x080*/ DWORD HeapDeCommitTotalFreeThreshold;
	/*0x084*/ DWORD HeapDeCommitFreeBlockThreshold;
	/*0x088*/ DWORD NumberOfHeaps;
	/*0x08c*/ DWORD MaximumNumberOfHeaps;
	/*0x090*/ PVOID *ProcessHeaps;
	/*0x094*/ PVOID GdiSharedHandleTable;
	/*0x098*/ PVOID ProcessStarterHelper;
	/*0x09c*/ DWORD GdiDCAttributeList;
	/*0x0a0*/ PRTL_CRITICAL_SECTION LoaderLock;
	/*0x0a4*/ DWORD OSMajorVersion;
	/*0x0a8*/ DWORD OSMinorVersion;
	/*0x0ac*/ DWORD OSBuildNumber;
	/*0x0ae*/ DWORD OSCSDVersion;
	/*0x0b0*/ DWORD OSPlatformId;
	/*0x0b4*/ DWORD ImageSubsystem;
	/*0x0b8*/ DWORD ImageSubsystemMajorVersion;
	/*0x0bc*/ DWORD ImageSubsystemMinorVersion;
	/*0x0c0*/ DWORD ActiveProcessAffinityMask;
	/*0x0c4*/ DWORD GdiHandleBuffer[34];
	/*0x14c*/ PVOID PostProcessInitRoutine;
	/*0x150*/ PVOID TlsExpansionBitmap;
	/*0x154*/ DWORD TlsExpansionBitmapBits[32];
	/*0x1d4*/ DWORD SessionId;
	/*0x1d8*/ ULARGE_INTEGER AppCompatFlags;
	/*0x1e0*/ ULARGE_INTEGER AppCompatFlagsUser;
	/*0x1e8*/ PVOID pShimData;
	/*0x1ec*/ PVOID AppCompatInfo;
	/*0x1f0*/ UNICODE_STRING CSDVersion;
	/*0x1f8*/ PACTIVATION_CONTEXT_DATA ActivationContextData;
	/*0x1fc*/ PASSEMBLY_STORAGE_MAP ProcessAssemblyStorageMap;
	/*0x200*/ PACTIVATION_CONTEXT_DATA SystemDefaultActivationContextData;
	/*0x204*/ PASSEMBLY_STORAGE_MAP SystemAssemblyStorageMap;
	/*0x208*/ DWORD MinimumStackCommit;
	/*0x20c*/ PFLS_CALLBACK_INFO FlsCallback;
	/*0x210*/ LIST_ENTRY FlsListHead;
	/*0x218*/ PVOID FlsBitmap;
	/*0x21c*/ DWORD FlsBitmapBits[4];
	/*0x22c*/ DWORD FlsHighIndex;
	/*0x230*/ PVOID WerRegistrationData;
	/*0x234*/ PVOID WerShipAssertPtr;
	/*0x238*/ PVOID pUnused;
	/*0x23c*/ PVOID pImageHeaderHash;
	union {
		/*0x240*/ DWORD TracingFlags;
		/*0x240*/ DWORD HeapTracingEnabled : 1;
		/*0x240*/ DWORD CritSecTracingEnabled : 1;
		/*0x240*/ DWORD LibLoaderTracingEnabled : 1;
		/*0x240*/ DWORD SpareTracingBits : 29;
	};
	/*0x248*/ DWORD64 CsrServerReadOnlySharedMemoryBase;
} PEB, *PPEB;

typedef struct _TEB {
	/*0x000*/ NT_TIB NtTib;
	/*0x01c*/ PVOID EnvironmentPointer;
	/*0x020*/ CLIENT_ID ClientId;
	/*0x028*/ PVOID ActiveRpcHandle;
	/*0x02c*/ PVOID ThreadLocalStoragePointer;
	/*0x030*/ PPEB ProcessEnvironmentBlock;
	/*0x034*/ DWORD LastErrorValue;
	/*0x038*/ DWORD CountOfOwnedCriticalSections;
	/*0x03c*/ PVOID CsrClientThread;
	/*0x040*/ PVOID Win32ThreadInfo;
	/*0x044*/ DWORD User32Reserved[26];
	/*0x0ac*/ DWORD UserReserved[5];
	/*0x0c0*/ PVOID WOW32Reserved;
	/*0x0c4*/ DWORD CurrentLocale;
	/*0x0c8*/ DWORD FpSoftwareStatusRegister;
	/*0x0cc*/ PVOID SystemReserved1[54];
	/*0x1a4*/ LONG ExceptionCode;
	/*0x1a8*/ PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;
	/*0x1ac*/ UCHAR SpareBytes[36];
	/*0x1d0*/ DWORD TxFsContext;
	/*0x1d4*/ GDI_TEB_BATCH GdiTebBatch;
	/*0x6b4*/ CLIENT_ID RealClientId;
	/*0x6bc*/ PVOID GdiCachedProcessHandle;
	/*0x6c0*/ DWORD GdiClientPID;
	/*0x6c4*/ DWORD GdiClientTID;
	/*0x6c8*/ PVOID GdiThreadLocalInfo;
	/*0x6cc*/ DWORD Win32ClientInfo[62];
	/*0x7c4*/ PVOID glDispatchTable[233];
	/*0xb68*/ DWORD glReserved1[29];
	/*0xbdc*/ PVOID glReserved2;
	/*0xbe0*/ PVOID glSectionInfo;
	/*0xbe4*/ PVOID glSection;
	/*0xbe8*/ PVOID glTable;
	/*0xbec*/ PVOID glCurrentRC;
	/*0xbf0*/ PVOID glContext;
	/*0xbf4*/ DWORD LastStatusValue;
	/*0xbf8*/ UNICODE_STRING StaticUnicodeString;
	/*0xc00*/ WCHAR StaticUnicodeBuffer[261];
	/*0xe0c*/ PVOID DeallocationStack;
	/*0xe10*/ PVOID TlsSlots[64];
	/*0xf10*/ LIST_ENTRY TlsLinks;
	/*0xf18*/ PVOID Vdm;
	/*0xf1c*/ PVOID ReservedForNtRpc;
	/*0xf20*/ PVOID DbgSsReserved[2];
	/*0xf28*/ DWORD HardErrorMode;
	/*0xf2c*/ PVOID Instrumentation[9];
	/*0xf50*/ GUID ActivityId;
	/*0xf60*/ PVOID SubProcessTag;
	/*0xf64*/ PVOID PerflibData;
	/*0xf68*/ PVOID EtwTraceData;
	/*0xf6c*/ PVOID WinSockData;
	/*0xf70*/ DWORD GdiBatchCount;
	union {
		/*0xf74*/ PROCESSOR_NUMBER CurrentIdealProcessor;
		/*0xf74*/ DWORD IdealProcessorValue;
		struct {
			/*0xf74*/ UCHAR ReservedPad0;
			/*0xf75*/ UCHAR ReservedPad1;
			/*0xf76*/ UCHAR ReservedPad2;
			/*0xf77*/ UCHAR IdealProcessor;
		};
	};
	/*0xf78*/ DWORD GuaranteedStackBytes;
	/*0xf7c*/ PVOID ReservedForPerf;
	/*0xf80*/ PVOID ReservedForOle;
	/*0xf84*/ DWORD WaitingOnLoaderLock;
	/*0xf88*/ PVOID SavedPriorityState;
	/*0xf8c*/ DWORD ReservedForCodeCoverage;
	/*0xf90*/ PVOID ThreadPoolData;
	/*0xf94*/ PVOID *TlsExpansionSlots;
	/*0xf98*/ DWORD MuiGeneration;
	/*0xf9c*/ DWORD IsImpersonating;
	/*0xfa0*/ PVOID NlsCache;
	/*0xfa4*/ PVOID pShimData;
	/*0xfa8*/ WORD HeapVirtualAffinity;
	/*0xfaa*/ WORD LowFragHeapDataSlot;
	/*0xfac*/ PVOID CurrentTransactionHandle;
	/*0xfb0*/ PTEB_ACTIVE_FRAME ActiveFrame;
	/*0xfb4*/ PVOID FlsData;
	/*0xfb8*/ PVOID PreferredLanguages;
	/*0xfbc*/ PVOID UserPrefLanguages;
	/*0xfc0*/ PVOID MergedPrefLanguages;
	/*0xfc4*/ DWORD MuiImpersonation;
	union {
		/*0xfc8*/ WORD CrossTebFlags;
		/*0xfc8*/ WORD SpareCrossTebBits : 16;
	};
	union {
		/*0xfca*/ WORD SameTebFlags;
		struct {
			/*0xfca*/ WORD SafeThunkCall : 1;
			/*0xfca*/ WORD InDebugPrint : 1;
			/*0xfca*/ WORD HasFiberData : 1;
			/*0xfca*/ WORD SkipThreadAttach : 1;
			/*0xfca*/ WORD WerInShipAssertCode : 1;
			/*0xfca*/ WORD RanProcessInit : 1;
			/*0xfca*/ WORD ClonedThread : 1;
			/*0xfca*/ WORD SuppressDebugMsg : 1;
			/*0xfca*/ WORD DisableUserStackWalk : 1;
			/*0xfca*/ WORD RtlExceptionAttached : 1;
			/*0xfca*/ WORD InitialThread : 1;
			/*0xfca*/ WORD SessionAware : 1;
			/*0xfca*/ WORD SpareSameTebBits : 4;
		};
	};
	/*0xfcc*/ PVOID TxnScopeEnterCallback;
	/*0xfd0*/ PVOID TxnScopeExitCallback;
	/*0xfd4*/ PVOID TxnScopeContext;
	/*0xfd8*/ DWORD LockCount;
	/*0xfdc*/ DWORD SpareUlong0;
	/*0xfe0*/ PVOID ResourceRetValue;
	/*0xfe4*/ PVOID ReservedForWdf;
} TEB, *PTEB;