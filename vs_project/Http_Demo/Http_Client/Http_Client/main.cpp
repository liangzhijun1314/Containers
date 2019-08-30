#include <iostream>
#include "Http_Client.h"

using namespace std;


static const char *url = "http://www.google.com";

void handle_func(std::string rsp)
{
	// do sth according to rsp

	std::cout << "http rsp1: " << rsp << std::endl;
}

int main(void) {

	// 拼完整url，带参数
	bool isPost = true;
	//std::string url1 = "http://127.0.0.1:7999/api/fun1";
	//HttpClient::SendReq(url1, handle_func);

	//std::string url2 = "http://127.0.0.1:7999/api/fun2";
	//HttpClient::SendReq(url2, handle_func);

	//HttpClient::SendReq(url2, [](std::string rsp) {
	//	std::cout << "http rsp2: " << rsp << std::endl;
	//});

	//std::string url3 = "http://127.0.0.1:7999/api/sum";
	//HttpClient::SendReq(url3, handle_func);

	std::string registUrl = "http://127.0.0.1:7999/api/registration";
	HttpClient::SendReq(registUrl, handle_func, isPost);

	//std::string hearUrl = "http://127.0.0.1:7999/api/heartbeat";
	//HttpClient::SendReq(hearUrl, handle_func, isPost);


	system("pause");

	return 0;
}