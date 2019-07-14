#ifndef WINMISCR_H
#define WINMISCR_H

#include <cwchar>


namespace winmiscr {

	extern wchar_t* optarg;
	extern size_t optind;
	extern wint_t optopt;
	extern bool opterr;
	extern bool optreset;
	wint_t wgetopt(int, wchar_t**, const wchar_t*);

}

#endif //WINMISCR_H
