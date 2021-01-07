/**
 *	@file	main.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include "gtest/gtest.h"

#if (_MSC_VER)
#include <crtdbg.h>
#include <iostream>

int __cdecl PrintToStdErr(int /*report_type*/, char* msg, int* /*ret_val*/)
{
	std::cerr << msg;
	return 1; // No further processing required by _CrtDebugReport
}

class MemLeakListener : public ::testing::EmptyTestEventListener
{
public:
	void OnTestStart(const ::testing::TestInfo& /*test_info*/)
	{
		_CrtMemCheckpoint(&m_mem_at_start);
	}

	void OnTestEnd(const ::testing::TestInfo& test_info)
	{
		if (test_info.result()->Passed())
		{
			CheckForMemLeaks(test_info);
		}
	}

	void OnTestProgramStart(const ::testing::UnitTest& /*unit_test*/)
	{
		_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, &PrintToStdErr);
	}

	void OnTestProgramEnd(const ::testing::UnitTest& /*unit_test*/)
	{
		_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE, &PrintToStdErr);
	}

private:
	void CheckForMemLeaks(const ::testing::TestInfo& test_info)
	{
		_CrtMemState mem_at_end;
		_CrtMemCheckpoint(&mem_at_end);
		_CrtMemState mem_diff;
		if (_CrtMemDifference(&mem_diff, &m_mem_at_start, &mem_at_end))
		{
			_CrtMemDumpStatistics(&mem_diff);
			FAIL() << "Memory leak in " << test_info.test_case_name() << "." << test_info.name() << '\n';
		}
		(void)mem_at_end;
		(void)mem_diff;
	}

private:
	_CrtMemState m_mem_at_start;
};
#endif

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

#if (_MSC_VER)
	auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new MemLeakListener());

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	return RUN_ALL_TESTS();
}
