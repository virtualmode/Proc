// В этом файле содержатся зависимости и объявления, которые должны поддерживаться Proc по умолчанию.
// После сборки первой версии данный файл должен быть исключён из исходных кодов компилятора.

#pragma once

#ifndef DEPENDENCY_H
#define DEPENDENCY_H

/*
	The operating system, must be one of: (PROC_OS_...)

		DARWIN   - Darwin OS (synonym for PROC_OS_MAC)
		SYMBIAN  - Symbian
		MSDOS    - MS-DOS and Windows
		OS2      - OS/2
		OS2EMX   - XFree86 on OS/2 (not PM)
		WIN32    - Win32 (Windows 2000/XP/Vista/7 and Windows Server 2003/2008)
		WINCE    - WinCE (Windows CE 5.0)
		CYGWIN   - Cygwin
		SOLARIS  - Sun Solaris
		HPUX     - HP-UX
		ULTRIX   - DEC Ultrix
		LINUX    - Linux
		NACL     - Native Client
		FREEBSD  - FreeBSD
		NETBSD   - NetBSD
		OPENBSD  - OpenBSD
		BSDI     - BSD/OS
		IRIX     - SGI Irix
		OSF      - HP Tru64 UNIX
		SCO      - SCO OpenServer 5
		UNIXWARE - UnixWare 7, Open UNIX 8
		AIX      - AIX
		HURD     - GNU Hurd
		DGUX     - DG/UX
		RELIANT  - Reliant UNIX
		DYNIX    - DYNIX/ptx
		QNX      - QNX
		LYNX     - LynxOS
		BSD4     - Any BSD 4.4 system
		UNIX     - Any UNIX BSD/SYSV system
*/

#if defined(MSDOS) || defined(_MSDOS) // MS-DOS:
#define PROC_OS_MSDOS

#elif defined(__MWERKS__) && defined(__INTEL__) // Windows x86:
#define PROC_OS_WIN
#define PROC_OS_32

#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) // Windows family:
#define PROC_OS_WIN

// Pointer size of Windows:
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__) // _WIN32 and _WIN64 macroses.
#define PROC_OS_64
#else
#define PROC_OS_32
#endif

#elif defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__)) // Mac OS (Darwin OS):
#define PROC_OS_DARWIN
#define PROC_OS_MAC // PROC_OS_MAC is mostly for compatibility, but also more clear.
#define PROC_OS_BSD4
#ifdef __LP64__
#define PROC_OS_DARWIN64
#define PROC_OS_MAC64
#else
#define PROC_OS_DARWIN32
#define PROC_OS_MAC32
#endif

#elif defined(__SYMBIAN32__) || defined(SYMBIAN) // Symbian:
#define PROC_OS_SYMBIAN

#elif defined(__CYGWIN__) // Cygwin:
#define PROC_OS_CYGWIN

#elif defined(__OS2__) // OS/2:
#if defined(__EMX__)
#define PROC_OS_OS2EMX // XFree86 on OS/2 (not PM).
#else
#define PROC_OS_OS2
#endif

#elif defined(__sun) || defined(sun) // Sun Solaris:
#define PROC_OS_SOLARIS

#elif defined(hpux) || defined(__hpux) // HP-UX:
#define PROC_OS_HPUX

#elif defined(__ultrix) || defined(ultrix) // DEC Ultrix:
#define PROC_OS_ULTRIX

#elif defined(sinix) // Reliant UNIX:
#define PROC_OS_RELIANT

#elif defined(__native_client__) // Native Client:
#define PROC_OS_NACL

#elif defined(__linux__) || defined(__linux) // Linux:
#define PROC_OS_LINUX

#elif defined(__FreeBSD__) || defined(__DragonFly__) // FreeBSD:
#define PROC_OS_FREEBSD
#define PROC_OS_BSD4

#elif defined(__NetBSD__) // NetBSD:
#define PROC_OS_NETBSD
#define PROC_OS_BSD4

#elif defined(__OpenBSD__) // OpenBSD:
#define PROC_OS_OPENBSD
#define PROC_OS_BSD4

#elif defined(__bsdi__) // BSD/OS:
#define PROC_OS_BSDI
#define PROC_OS_BSD4

#elif defined(__sgi) // SGI Irix:
#define PROC_OS_IRIX

#elif defined(__osf__) // HP Tru64 UNIX:
#define PROC_OS_OSF

#elif defined(_AIX) // AIX:
#define PROC_OS_AIX

