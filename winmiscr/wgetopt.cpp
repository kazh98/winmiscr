#include "pch.h"
#include "winmiscr.h"

static const wint_t WITH_ARGUMENT = L':';
static const wint_t RVAL_UNKNOWN = L'?';
static const wint_t RVAL_END = WEOF;


namespace winmiscr {

	wchar_t* optarg;
	size_t optind;
	wint_t optopt;
	bool opterr = true;
	bool optreset = true;

	static size_t target;
	static wchar_t* p;


	wint_t wgetopt(int argc, wchar_t** argv, const wchar_t* options)
	{
		const wchar_t* option;

		if (optreset) {
			optreset = false;
			optind = 1;
			target = 1;
			p = nullptr;
		}

		if (p == nullptr) {
			for (; target < argc; ++target) {
				p = argv[target];
				if (*p++ == L'-' && *p != L'\0') {
					break;
				}
			}
			if (target >= argc) {
				return RVAL_END;
			}
		}

		optopt = *p++;
		if (optopt == WITH_ARGUMENT) {
			if (*p == L'\0') {
				for (size_t i = target; i > optind; --i) {
					wchar_t* const tmp = argv[i];
					argv[i] = argv[i - 1];
					argv[i - 1] = tmp;
				}
				++optind;
				p = nullptr;
				++target;
			}
			return RVAL_UNKNOWN;
		}
	
		option = wcschr(options, optopt);
		if (option == NULL) {
			if (*p == L'\0') {
				for (size_t i = target; i > optind; --i) {
					wchar_t* const tmp = argv[i];
					argv[i] = argv[i - 1];
					argv[i - 1] = tmp;
				}
				++optind;
				p = nullptr;
				++target;
			}
			return RVAL_UNKNOWN;
		}

		if (option[1] == WITH_ARGUMENT) {
			if (*p == L'\0') {
				if (target + 1 >= argc) {
					return RVAL_END;
				}
				for (size_t i = target; i > optind; --i) {
					wchar_t* const tmp = argv[i];
					argv[i] = argv[i - 1];
					argv[i - 1] = tmp;
				}
				++optind;
				++target;
				optarg = argv[target];
				for (size_t i = target; i > optind; --i) {
					wchar_t* const tmp = argv[i];
					argv[i] = argv[i - 1];
					argv[i - 1] = tmp;
				}
				++optind;
				++target;
				p = nullptr;
			}
			else {
				optarg = p;
				for (size_t i = target; i > optind; --i) {
					wchar_t* const tmp = argv[i];
					argv[i] = argv[i - 1];
					argv[i - 1] = tmp;
				}
				++optind;
				++target;
				p = nullptr;
			}
		}
		else {
			if (*p == L'\0') {
				for (size_t i = target; i > optind; --i) {
					wchar_t* const tmp = argv[i];
					argv[i] = argv[i - 1];
					argv[i - 1] = tmp;
				}
				++optind;
				++target;
				p = nullptr;
			}
		}

		return optopt;
	}

}
