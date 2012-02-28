#ifndef SBOL_CORE_API
#define SBOL_CORE_API

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#	if defined(STATIC_LINKED)
#		define SBOLAPIEXPORTS
#	else
#		if defined(SBOL_EXPORTS)
#			if defined(USE_STDCALL)
#				define SBOLAPIEXPORTS __stdcall __declspec(dllexport)
#			else
#				define SBOLAPIEXPORTS __declspec(dllexport)
#			endif
#		else
#			define SBOLAPIEXPORTS
#		endif
#	endif
#else
#	if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#		define SBOLAPIEXPORTS __attribute__ ((visibility("default")))
#	else
#		define SBOLAPIEXPORTS
#	endif
#endif

#endif