#elif defined(__Lynx__) // LynxOS:
#define PROC_OS_LYNX

#elif defined(__GNU__) // GNU Hurd:
#define PROC_OS_HURD

#elif defined(__DGUX__) // DG/UX:
#define PROC_OS_DGUX

#elif defined(__QNXNTO__) // QNX:
#define PROC_OS_QNX

#elif defined(_SEQUENT_) // DYNIX/ptx:
#define PROC_OS_DYNIX

#elif defined(_SCO_DS) // SCO OpenServer 5 + GCC:
#define PROC_OS_SCO

#elif defined(__USLC__) // All SCO platforms + UDK or OUDK:
#define PROC_OS_UNIXWARE

#elif defined(__svr4__) && defined(i386) // Open UNIX 8 + GCC:
#define PROC_OS_UNIXWARE

#elif defined(__INTEGRITY) // INTEGRITY:
#define PROC_OS_INTEGRITY

#elif defined(VXWORKS) // There is no "real" VxWorks define - this has to be set in the mkspec:
#define PROC_OS_VXWORKS

#elif defined(__MAKEDEPEND__)

#else // Unsupported operating system:
#error "Proc-0 has not been ported to this operating system."
#endif

// UNIX operating system:
#if !(defined(PROC_OS_MSDOS) || defined(PROC_OS_OS2) || defined(PROC_OS_WIN))
#define PROC_OS_UNIX
#endif

/*
	The compiler, must be one of: (PROC_CC_...)

		SYM      - Digital Mars C/C++ (used to be Symantec C++)
		MWERKS   - Metrowerks CodeWarrior
		MSVC     - Microsoft Visual C/C++, Intel C++ for Windows
		BOR      - Borland/Turbo C++
		WAT      - Watcom C++
		GNU      - GNU C++
		MINGW    - MinGW
		COMEAU   - Comeau C++
		EDG      - Edison Design Group C++
		OC       - CenterLine C++
		SUN      - Forte Developer, or Sun Studio C++
		MIPS     - MIPSpro C++
		DEC      - DEC C++
		HPACC    - HP aC++
		USLC     - SCO OUDK and UDK
		CDS      - Reliant C++
		KAI      - KAI C++
		INTEL    - Intel C++ for Linux, Intel C++ for Windows
		HIGHC    - MetaWare High C/C++
		PGI      - Portland Group C++
		GHS      - Green Hills Optimizing C++ Compilers
		GCCE     - GCCE (Symbian GCCE builds)
		RVCT     - ARM Realview Compiler Suite
		NOKIAX86 - Nokia x86 (Symbian WINSCW builds)
		CLANG    - C++ front-end for the LLVM compiler
*/

#if defined(__DMC__) || defined(__SC__) // Symantec C++ is now Digital Mars:
#define PROC_CC_SYM

#elif defined(__CUDACC__) // NVCC CUDA compiler.
#define PROC_CC_NVCC
#define PROC_CC_CUDA

#elif defined(__MWERKS__) // Metrowerks CodeWarrior:
#define PROC_CC_MWERKS
#if defined(__EMU_SYMBIAN_OS__) // Nokia x86:
#define PROC_CC_NOKIAX86
#endif

#elif defined(_MSC_VER) // Microsoft Visual C/C++, Intel C++ for Windows:
#define PROC_CC_MSVC
#if defined(__INTEL_COMPILER) // Intel C++ disguising as Visual C++:
#define PROC_CC_INTEL
#endif

#elif defined(__BORLANDC__) || defined(__TURBOC__) // Borland/Turbo C++:
#define PROC_CC_BOR

#elif defined(__WATCOMC__) // Watcom C++:
#define PROC_CC_WAT

#elif defined(__GCCE__) // Symbian GCCE:
#define PROC_CC_GCCE

#elif defined(__ARMCC__) || defined(__CC_ARM) // ARM Realview Compiler Suite:
#define PROC_CC_RVCT

#elif defined(__GNUC__) // GNU C++:
#define PROC_CC_GNU
#if defined(__MINGW32__) // MinGW:
#define PROC_CC_MINGW
#endif
#if defined(__INTEL_COMPILER) // Intel C++ also masquerades as GCC 3.2.0:
#define PROC_CC_INTEL
#endif
#if defined(__clang__) // Clang also masquerades as GCC 4.2.1:
#define PROC_CC_CLANG
#endif

#elif defined(__xlC__) // IBM C compilers. Version of the C compiler in hexadecimal notation (is only an approximation of the C++ compiler version):
#define PROC_CC_XLC

