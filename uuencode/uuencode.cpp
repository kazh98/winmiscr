#include <cstdio>
#include <cstdlib>
#include <cwchar>


static const wchar_t ttable[] = L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";


int wmain(int argc, wchar_t *argv[], wchar_t* envp[])
{
    wprintf(L"Hello World!\n");

	return EXIT_SUCCESS;
}
