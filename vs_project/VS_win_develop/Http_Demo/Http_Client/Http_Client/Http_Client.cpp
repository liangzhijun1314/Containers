#include "Http_Client.h"
#include <string>
#include <iostream>
using namespace std;

#define POSTFIELDS1 "username=aitest&password=123456&manage=vip&rememberme=true&isApp=1"
#define POSTFIELDS2 "action=get_carer_psgs&lineId=2757&issueId=244&classesId=6006"
#define POSTFIELDS3 "imgName=/ossfs/cpn/user/psg_photo/20170904/05f9f6c9-5b72-41ff-a04e-5fda53fc994a_small.jpg"
#define CONTENTTYPE "Content-Type: application/x-www-form-urlencoded\r\n"
#define CONTENTTYPE1 "Content-Type: application/json;charset=utf-8\r\n"

#define HTTP_HEADER "Content-Type: application/x-www-form-urlencoded\r\n"
#define HTTP_BODY "body="



// 初始化client静态变量
int HttpClient::s_exit_flag = 0;
int HttpClient::s_show_headers = 0;
const char * HttpClient::s_show_headers_opt = "--show-headers";
ReqCallback HttpClient::s_req_callback;



// 客户端的网络请求响应
void HttpClient::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
{
	http_message *hm = (struct http_message *)event_data;
	int connect_status;

	switch (event_type)
	{
	case MG_EV_CONNECT:
		connect_status = *(int *)event_data;
		if (connect_status != 0)
		{
			printf("Error connecting to server, error code: %d\n", connect_status);
			s_exit_flag = 1;
		}
		break;
	case MG_EV_HTTP_REPLY:  //HTTP回复已到。解析的回复struct http_message通过处理程序的void *ev_data 指针传递
	{
		// LZJ add from official example 
		connection->flags |= MG_F_CLOSE_IMMEDIATELY;
		std::string rsp = "";
		if (s_show_headers) {

			std::cout << "Http header and result message : " << hm->message.p << std::endl;
			rsp = std::string(hm->message.p,  hm->message.len);
		}
		else {
			std::cout << "Http result message : " << hm->body.p << std::endl;
			rsp = std::string(hm->body.p, hm->body.len);
		}

		std::cout << "print message end." << std::endl;
		s_exit_flag = 1;		// 每次收到请求后关闭本次连接，重置标记
						 				 
		s_req_callback(rsp);	// 回调处理


		//printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);
		//std::string rsp = std::string(hm->body.p, hm->body.len);
		//connection->flags |= MG_F_SEND_AND_CLOSE;
		//s_exit_flag = 1; // 每次收到请求后关闭本次连接，重置标记

		//s_req_callback(rsp);  // 回调处理
	}
	break;
	case MG_EV_CLOSE:
		if (s_exit_flag == 0)
		{
			printf("Server closed connection\n");
			s_exit_flag = 1;
		};
		break;
	default:
		break;
	}
}


// 发送一次请求，并回调处理，然后关闭本次连接
void HttpClient::SendReq(const std::string &url, ReqCallback req_callback, bool isPost)
{
	// 给回调函数赋值
	s_req_callback = req_callback;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	std::string sbody =
		"{\"mac\":\"123456\","
		"\"ip\":\"10.10.10.1\","
		"\"port\":80,"
		"\"type\":1,"
		"\"card\":[{\"pos\":0,\"age\":0,\"status\":1,\"channel\" : 255}],"
		"\"callback\":\"/test.jsp\","
		"\"time\" : \"2019-05-12 11:20:00\"}";


	if (isPost) {
		auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), CONTENTTYPE1, sbody.c_str());
		mg_set_protocol_http_websocket(connection);
	}
	else 
	{
		auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), NULL, NULL);
		mg_set_protocol_http_websocket(connection);
	}

	std::cout << "Send http request , url : " << url << std::endl;

	// loop
	while (s_exit_flag == 0)
		mg_mgr_poll(&mgr, 500);

	mg_mgr_free(&mgr);
}