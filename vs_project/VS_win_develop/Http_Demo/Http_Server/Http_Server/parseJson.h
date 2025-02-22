#pragma once
#include <iostream>
using namespace std;

class parseJson
{
public:
	parseJson() {}
	~parseJson() {}

	static void parse(); // 遍历 用于知道name的情况
	static void parse_unknow_name(std::string data);  // 遍历 用于不知道name的前提下
	static void writeJson();  // 写json

	// 读取文件中的json数据
	static std::string readfile(std::string & fileName);

	//内容比对JSON 解析

	// 2.1 系统注册接口 解析与组装
	static void parserRegist(std::string data);
	static std::string writeRegist();

	// 2.2 心跳接口
	static void parserHeart(std::string data);
	static std::string writeHeart();

	// 2.6 节点状态上报
	static void parseNodeStatusReport(std::string data);
	static std::string writeNodeStatusReport();

	// 2.7 信号检测辅助数据
	static void parseSingleCheck(std::string data);
	static std::string writeSingleCheck();

	// 2.8 板卡信号提取任务下发
	static void parseCarSendTask(std::string data);
	static std::string writeCarSendTask();

	// 2.9 板卡信号提取任务停止
	static void parseCarStopTask(std::string data);
	static std::string writeCarStopTask();

private:
	// 获取当前时间
	static std::string getTime();
	
	
};