#elif defined(__DECCXX) || defined(__DECC) // DEC C++:
#define PROC_CC_DEC

#if defined(__EDG__) // Edison Design Group C++:
#define PROC_CC_EDG
#endif

#elif defined(__PGI) // Portland Group C++:
#define PROC_CC_PGI
#if defined(__EDG__)
#define PROC_CC_EDG
#endif

#elif !defined(PROC_OS_HPUX) && (defined(__EDG) || defined(__EDG__)) // Compilers with EDG front end:
#define PROC_CC_EDG
#if defined(__COMO__) // Comeau C++:
#define PROC_CC_COMEAU
#elif defined(__KCC) // KAI C++:
#define PROC_CC_KAI
#elif defined(__INTEL_COMPILER) // Intel C++ for Linux, Intel C++ for Windows:
#define PROC_CC_INTEL
#elif defined(__ghs) // Green Hills Optimizing C++ Compilers:
#define PROC_CC_GHS
#elif defined(__DCC__)
#define PROC_CC_DIAB
#elif defined(__USLC__) && defined(__SCO_VERSION__) // UnixWare 7 UDK compiler:
#define PROC_CC_USLC
#elif defined(CENTERLINE_CLPP) || defined(OBJECTCENTER) // CenterLine C++ (never tested):
#define PROC_CC_OC
#elif defined(sinix) // CDS++:
#define PROC_CC_CDS
#elif defined(__sgi) // MIPSpro C++:
#define PROC_CC_MIPS
#endif

#elif defined(_DIAB_TOOL) // VxWorks DIAB toolchain:
#define PROC_CC_DIAB

#elif defined(__HIGHC__) // MetaWare High C/C++ (never tested):
#define PROC_CC_HIGHC

#elif defined(__SUNPRO_CC) || defined(__SUNPRO_C) // Forte Developer and Sun Studio C++:
#define PROC_CC_SUN

#elif defined(sinix) // Reliant C++ and EDG:
#define PROC_CC_EDG
#define PROC_CC_CDS

#elif defined(PROC_OS_HPUX) // HP aC++:
#if defined(__HP_aCC) || __cplusplus >= 199707L
#define PROC_CC_HPACC
#else
#define PROC_CC_HP
#endif

#elif defined(__WINSCW__) && !defined(PROC_CC_NOKIAX86) // Nokia x86:
#define PROC_CC_NOKIAX86

#else // Unsupported compiler:
#error "Proc-0 has not been tested with this compiler."
#endif

// Proc-0 configuration header:
#include "Config.h"

/********************************

	CUDA NVCC definitions.

********************************/

#if defined(PROC_CC_NVCC) // For NVCC (CUDA) compiler:
#include <stdio.h> // Standard IO interface.
#include <cuda.h> // cuFunctions interface.
#include <cuda_runtime_api.h> // cudaFunctions interface.
#else // For another compilers:

/********************************

	C/C++ standard definitions.

********************************/

#include <stddef.h> // size_t, ptrdiff_t.
#include <stdint.h>
#include <iostream> // iostream.
#include <fstream> // iostream.
#include <sstream>
#include <iomanip> // setprecision.
#include <string> // string.
#include <list>
#include <time.h> // time().
#include <map>
#include <queue>

// C/C++ standard:
//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <vector>
//#include <memory.h>
//#include <stdexcept>
//#include <sstream>

/********************************

	Windows family.

********************************/

#if defined(PROC_OS_WIN)
#define atoll _atoi64 // TODO: Old definition after http server porting.
#define VC_EXTRALEAN // Reduce the size of the Win32 header files by excluding some of the less common APIs.
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers. Useless in current conditions.
#define NOCOMM // Excludes the serial communication API. For a list of support NOapi symbols, see Windows.h.
#include <windows.h> // Threads and other system functional.
#include <winsock2.h> // Network.
#include <ws2tcpip.h>
#include <shellapi.h> // Tray ShellExecute.
// Non-ANSI names for low-level i/o flags compatibility:
#include <fcntl.h> // O_BINARY, etc.
#include <sys/stat.h> // _S_IREAD, _S_IWRITE, sys/types.h.
#include <direct.h> // mkdir.
// File iterator implementation:
#include <io.h> // _access_s, _finddata_t.

