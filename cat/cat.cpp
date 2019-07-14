#include "pch.h"
#include "../winmiscr/winmiscr.h"
using namespace winmiscr;

static bool flag_d = false;
static bool flag_n = false;
static bool binary_mode = true;

static int errorlevel = EXIT_SUCCESS;
static size_t lineno = 1;

static unsigned char* buffer[BUFSIZ];


static void redirect(const wchar_t* filename)
{
	FILE* fp;

	if (wcscmp(filename, L"-") == 0) {
		fp = stdin;
	}
	else {
		errno_t eno;

		if (binary_mode) {
			eno = _wfopen_s(&fp, filename, L"rb");
		}
		else {
			eno = _wfopen_s(&fp, filename, L"rt,ccs=UTF-8");
		}
		if (eno != 0 || fp == NULL) {
			fwprintf(stderr, L"No such file: %s\n", filename);
			errorlevel = EXIT_FAILURE;
			return;
		}
	}

	if (binary_mode) {
		size_t wlen;

		do {
			wlen = fread(buffer, 1, BUFSIZ, fp);
			fwrite(buffer, 1, wlen, stdout);
		} while (wlen == BUFSIZ);
	}
	else {
		wint_t ch;

		if (flag_n && lineno == 1) {
			fwprintf(stdout, L"%6zu\t", lineno++);
		}
		while ((ch = fgetwc(fp)) != WEOF) {
			fputwc(ch, stdout);
			if (flag_n && ch == '\n') {
				fwprintf(stdout, L"%6zu\t", lineno++);
			}
		}
	}

	if (fp != stdin) {
		fclose(fp);
	}
}


int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	wint_t ch;

	setlocale(LC_ALL, "");
	
	while ((ch = wgetopt(argc, argv, L"dhn")) != WEOF) {
		switch (ch) {
		case L'd':
			flag_d = true;
			break;
		case L'n':
			flag_n = true;
			break;
		default:
			fwprintf(stderr, L"usage: %s [-dhn] [file ...]", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	binary_mode = !(flag_d || flag_n);

	if (optind < argc) {
		for (int i = optind; i < argc; ++i) {
			redirect(argv[i]);
		}
	}
	else {
		redirect(L"-");
	}

	return errorlevel;
}
