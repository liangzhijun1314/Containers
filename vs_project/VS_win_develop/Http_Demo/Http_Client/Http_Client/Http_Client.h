#pragma once
#include <string>
#include <functional>
#include "mongoose.h"

// 此处必须用function类，typedef再后面函数指针赋值无效
using ReqCallback = std::function<void(std::string)>;

class HttpClient
{
public:
	HttpClient() {}
	~HttpClient() {}

	static void SendReq(const std::string &url, ReqCallback req_callback, bool isPost=false);
	static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);
	static int s_exit_flag;
	static int s_show_headers;
	static const char *s_show_headers_opt;
	static ReqCallback s_req_callback;
};
