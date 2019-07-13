#include "pch.h"
#include "winmiscr.h"

static const wint_t RVAL_ERROR = L'?';


namespace winmiscr {

	wchar_t* optarg;
	size_t optind = 1;
	bool opterr = true;
	int optopt;

	wint_t wgetopt(int argc, wchar_t* argv[], wchar_t* options)
	{

		return WEOF;
	}

}
