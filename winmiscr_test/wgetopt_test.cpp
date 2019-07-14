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

		TEST_METHOD(no_options)
		{
			wchar_t* argv[] = {L"a.out", L"foo", L"bar"};

			optreset = true;
			Assert::IsTrue(WEOF == wgetopt(2, argv, L"abcd:"));
			Assert::IsFalse(optreset);
			Assert::AreEqual<size_t>(1, optind);
			Assert::AreEqual(L"foo", argv[1]);
			Assert::AreEqual(L"bar", argv[2]);
		}

		TEST_METHOD(simple)
		{
			wchar_t* argv[] = { L"a.out", L"-a", L"foo", L"bar" };
			bool flag_a = false;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
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

			optreset = true;
			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_a);
			Assert::AreEqual<size_t>(2, optind);
			Assert::AreEqual(L"foo", argv[2]);
			Assert::AreEqual(L"bar", argv[3]);
		}

		TEST_METHOD(complex)
		{
			wchar_t* argv[] = { L"a.out", L"-ab", L"foo", L"bar" };
			bool flag_a = false;
			bool flag_b = false;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				case L'b':
					flag_b = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_a);
			Assert::IsTrue(flag_b);
			Assert::AreEqual<size_t>(2, optind);
			Assert::AreEqual(L"foo", argv[2]);
			Assert::AreEqual(L"bar", argv[3]);
		}

		TEST_METHOD(complex_reversed)
		{
			wchar_t* argv[] = { L"a.out", L"foo", L"bar", L"-ab" };
			bool flag_a = false;
			bool flag_b = false;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				case L'b':
					flag_b = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_a);
			Assert::IsTrue(flag_b);
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

			optreset = true;
			while ((ch = wgetopt(6, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
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
			Assert::IsFalse(optreset);
			Assert::AreEqual(L"arg1", opt_c);
			Assert::AreEqual(L"arg2", opt_d);
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

			optreset = true;
			while ((ch = wgetopt(6, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
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
			Assert::IsFalse(optreset);
			Assert::AreEqual(L"arg1", opt_c);
			Assert::AreEqual(L"arg2", opt_d);
			Assert::AreEqual<size_t>(4, optind);
			Assert::AreEqual(L"foo", argv[4]);
			Assert::AreEqual(L"bar", argv[5]);
		}

		TEST_METHOD(complex_with_parameter)
		{
			wchar_t* argv[] = { L"a.out", L"-acarg1", L"-bd", L"arg2", L"foo", L"bar" };
			bool flag_a = false;
			bool flag_b = false;
			wchar_t* opt_c = nullptr;
			wchar_t* opt_d = nullptr;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(6, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				case L'b':
					flag_b = true;
					break;
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
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_a);
			Assert::IsTrue(flag_b);
			Assert::AreEqual(L"arg1", opt_c);
			Assert::AreEqual(L"arg2", opt_d);
			Assert::AreEqual<size_t>(4, optind);
			Assert::AreEqual(L"foo", argv[4]);
			Assert::AreEqual(L"bar", argv[5]);
		}

		TEST_METHOD(complex_with_parameter_reversed)
		{
			wchar_t* argv[] = { L"a.out", L"foo", L"bar", L"-acarg1", L"-bd", L"arg2" };
			bool flag_a = false;
			bool flag_b = false;
			wchar_t* opt_c = nullptr;
			wchar_t* opt_d = nullptr;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(6, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				case L'b':
					flag_b = true;
					break;
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
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_a);
			Assert::IsTrue(flag_b);
			Assert::AreEqual(L"arg1", opt_c);
			Assert::AreEqual(L"arg2", opt_d);
			Assert::AreEqual<size_t>(4, optind);
			Assert::AreEqual(L"foo", argv[4]);
			Assert::AreEqual(L"bar", argv[5]);
		}

		TEST_METHOD(unknown)
		{
			wchar_t* argv[] = { L"a.out", L"-e", L"foo", L"bar" };
			bool flag_unknown = false;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'?':
					flag_unknown = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_unknown);
			Assert::AreEqual<size_t>(2, optind);
			Assert::AreEqual(L"foo", argv[2]);
			Assert::AreEqual(L"bar", argv[3]);
		}

		TEST_METHOD(unknown_reversed)
		{
			wchar_t* argv[] = { L"a.out", L"foo", L"bar", L"-e" };
			bool flag_unknown = false;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(4, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'?':
					flag_unknown = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_unknown);
			Assert::AreEqual<size_t>(2, optind);
			Assert::AreEqual(L"foo", argv[2]);
			Assert::AreEqual(L"bar", argv[3]);
		}

		TEST_METHOD(solitary_hyphen)
		{
			wchar_t* argv[] = { L"a.out", L"-" };

			optreset = true;
			Assert::IsTrue(WEOF == wgetopt(2, argv, L"abcd:"));
			Assert::IsFalse(optreset);
			Assert::AreEqual<size_t>(1, optind);
			Assert::AreEqual(L"-", argv[1]);
		}

		TEST_METHOD(colon_as_option)
		{
			wchar_t* argv[] = { L"a.out", L"-:a" };
			bool flag_a = false;
			bool flag_unknown = false;
			wint_t ch;

			optreset = true;
			while ((ch = wgetopt(2, argv, L"abc:d:")) != WEOF) {
				Assert::IsFalse(optreset);
				switch (ch) {
				case L'a':
					flag_a = true;
					break;
				case L'?':
					flag_unknown = true;
					break;
				default:
					Assert::Fail();
				}
			}
			Assert::IsFalse(optreset);
			Assert::IsTrue(flag_a);
			Assert::IsTrue(flag_unknown);
			Assert::AreEqual<size_t>(2, optind);
		}

	};

}
