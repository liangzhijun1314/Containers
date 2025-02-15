#ifndef CTV_JSONPROCESS_H
#define CTV_JSONPROCESS_H

// ctv-jsonprocess.h
// 用来处理json数据
//
#include <iostream>
#include <list>
#include <vector>

#define POINT_LIST_COUNT 3
//
//// 2.1 请求参数 结构体
//typedef struct
//{
//	int pos;
//	int status;
//	int channel;
//}regist_single_board_info;
//
//typedef struct
//{
//	std::string mac = "";
//	std::string ip = "";
//	int port;
//	int type;
//	std::vector<regist_single_board_info> vboardList;
//	std::string callback = "";
//	std::string time = "";
//}RegistTrationRequest;
//
//// 2.6 节点上报 请求参数 结构体
//typedef struct {
//	int point_id;			// 含义：每个点的id		*
//	int status;				// 含义：1,正常 2 视频丢失 3音频丢失 4.线序异常 5.信号格式错误 6.温度告警 7.固定电平	*
//	int value;				// 含义：声道指示位   目前自适用status为7的情况，用uint8标识通道差异，每个bit对应一个通道 (1,固定电平 0正常)	*
//	std::string desc;		// 含义：节点状态描述
//	std::string time;		// 含义：时间`	*
//	int	dynamic_range;		// 含义：动态范围	说明：0 unknown  1 SDR	2 HLG	3 PQ	*
//	int colour_range;		// 含义：色域		说明：0 UNKNOWN	1 BT709	2 VANC	3 BT2020	*
//	int depth;				// 含义：量化深度   说明：0 unknown 其它多少bit就显示多少	*
//}ReportingRequest;
//
//// 2.7 信号检测辅助数据 请求参数 结构体
//typedef struct {
//	int point_id;			// 含义：信源主键    *
//	int video;				// 含义：视频类型    说明：0 标清 1,高清 2 4k   *
//	std::string point_pos;	// 含义：节点位置    *
//							/*说明：	110 主源HDD		111 主源BMC
//							210 备源HDD		211 备源BMC
//							120 主末（标清）121 主末（高清）
//							122 主末（4k）	220 备末（标清）
//							221 备末（高清）222 备末（4k）*/
//	int server_pk;			// 含义：节点对应服务器主键		说明：注册接口，系统返回的服务器主键	*
//	int server_pos;			// 含义：板卡槽位   说明：1-8	*
//	int server_channel;		// 含义：板卡通道   说明:4k信号 1-2 通道 高标清 1 - 8 通道	*
//}SignalDetailRequest;
//
//// 2.7 信号检测辅助数据 返回参数 结构体
//typedef struct {
//	std::string code;	// 含义：状态		说明：1成功0出错	*
//	std::string desc;	// 含义：错误信息描述	
//	// result object
//	int	point_id;		// 含义：信源唯一标识	*
//	std::string time;	// 含义：时间		说明：时间格式：YYYY-MM-DD hh:mm:ss		*
//	std::string point_desc;// 含义： 点状态描述
//	int status;			// 含义：每个点的状态	说明：1,正常 2 视频丢失 3音频丢失 4.线序异常
//	int	dynamic_range;	// 含义：动态范围	说明：0 unknown  1 SDR	2 HLG	3 PQ	*
//	int colour_range;	// 含义：色域		说明：0 UNKNOWN	1 BT709	2 VANC	3 BT2020	*
//	int depth;			// 含义：量化深度   说明：0 unknown 其它多少bit就显示多少	*
//}SignalDetailResult;
//
//// 2.8 板卡信号提取任务下发 请求参数 结构体
//typedef struct {
//	int point_id;			// 含义：每个点的id		*
//	int type;				// 含义：任务类型  1:定时  2：即使  *
//	std::string time;		// 含义：开始或结束执行时间
//	int status;				// 含义：启动或停止标志   0 停止 1 启动   *
//	int video;				// 含义：视频类型	说明：0 标清 1,高清 2 4k	*
//	std::string point_pos;	//含义：节点位置	*
//						  /*说明：	110 主源HDD		111 主源BMC
//						  210 备源HDD		211 备源BMC
//						  120 主末（标清）121 主末（高清）
//						  122 主末（4k）	220 备末（标清）
//						  221 备末（高清）222 备末（4k）*/
//	int server_pk;			// 含义：节点对应服务器主键		说明：注册接口，系统返回的服务器主键	*
//	int server_pos;			// 含义：板卡槽位   说明：1-8	*
//	int server_channel;		// 含义：板卡通道   说明:4k信号 1-2 通道 高标清 1 - 8 通道	*
//}point_list;
//
//typedef struct {
//	int job_id;				// 含义：比对任务唯一编号	*
//	int systemPk;			// 含义：系统主键	*
//	int type;				// 含义：任务类型	说明：1 定时 2 即时		*
//	std::string start_time;	// 含义：比对任务的开始时间		说明：YYYY-MM-DD hh:mm:ss
//	std::string end_time;	// 含义：停止时间
//	//point_list list[POINT_LIST_COUNT];
//	std::vector<point_list> vlist;
//}SingalMonitorStartInfo;
//
//
//// 2.9 板卡信号提取任务停止 请求参数 结构体
//typedef struct {
//	int job_id;			// 含义：比对任务唯一编号	*
//	int type;			// 含义：任务类型	说明： 1 定时 2 即时		*
//	std::string end_time;//含义：比对任务的停止时间		说明：YYYY-MM-DD hh:mm:ss	
//}SingalMonitorEndInfo;
//
//
class JsonProcess
{
public:
	JsonProcess() {}
	~JsonProcess() {}
//
//	static void parse(); // 遍历 用于知道name的情况
//	static void parse_unknow_name(std::string data);  // 遍历 用于不知道name的前提下
//	static void writeJson();  // 写json
//
	// 读取文件中的json数据
	static std::string readfile(const std::string fileName);
//	static void writefile(const std::string fileName, const std::string data);
	static void parseConfig(std::string data);  // 解析配置文件
//
//	//内容比对JSON 解析
//
//	static bool parseReponse(const std::string data, std::string &code, std::string &desc); // 解析常规的返回结果
//	static std::string writeReponse(const std::string &code, const std::string &desc); // 组装常规的返回结果
//
//	// 2.1 系统注册接口 解析与组装
//	static void parseRegistration(std::string data);  //解析注册接口json 的参数
//	static bool parseRegistrationReponse(const std::string data,std::string &code, std::string &desc, int &pk);  // 解析注册接口 返回参数
//	static std::string writeRegistration(RegistTrationRequest registInfo);// 组装注册接口的json
//
//	// 2.2 心跳接口
//	static void parseHeartbeat(std::string data);
//	static std::string writeHeartbeat(int pk, const std::string &time);
//
//	// 2.6 节点状态上报
//	static void parseReporting(std::string data);  
//	static std::string writeReporting(ReportingRequest *info);
//
//	// 2.7 信号检测辅助数据
//	static void parseSignalDetail(SignalDetailRequest &info, std::string data);
//	static bool parseSignalDetailReponse(std::string data);  // 解析信号检测辅助数据的 返回参数
//	static std::string writeSignalDetail(int point_id, int video, int point_pos, int server_pk, int server_pos, int server_channel);
//	static std::string writeSignalDetailResult(SignalDetailResult &resultInfo);
//
//	// 2.8 板卡信号提取任务下发
//	static void parseSingalMonitorStart(SingalMonitorStartInfo* info, std::string data);
//	static std::string writeSingalMonitorStart(int job_id, int systemPk, int type, const std::string &start_time, const std::string &end_time); //TODO 参数没加完
//
//	// 2.9 板卡信号提取任务停止
//	static void parseSingalMonitorEnd(SingalMonitorEndInfo& info, std::string data);
//	static std::string writeSingalMonitorEnd(int job_id, int type, const std::string &end_time);
//
//	// alarm 报警 json
//	static std::string writeAlarm(int BoardNo, int WarningFlags, void* WaringInfo);
//private:	
};

#endif // CTV_JSONPROCESS_H
