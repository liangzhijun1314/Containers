#include <iostream>
#include <memory>
#include "http_server.h"
#include "parseJson.h"

// 初始化HttpServer静态类成员
mg_serve_http_opts HttpServer::s_server_option;
std::string HttpServer::s_web_dir = "./web";
std::unordered_map<std::string, ReqHandler> HttpServer::s_handler_map;
std::unordered_set<mg_connection *> HttpServer::s_websocket_session_set;

bool handle_fun1(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	// do sth
	std::cout << "handle fun1" << std::endl;
	std::cout << "url: " << url << std::endl;
	std::cout << "body: " << body << std::endl;



	rsp_callback(c, "hello 1");

	return true;
}

bool handle_fun2(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	// do sth
	std::cout << "handle fun2" << std::endl;
	std::cout << "url: " << url << std::endl;
	std::cout << "body: " << body << std::endl;

	rsp_callback(c, body);

	return true;
}

// 系统注册接口 返回
bool handle_registration(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	//test 
	std::string res = "{\"code\":\"1\",\"desc\":\"\",\"result\":{\"pk\":\"21312313\"}}";

	printf("### body: %s\n", body.c_str());
	rsp_callback(c, res);
	return true;
}

// 心跳 返回
bool handle_heartbeat(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	//test 
	std::string res = "{\"code\":\"1\",\"desc\":\"\"}";

	rsp_callback(c, res);
	return true;
}

// 节点状态上报 返回
bool handle_reporting(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	//test 
	std::string res = "{\"code\":\"1\",\"desc\":\"\"}";

	rsp_callback(c, res);
	return true;
}

// 信号检测辅助数据 返回
bool handle_signal_detail(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	//test 
	std::string res = "{\"code\":\"1\",\"result\":{\"pk\":123456,\"dynamic_range\":1\"colour_range\":1\"depth\":8}}";

	rsp_callback(c, res);
	return true;
}

// 板卡信号提取任务下发/停止 返回
bool handle_singal_monitor(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	//test 
	std::string res = "{\"code\":\"1\",\"desc\":\"\"}";

	rsp_callback(c, res);
	return true;
}

void addALLTask() {

}

int main(int argc, char *argv[])
{
	std::string data = "{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}";
	parseJson::parse_unknow_name(data);
	parseJson::parse();
	parseJson::writeJson();

	data = parseJson::writeRegist();
	parseJson::parserRegist(data);

	data = parseJson::writeHeart();
	parseJson::parserHeart(data);

	data = parseJson::writeNodeStatusReport();
	parseJson::parseNodeStatusReport(data);

	data = parseJson::writeSingleCheck();
	parseJson::parseSingleCheck(data);

	data = parseJson::writeCarSendTask();
	parseJson::parseCarSendTask(data);


	data = parseJson::writeCarStopTask();
	parseJson::parseCarStopTask(data);

	std::string port = "127.0.0.1:7999";
	auto http_server = std::shared_ptr<HttpServer>(new HttpServer);
	http_server->Init(port);
	// add handler
	http_server->AddHandler("/api/fun1", handle_fun1);
	http_server->AddHandler("/api/fun2", handle_fun2);
	http_server->AddHandler("/api/registration", handle_registration);


	http_server->Start();


	return 0;
}