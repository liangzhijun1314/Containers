#pragma once
#include <iostream>
using namespace std;

class parseJson
{
public:
	parseJson() {}
	~parseJson() {}

	static void parseServerResult(std::string strJson);


	static void parse();
	static void parse_unknow_name();
	static void Serialize();


	static string readfile(const char *filename);

	//内容比对JSON

	//2.1 系统注册接口
	static void parserRegist();


};
