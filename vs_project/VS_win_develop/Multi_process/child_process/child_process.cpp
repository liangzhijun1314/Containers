// child_process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main(int argc, char *argv[])
{

	std::cout << "args_num: " << argc << std::endl;

	for (int i = 0; i < argc; i++) {

		std::cout << "arg " << i << " = " << argv[i] << std::endl;

	}
	Sleep(2000);
    return 0;
}

