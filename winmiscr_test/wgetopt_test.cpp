#include "pch.h"
#include "CppUnitTest.h"
#include "../winmiscr/winmiscr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace winmiscr;


namespace winmiscr_test
{

	TEST_CLASS(wgetopt_test)
	{
	public:
		
		TEST_METHOD(initial_state)
		{
			Assert::AreEqual<size_t>(1, optind);
			Assert::IsTrue(opterr);
		}

		TEST_METHOD(no_options)
		{
			wchar_t* argv[] = {L"a.out", L"foo", L"bar"};

			Assert::IsTrue(WEOF == wgetopt(2, argv, L"abcd:"));
			Assert::AreEqual<size_t>(1, optind);
			Assert::AreEqual(L"foo", argv[1]);
			Assert::AreEqual(L"bar", argv[2]);
		}

		TEST_METHOD(simple)
		{
			wchar_t* argv[] = { L"a.out", L"-a", L"foo", L"bar" };
			bool flag_a = false;
			wint_t ch;

			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsTrue(flag_a);
			Assert::AreEqual<size_t>(2, optind);
			Assert::AreEqual(L"foo", argv[2]);
			Assert::AreEqual(L"bar", argv[3]);
		}

		TEST_METHOD(simple_reversed)
		{
			wchar_t* argv[] = { L"a.out", L"foo", L"bar", L"-a" };
			bool flag_a = false;
			wint_t ch;

			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsTrue(flag_a);
			Assert::AreEqual<size_t>(2, optind);
			Assert::AreEqual(L"foo", argv[2]);
			Assert::AreEqual(L"bar", argv[3]);
		}

		TEST_METHOD(with_parameter)
		{
			wchar_t* argv[] = { L"a.out", L"-carg1", L"-d", L"arg2", L"foo", L"bar" };
			wchar_t* opt_c = nullptr;
			wchar_t* opt_d = nullptr;
			wint_t ch;

			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				switch (ch) {
				case L'c':
					opt_c = optarg;
					break;
				case L'd':
					opt_d = optarg;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::AreEqual(L"arg1", opt_c);
			Assert::AreEqual(L"arg2", opt_c);
			Assert::AreEqual<size_t>(4, optind);
			Assert::AreEqual(L"foo", argv[4]);
			Assert::AreEqual(L"bar", argv[5]);
		}

		TEST_METHOD(with_parameter_reversed)
		{
			wchar_t* argv[] = { L"a.out", L"foo", L"bar", L"-carg1", L"-d", L"arg2" };
			wchar_t* opt_c = nullptr;
			wchar_t* opt_d = nullptr;
			wint_t ch;

			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				switch (ch) {
				case L'c':
					opt_c = optarg;
					break;
				case L'd':
					opt_d = optarg;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::AreEqual(L"arg1", opt_c);
			Assert::AreEqual(L"arg2", opt_c);
			Assert::AreEqual<size_t>(4, optind);
			Assert::AreEqual(L"foo", argv[4]);
			Assert::AreEqual(L"bar", argv[5]);
		}
	};

}