// WINVER:
// Windows 8.1											_WIN32_WINNT_WINBLUE (0x0602)
// Windows 8											_WIN32_WINNT_WIN8 (0x0602)
// Windows 7											_WIN32_WINNT_WIN7 (0x0601)
// Windows Server 2008									_WIN32_WINNT_WS08 (0x0600)
// Windows Vista										_WIN32_WINNT_VISTA (0x0600)
// Windows Server 2003 with SP1, Windows XP with SP2	_WIN32_WINNT_WS03 (0x0502)
// Windows Server 2003, Windows XP						_WIN32_WINNT_WINXP (0x0501)

// NTDDI_VERSION:
// Windows 8.1											NTDDI_WINBLUE (0x06030000)
// Windows 8											NTDDI_WIN8 (0x06020000)
// Windows 7											NTDDI_WIN7 (0x06010000)
// Windows Server 2008									NTDDI_WS08 (0x06000100)
// Windows Vista with Service Pack 1 (SP1)				NTDDI_VISTASP1 (0x06000100)
// Windows Vista										NTDDI_VISTA (0x06000000)
// Windows Server 2003 with Service Pack 2 (SP2)		NTDDI_WS03SP2 (0x05020200)
// Windows Server 2003 with Service Pack 1 (SP1)		NTDDI_WS03SP1 (0x05020100)
// Windows Server 2003									NTDDI_WS03 (0x05020000)
// Windows XP with Service Pack 3 (SP3)					NTDDI_WINXPSP3 (0x05010300)
// Windows XP with Service Pack 2 (SP2)					NTDDI_WINXPSP2 (0x05010200)
// Windows XP with Service Pack 1 (SP1)					NTDDI_WINXPSP1 (0x05010100)
// Windows XP											NTDDI_WINXP (0x05010000)

// Windows CE family:
#if defined(WINCE) || defined(_WIN32_WCE)
#define PROC_OS_WINCE

// Windows NT family:
#elif (defined(WINVER) && WINVER >= _WIN32_WINNT_WINXP) || (defined(NTDDI_VERSION) && NTDDI_VERSION >= NTDDI_WINXP)
#define PROC_OS_WINXP

#if (defined(WINVER) && WINVER >= _WIN32_WINNT_VISTA) || (defined(NTDDI_VERSION) && NTDDI_VERSION >= NTDDI_VISTA)
#define PROC_OS_VISTA
#endif
#endif // Windows family end.


/********************************

	UNIX family.

********************************/

#elif defined(PROC_OS_UNIX)
#include <pthread.h> // Threads.
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


/********************************

	Third party crossplatform components.

********************************/

//#include "utf8_decode.h" // Simple UTF-8 parser.

#endif // PROC_CC_NVCC


// Переменная, указывающая на объект и основание должны быть размерности указателя для архитектуры,
// или безразмерного (целого). Указатель очень для этого подходит. IntPtr, IntObj, pointer, object, base.
// Базовый "безразмерный" тип для всех объектов, чисел, структур, enum'ов и прочей фигни.
// Этот тип будет реализовывать простейшие операции над любым объектом, скорее всего
// просто адресация и счёт. В данном языке это может быть основание - количество состояний информации.
//#define object char*
#define object ptrdiff_t

#define bool int
#define false 0
#define true 1

// Unsigned integer types:
typedef unsigned char u8; //!< 1 byte from 0 to 255 (char, bool).
typedef unsigned short u16; //!< 2 bytes from 0 to 65,535 (short).
typedef unsigned int u32; //!< 4 bytes from 0 to 4,294,967,295 (int, long).
typedef unsigned long long u64; //!< 8 bytes from 0 to 18,446,744,073,709,551,615 (long long).
//typedef u64 ul; //!< Largest supported unsigned type.

// Signed integer types:
typedef signed char s8; //!< 1 bytes from –128 to 127.
typedef signed short s16; //!< 2 bytes from –32,768 to 32,767.
typedef signed int s32; //!< 4 bytes from –2,147,483,648 to 2,147,483,647.
typedef signed long long s64; //!< 8 bytes from –9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
//typedef s64 sl; //!< Largest supported signed type.

// Floating point types:
typedef float f32;
typedef double f64;
typedef long double f80; // Rare.

union type {
	bool type::bool_t;
	u8 type::u8;
	u16 type::u16;
	u32 type::u32;
	u64 type::u64;
	s8 type::s8;
	s16 type::s16;
	s32 type::s32;
	s64 type::s64;
	f32 type::f32;
	f64 type::f64;
	f80 type::f80;
	::size_t type::size_t;
	::ptrdiff_t type::ptrdiff_t;
};

#endif // DEPENDENCY_H
