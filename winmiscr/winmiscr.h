#ifndef WINMISCR_H
#define WINMISCR_H

#include <cwchar>


namespace winmiscr {

	extern wchar_t* optarg;
	extern size_t optind;
	extern bool opterr;
	extern int optopt;
	wint_t wgetopt(int, wchar_t*[], wchar_t*);

}

#endif //WINMISCR_H
