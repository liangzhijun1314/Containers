#include "stdafx.h"
#include "ctv-jsonprocess.h"

#include "glog/logging.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"



std::string JsonProcess::readfile(const std::string fileName) {
	FILE *fp = fopen(fileName.c_str(), "rb");
	if (!fp) {
		LOG(ERROR) << "Open failed! file:" << fileName;
		return "";
	}
	fseek(fp, 0, SEEK_END);
	int32_t fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = new char[fsize + 0x1000];
	if (NULL == buf)
	{
		LOG(ERROR) << fileName << "not enough mem.";
		return "";
	}
	size_t ret = fread(buf, 1, fsize, fp);
	if (ret != fsize) {
		LOG(ERROR) << "Failed to read : " << fsize << "read : " << ret;
	}
		
	buf[ret] = 0;
	fclose(fp);

	std::string result;
	if (ret >= 0) {
		result.append(buf, 0, ret);
	}
	delete[]buf;
	return result;
}

//void JsonProcess::writefile(const std::string fileName, const std::string data)
//{
//	FILE* fp = fopen(fileName.c_str(), "ab+");
//	if (!fp)
//	{
//		LOG(ERROR) << "Open failed! file:" << fileName;
//		return;
//	}
//	fwrite(data.c_str(), sizeof(char), strlen(data.c_str()), fp);
//	fclose(fp);
//	return;
//}

void JsonProcess::parseConfig(std::string data)
{
	//g_fixe_level_ratio = AUDIO_IS_VALID_COEFFICIENT_NUM;
	//g_strLocalIp = ctvCommon::getLocalWinIP();
	//g_strLocalMac = ctvCommon::getLocalWinMac();
	////创建解析对象
	//rapidjson::Document doc;
	////首先进行解析，没有解析错误才能进行具体字段的解析
	//if (!doc.Parse(data.data()).HasParseError())
	//{
	//	if (doc.HasMember("fixe_level_ratio") && doc["fixe_level_ratio"].IsInt())
	//	{
	//		g_fixe_level_ratio = doc["fixe_level_ratio"].GetInt();
	//	}

	//	if (doc.HasMember("localIP") && doc["localIP"].IsString())
	//	{
	//		g_strLocalIp = doc["localIP"].GetString();
	//	}

	//	if (doc.HasMember("localMac") && doc["localMac"].IsString())
	//	{
	//		g_strLocalMac = doc["localMac"].GetString();
	//	}

	//	if (doc.HasMember("localPort") && doc["localPort"].IsInt())
	//	{
	//		g_iLocalPort = doc["localPort"].GetInt();
	//	}

	//	if (doc.HasMember("boardNo") && doc["boardNo"].IsInt())
	//	{
	//		g_iLocalBoardNo = doc["boardNo"].GetInt();
	//	}

	//	if (doc.HasMember("4KChanNo") && doc["4KChanNo"].IsInt())
	//	{
	//		g_iLocal4KChanNo = doc["4KChanNo"].GetInt();
	//	}
	//}
	//else
	//{
	//	LOG(ERROR) << "Parse config data is not a json .";
	//}

	return;
}

//bool JsonProcess::parseReponse(const std::string data, std::string &code, std::string &desc)
//{
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("code") && doc["code"].IsString())
//		{
//			code = doc["code"].GetString();
//		}
//
//		if (doc.HasMember("desc") && doc["desc"].IsString())
//		{
//			desc = doc["desc"].GetString();
//		}
//		return true;
//	}
//	else
//	{
//		LOG(ERROR) << "Reponse is not a json .";
//		return false;
//	}
//}
//std::string JsonProcess::writeReponse(const std::string &code, const std::string &desc)
//{
//	LOG(INFO) << "-----------writeReponse-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("code");
//	writer.String(code.c_str());
//
//	writer.Key("desc");
//	writer.String(desc.c_str());
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//
//void JsonProcess::parseRegistration(std::string data)
//{
//	LOG(INFO) << "-----------parseRegistration-----------";
//	//std::string data = readfile("reg.json");
//
//	// test Json
//	//std::string data =
//	//	"{\"mac\":\"123456\","
//	//	"\"ip\":\"10.10.10.1\","
//	//	"\"port\":80,"
//	//	"\"type\":1,"
//	//	"\"card\":[{\"pos\":0,\"age\":0,\"status\":1,\"channel\" : 255}],"
//	//	"\"callback\":\"/test.jsp\","
//	//	"\"time\" : \"2019-05-12 11:20:00\"}";
//
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("mac") && doc["mac"].IsString())
//		{
//			LOG(INFO) << "mac = " << doc["mac"].GetString();
//		}
//
//		if (doc.HasMember("ip") && doc["ip"].IsString())
//		{
//			LOG(INFO) << "ip = " << doc["ip"].GetString();
//		}
//
//		if (doc.HasMember("port") && doc["port"].IsInt())
//		{
//			LOG(INFO) << "port = " << doc["port"].GetInt();
//		}
//
//		if (doc.HasMember("type") && doc["type"].IsInt())
//		{
//			LOG(INFO) << "type = " << doc["type"].GetInt();
//		}
//
//
//		if (doc.HasMember("card") && doc["card"].IsArray())
//		{
//			const rapidjson::Value& array = doc["card"];
//			size_t len = array.Size();
//			for (size_t i = 0; i < len; i++)
//			{
//				const rapidjson::Value& object = array[i];
//				//为防止类型不匹配，一般会添加类型校验
//				if (object.IsObject())
//				{
//					LOG(INFO) << "ObjectArray[" << i << "]: ";
//
//					if (object.HasMember("pos") && object["pos"].IsInt())
//					{
//						LOG(INFO) << ", pos=" << object["pos"].GetInt();
//					}
//					if (object.HasMember("age") && object["age"].IsInt())
//					{
//						LOG(INFO) << ", age=" << object["age"].GetInt();
//					}
//					if (object.HasMember("status") && object["status"].IsInt())
//					{
//						LOG(INFO) << ", status=" << object["status"].GetInt();
//					}
//					if (object.HasMember("channel") && object["channel"].IsInt())
//					{
//						LOG(INFO) << ", channel=" << object["channel"].GetInt();
//					}
//
//				}
//			}
//		}
//
//
//		if (doc.HasMember("callback") && doc["callback"].IsString())
//		{
//			LOG(INFO) << "callback = " << doc["callback"].GetString();
//		}
//
//		if (doc.HasMember("time") && doc["time"].IsString())
//		{
//			LOG(INFO) << "time = " << doc["time"].GetString();
//		}
//	}
//
//}
//bool JsonProcess::parseRegistrationReponse(const std::string data, std::string &code, std::string &desc, int &pk) 
//{
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("code") && doc["code"].IsString())
//		{
//			code = doc["code"].GetString();
//		}
//
//		if (doc.HasMember("desc") && doc["desc"].IsString())
//		{
//			desc = doc["desc"].GetString();
//		}
//
//		if (doc.HasMember("result") && doc["result"].IsObject())
//		{
//			const rapidjson::Value& object = doc["result"];
//			if (object.HasMember("pk") && object["pk"].IsInt())
//			{
//				pk = object["pk"].GetInt();
//			}
//		}
//		return true;
//	}
//	else
//	{
//		LOG(ERROR) << "Registration reponse is not a json .";
//		return false;
//	}
//}
//
//std::string JsonProcess::writeRegistration(RegistTrationRequest registInfo)
//{
//	LOG(INFO) << "-----------writeRegistration-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("mac");
//	writer.String(registInfo.mac.c_str());
//
//	writer.Key("ip");
//	writer.String(registInfo.ip.c_str());
//
//	writer.Key("port");
//	writer.Int(registInfo.port);
//
//	writer.Key("type");
//	writer.Int(registInfo.type);
//
//	writer.Key("card");
//	writer.StartArray();
//	for (int i = 0; i < registInfo.vboardList.size(); i++)
//	{
//		writer.StartObject();
//		writer.Key("pos");
//		writer.Int(registInfo.vboardList.at(i).pos);
//		writer.Key("status");
//		writer.Int(registInfo.vboardList.at(i).status);
//		writer.Key("channel");
//		writer.Int(registInfo.vboardList.at(i).channel);
//		writer.EndObject();
//	}
//	writer.EndArray();
//
//
//	writer.Key("callback");
//	writer.String(registInfo.callback.c_str());
//
//	writer.Key("time");
//	writer.String(registInfo.time.c_str());
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//
//void JsonProcess::parseHeartbeat(std::string data)
//{
//	LOG(INFO) << "-----------parserHeartbeat-----------";
//	// test json 
//	//std::string data = "{\"pk\":\"123456\",\"time\":\"2019-05-12 11:20:00\"}";
//
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("pk") && doc["pk"].IsString())
//		{
//			LOG(INFO) << "pk = " << doc["pk"].GetString();
//		}
//		if (doc.HasMember("time") && doc["time"].IsString())
//		{
//			LOG(INFO) << "time = " << doc["time"].GetString();
//		}
//	}
//}
//
//std::string JsonProcess::writeHeartbeat(int pk,const std::string &time)
//{
//	LOG(INFO) << "-----------writeHeartbeat-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("pk");
//	writer.Int(pk);
//
//	writer.Key("time");
//	writer.String(time.c_str());
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//
//void JsonProcess::parseReporting(std::string data)
//{
//	LOG(INFO) << "-----------parseReporting-----------";
//	//test json
//	//1.4
//	//std::string data =
//	//	"{\"pk\": 123,"
//	//	"\"status\":1,"
//	//	"\"time\":\"2019-05-12 11:20:00\","
//	//	"\"desc\":\"板卡1\","
//	//	"\"card\":[{"
//	//	"\"pos\":1,"
//	//	"\"status\":1,"
//	//	"\"channel\":125}]}";
//
//	//1.5
//	//std::string data = "{\"point_id \":123456,\"status\":1,\"time\":\"2019-05-12 11:20:00\",\"dynamic_range\":1,\"colour_range\":1,\"depth\":8}";
//
//
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("pk") && doc["pk"].IsInt())
//		{
//			LOG(INFO) << "pk = " << doc["pk"].GetInt();
//		}
//
//		if (doc.HasMember("status") && doc["status"].IsInt())
//		{
//			LOG(INFO) << "status = " << doc["status"].GetInt();
//		}
//
//		if (doc.HasMember("time") && doc["time"].IsString())
//		{
//			LOG(INFO) << "time = " << doc["time"].GetString();
//		}
//
//		if (doc.HasMember("dynamic_range") && doc["dynamic_range"].IsString())
//		{
//			LOG(INFO) << "dynamic_range = " << doc["dynamic_range"].GetString();
//		}
//
//		if (doc.HasMember("colour_range") && doc["colour_range"].IsString())
//		{
//			LOG(INFO) << "colour_range = " << doc["colour_range"].GetString();
//		}
//
//		if (doc.HasMember("depth") && doc["depth"].IsString())
//		{
//			LOG(INFO) << "depth = " << doc["depth"].GetString();
//		}
//	}
//}
//
//std::string JsonProcess::writeReporting(ReportingRequest *info)
//{
//	LOG(INFO) << "-----------writeReporting-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("point_id");
//	writer.Int(info->point_id);
//
//	writer.Key("status");
//	writer.Int(info->status);
//
//	writer.Key("value");
//	writer.Int(info->value);
//
//	writer.Key("desc");
//	writer.String(info->desc.c_str());
//
//	writer.Key("time");
//	writer.String(info->time.c_str());
//
//	writer.Key("dynamic_range");
//	writer.Int(info->dynamic_range);
//
//	writer.Key("colour_range");
//	writer.Int(info->colour_range);
//
//	writer.Key("depth");
//	writer.Int(info->depth);
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//void JsonProcess::parseSignalDetail(SignalDetailRequest &info, std::string data)
//{
//	LOG(INFO) << "-----------parseSignalDetail-----------" ;
//	// test json 
//	// v1.4
//	//std::string data = "{\"pk \":123456,\"server_pk\":123,\"server_pos\":1,\"server_channel\":15}";
//
//	// v1.6
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("point_id") && doc["point_id"].IsInt())
//		{
//			info.point_id = doc["point_id"].GetInt();
//			LOG(INFO) << "point_id = " << doc["point_id"].GetInt();
//		}
//
//		if (doc.HasMember("video") && doc["video"].IsInt())
//		{
//			info.video = doc["video"].GetInt();
//			LOG(INFO) << "video = " << doc["video"].GetInt();
//		}
//
//		if (doc.HasMember("point_pos") && doc["point_pos"].IsString())
//		{
//			info.point_pos = doc["point_pos"].GetString();
//			LOG(INFO) << "point_pos = " << doc["point_pos"].GetString();
//		}
//
//		if (doc.HasMember("server_pk") && doc["server_pk"].IsInt())
//		{
//			info.server_pk = doc["server_pk"].GetInt();
//			LOG(INFO) << "server_pk = " << doc["server_pk"].GetInt();
//		}
//
//		if (doc.HasMember("server_pos") && doc["server_pos"].IsInt())
//		{
//			info.server_pos = doc["server_pos"].GetInt();
//			LOG(INFO) << "server_pos = " << doc["server_pos"].GetInt();
//		}
//
//		if (doc.HasMember("server_channel") && doc["server_channel"].IsInt())
//		{
//			info.server_channel = doc["server_channel"].GetInt();
//			LOG(INFO) << "server_channel = " << doc["server_channel"].GetInt();
//		}
//	}
//}
//
//bool JsonProcess::parseSignalDetailReponse(std::string data)
//{
//	std::string code = "";
//	std::string desc = "";
//	int point_id = -1;
//	std::string time = "";
//	int status = -1;
//	int dynamic_range = -1;
//	int colour_range = -1;
//	int depth = -1;
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("code") && doc["code"].IsString())
//		{
//			code = doc["code"].GetString();
//		}
//		if (doc.HasMember("desc") && doc["desc"].IsString())
//		{
//			desc = doc["desc"].GetString();
//		}
//		if (doc.HasMember("result") && doc["result"].IsObject())
//		{
//			const rapidjson::Value& object = doc["result"];
//			if (object.HasMember("point_id") && object["point_id"].IsInt())
//			{
//				point_id = object["point_id"].GetInt();
//			}
//			if (object.HasMember("time") && object["time"].IsString())
//			{
//				time = object["time"].GetString();
//			}
//			if (object.HasMember("status") && object["status"].IsInt())
//			{
//				status = object["status"].GetInt();
//			}
//			if (object.HasMember("dynamic_range") && object["dynamic_range"].IsInt())
//			{
//				dynamic_range = object["dynamic_range"].GetInt();
//			}
//			if (object.HasMember("colour_range") && object["colour_range"].IsInt())
//			{
//				colour_range = object["colour_range"].GetInt();
//			}
//			if (object.HasMember("depth") && object["depth"].IsInt())
//			{
//				depth = object["depth"].GetInt();
//			}
//		}
//		return true;
//	}
//	else
//	{
//		LOG(ERROR) << "SignalDetail reponse is not a json .";
//		return false;
//	}
//}
//
//std::string JsonProcess::writeSignalDetail(int point_id, int video, int point_pos, int server_pk, int server_pos, int server_channel)
//{
//	LOG(INFO) << "-----------writeSignalDetail-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("point_id");
//	writer.Int(point_id);
//
//	writer.Key("video");
//	writer.Int(video);
//
//	writer.Key("point_pos");
//	writer.Int(point_pos);
//
//	writer.Key("server_pk");
//	writer.Int(server_pk);
//
//	writer.Key("server_pos");
//	writer.Int(server_pos);
//
//	writer.Key("server_channel");
//	writer.Int(server_channel);
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//std::string JsonProcess::writeSignalDetailResult(SignalDetailResult &resultInfo)
//{
//	LOG(INFO) << "-----------writeSignalDetailResult-----------";
//
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("code");
//	writer.String(resultInfo.code.c_str());
//
//	writer.Key("desc");
//	writer.String(resultInfo.desc.c_str());
//
//	writer.Key("result");
//	writer.StartObject();
//	writer.Key("point_id");
//	writer.Int(resultInfo.point_id);
//
//	writer.Key("time");
//	writer.String(ctvCommon::getTime().c_str());
//
//	writer.Key("status");
//	writer.Int(resultInfo.status);
//
//	writer.Key("desc");
//	writer.String(resultInfo.point_desc.c_str());
//
//	writer.Key("dynamic_range");
//	writer.Int(resultInfo.dynamic_range);
//	writer.Key("colour_range");
//	writer.Int(resultInfo.colour_range);
//	writer.Key("depth");
//	writer.Int(resultInfo.depth);
//
//	writer.EndObject();
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//
//void JsonProcess::parseSingalMonitorStart(SingalMonitorStartInfo* info, std::string data)
//{
//	LOG(INFO) << "-----------parseSingalMonitorStart-----------" ;
//	// test json 
//	/*   v1.6
//	{
//	"job_ID": 62,
//	"type": 1,
//	"start_time": "2019-07-11 09:24:24",
//	"point": {
//	"point_list": [
//	{
//	"point_id": 8,
//	"video": 2,
//	"point_pos": "120",
//	"server_pk": 8,
//	"server_pos": 1,
//	"server_channel": 1
//	},
//	{
//	"point_id": 9,
//	"video": 2,
//	"point_pos": "220",
//	"server_pk": 8,
//	"server_pos": 1,
//	"server_channel": 2
//	},
//	{
//	"point_id": 6,
//	"video": 2,
//	"point_pos": "110",
//	"server_pk": 8,
//	"server_pos": 2,
//	"server_channel": 1
//	}
//	]
//	}
//	}
//	*/
//
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("job_id") && doc["job_id"].IsInt())
//		{
//			info->job_id = doc["job_id"].GetInt();
//			LOG(INFO) << "job_id = " << doc["job_id"].GetInt();
//		}
//		if (doc.HasMember("systemPk") && doc["systemPk"].IsInt())
//		{
//			info->systemPk = doc["systemPk"].GetInt();
//			LOG(INFO) << "systemPk = " << doc["systemPk"].GetInt();
//		}
//		if (doc.HasMember("type") && doc["type"].IsInt())
//		{
//			info->type = doc["type"].GetInt();
//			LOG(INFO) << "type = " << doc["type"].GetInt();
//		}
//
//		if (doc.HasMember("start_time") && doc["start_time"].IsString())
//		{
//			info->start_time = doc["start_time"].GetString(); 
//			LOG(INFO) << "start_time = " << info->start_time;
//		}
//
//		if (doc.HasMember("end_time") && doc["end_time"].IsString())
//		{
//			info->end_time = doc["end_time"].GetString();
//			LOG(INFO) << "end_time = " << doc["end_time"].GetString();
//		}
//
//		if (doc.HasMember("point") && doc["point"].IsObject())
//		{
//			const rapidjson::Value& point = doc["point"];
//
//			const rapidjson::Value& pointlist = point["point_list"];
//			size_t lenlist = pointlist.Size();
//			for (size_t nplist = 0; nplist < lenlist; nplist++)
//			{
//				point_list ptlist;
//				const rapidjson::Value& object = pointlist[nplist];
//				//为防止类型不匹配，一般会添加类型校验
//				if (object.IsObject())
//				{
//					LOG(INFO) << "pointlistArray[" << nplist << "]: ";
//
//					if (object.HasMember("point_id") && object["point_id"].IsInt())
//					{
//						ptlist.point_id = object["point_id"].GetInt();
//						LOG(INFO) << ", point_id=" << object["point_id"].GetInt();
//					}
//					if (object.HasMember("type") && object["type"].IsInt())
//					{
//						ptlist.type = object["type"].GetInt();
//						LOG(INFO) << ", type=" << object["type"].GetInt();
//					}
//					if (object.HasMember("time") && object["time"].IsString())
//					{
//						ptlist.time = object["time"].GetString();
//						LOG(INFO) << ", time=" << object["time"].GetString();
//					}
//					if (object.HasMember("status") && object["status"].IsInt())
//					{
//						ptlist.status = object["status"].GetInt();
//						LOG(INFO) << ", status=" << object["status"].GetInt();
//					}
//					if (object.HasMember("video") && object["video"].IsInt())
//					{
//						ptlist.video = object["video"].GetInt();
//						LOG(INFO) << ", video=" << object["video"].GetInt();
//					}
//					if (object.HasMember("point_pos") && object["point_pos"].IsString())
//					{
//						ptlist.point_pos = object["point_pos"].GetString();
//						LOG(INFO) << ", point_pos=" << object["point_pos"].GetString();
//					}
//					if (object.HasMember("server_pk") && object["server_pk"].IsInt())
//					{
//						ptlist.server_pk = object["server_pk"].GetInt();
//						LOG(INFO) << ", server_pk=" << object["server_pk"].GetInt();
//					}
//
//					if (object.HasMember("server_pos") && object["server_pos"].IsInt())
//					{
//						ptlist.server_pos = object["server_pos"].GetInt();
//						LOG(INFO) << ", server_pos=" << object["server_pos"].GetInt();
//					}
//
//					if (object.HasMember("server_channel") && object["server_channel"].IsInt())
//					{
//						ptlist.server_channel = object["server_channel"].GetInt();
//						LOG(INFO) << ", server_channel=" << object["server_channel"].GetInt();
//					}
//				}
//
//				info->vlist.push_back(ptlist);
//			}
//		}
//	}
//}
//std::string JsonProcess::writeSingalMonitorStart(int job_id, int systemPk, int type, const std::string &start_time,const std::string &end_time)
//{
//	LOG(INFO) << "-----------writeSingalMonitorStart-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("job_id");
//	writer.Int(job_id);
//
//	writer.Key("systemPk");
//	writer.Int(systemPk);
//
//	writer.Key("type");
//	writer.Int(type);
//
//	writer.Key("start_time");
//	writer.String(start_time.c_str());
//
//	writer.Key("end_time");
//	writer.String(end_time.c_str());
//
//	writer.Key("point");
//	writer.StartObject();
//	
//	writer.Key("point_list");
//	writer.StartArray();
//	for (int i = 0; i < 3; i++)
//	{
//		writer.StartObject();
//		writer.Key("point_id");
//		writer.Int(8);
//		writer.Key("video");
//		writer.Int(2);
//		writer.Key("point_pos");
//		writer.String("120");
//		writer.Key("server_pk");
//		writer.Int(8);
//		writer.Key("server_pos");
//		writer.Int(1);
//		writer.Key("server_channel");
//		writer.Int(1);
//		writer.EndObject();
//	}
//	writer.EndArray();
//
//	writer.EndObject();
//
//	writer.EndObject();
//
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//	return  strData;
//}
//
//std::string JsonProcess::writeSingalMonitorEnd(int job_id, int type,const std::string &end_time)
//{
//	LOG(INFO) << "-----------writeSingalMonitorEnd-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("job_id");
//	writer.Int(job_id);
//
//	writer.Key("type");
//	writer.Int(type);
//
//	writer.Key("end_time");
//	writer.String(end_time.c_str());
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//
//void JsonProcess::parseSingalMonitorEnd(SingalMonitorEndInfo& info, std::string data)
//{
//	LOG(INFO) << "-----------parseSingalMonitorEnd-----------";
//	// test json
//	//std::string data = "{\"job_id\":123456,\"type\":1,\"end_time\":\"2019-05-12 11:20:00\"}";
//
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		if (doc.HasMember("job_id") && doc["job_id"].IsInt())
//		{
//			info.job_id = doc["job_id"].GetInt();
//			LOG(INFO) << "job_id = " << doc["job_id"].GetInt();
//		}
//		if (doc.HasMember("type") && doc["type"].IsInt())
//		{
//			info.type = doc["type"].GetInt();
//			LOG(INFO) << "type = " << doc["type"].GetInt();
//		}
//		if (doc.HasMember("end_time") && doc["end_time"].IsString())
//		{
//			info.end_time = doc["end_time"].GetString();
//			LOG(INFO) << "end_time = " << doc["end_time"].GetString();
//		}
//	}
//}
//
//std::string JsonProcess::writeAlarm(int BoardNo, int WarningFlags, void* WaringInfo)
//{
//	//// 以下是 报警 用到的结构体  0x10 = 16
//	/////\brief 板卡故障信息结构体，信号丢失、标准错误
//	//typedef struct BoardSignalLostStdError
//	//{
//	//	char signal_lost_error[0x10]; ///\brief 信号丢失错误信息：字节下标对应信号序号，字节为0-正常；1-丢失；-1或其他，信号不存在
//	//	char signal_format_std_error[0x10]; ///\brief 信号标准不符错误信息：字节下标对应信号序号，字节为0-符合；1-不符；；-1或其他，信号不存在
//	//} ctvBoardSignalLostStdError;
//
//	/////\brief 板卡故障信息结构体，信号线序错误
//	//typedef struct BoardSignalSeqError
//	//{
//	//	char signal_seq_error_current_seq[0x10]; ///\brief 信号线序错误的信号当前序号：字节下标对应信号序号，；-1或小于0，信号不存在；其他，代表信号当前序号
//	//	char padding[0x10];
//	//}ctvBoardSignalSeqError;
//
//	/////\brief 板卡故障信息结构体，温度过高
//	//typedef struct BoardTempOver
//	//{
//	//	unsigned char temperature[4]; ///\brief 板卡温度，摄氏度。LittleEndian
//	//	char padding[0x10 * 2 - 4];
//	//}ctvBoardTempOver;
//
//
//	LOG(INFO) << "-----------writeAlarm-----------";
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	writer.Key("BoardNo");
//	writer.Int(BoardNo);
//
//	writer.Key("WarningFlags");
//	writer.Int(WarningFlags);
//
//	writer.Key("WaringInfo");
//	writer.String((char *)WaringInfo);
//
//	writer.EndObject();
//
//	std::string strData = strBuf.GetString();
//	LOG(INFO) << strData;
//
//	return  strData;
//}
//
//void JsonProcess::parse() 
//{
//	std::cout << "-----------parse-----------";
//	std::string data =
//		"{\"Int\":1,"
//		"\"Double\":12.0000001,"
//		"\"String\":\"This is a string\","
//		"\"Object\":{\"name\":\"qq849635649\",\"age\":25},"
//		"\"IntArray\":[10,20,30],"
//		"\"DoubleArray\":[1.0,2.0,3.0],"
//		"\"StringArray\":[\"one\",\"two\",\"three\"],"
//		"\"MixedArray\":[\"one\",50,false,12.005],"
//		"\"People\":[{\"name\":\"qq849635649\",\"age\":0,\"sex\":true},"
//		"{\"name\":\"qq849635649\",\"age\":10,\"sex\":false},"
//		"{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}]}";
//
//	//创建解析对象
//	rapidjson::Document doc;
//	//首先进行解析，没有解析错误才能进行具体字段的解析
//	if (!doc.Parse(data.data()).HasParseError())
//	{
//		//1. 解析整数
//		if (doc.HasMember("Int") && doc["Int"].IsInt())
//		{
//			std::cout << "Int = " << doc["Int"].GetInt() << std::endl;
//		}
//		//2. 解析浮点型
//		if (doc.HasMember("Double") && doc["Double"].IsDouble())
//		{
//			std::cout << "Double = " << doc["Double"].GetDouble() << std::endl;
//		}
//		//3. 解析字符串
//		if (doc.HasMember("String") && doc["String"].IsString())
//		{
//			std::cout << "String = " << doc["String"].GetString() << std::endl;
//		}
//		//4. 解析结构体
//		if (doc.HasMember("Object") && doc["Object"].IsObject())
//		{
//			const rapidjson::Value& object = doc["Object"];
//			if (object.HasMember("name") && object["name"].IsString())
//			{
//				std::cout << "Object.name = " << object["name"].GetString() << std::endl;
//			}
//			if (object.HasMember("age") && object["age"].IsInt())
//			{
//				std::cout << "Object.age = " << object["age"].GetInt() << std::endl;
//			}
//		}
//		//5. 解析数组类型
//		//5.1 整型数组类型
//		if (doc.HasMember("IntArray") && doc["IntArray"].IsArray())
//		{
//			//5.1.1 将字段转换成为rapidjson::Value类型
//			const rapidjson::Value& array = doc["IntArray"];
//			//5.1.2 获取数组长度
//			size_t len = array.Size();
//			//5.1.3 根据下标遍历，注意将元素转换为相应类型，即需要调用GetInt()
//			for (size_t i = 0; i < len; i++)
//			{
//				std::cout << "IntArray[" << i << "] = " << array[i].GetInt() << std::endl;
//			}
//		}
//		//5.2 浮点型数组类型
//		if (doc.HasMember("DoubleArray") && doc["DoubleArray"].IsArray())
//		{
//			const rapidjson::Value& array = doc["DoubleArray"];
//			size_t len = array.Size();
//			for (size_t i = 0; i < len; i++)
//			{
//				//为防止类型不匹配，一般会添加类型校验
//				if (array[i].IsDouble())
//				{
//					std::cout << "DoubleArray[" << i << "] = " << array[i].GetDouble() << std::endl;
//				}
//			}
//		}
//		//5.3 字符串数组类型
//		if (doc.HasMember("StringArray") && doc["StringArray"].IsArray())
//		{
//			const rapidjson::Value& array = doc["StringArray"];
//			size_t len = array.Size();
//			for (size_t i = 0; i < len; i++)
//			{
//				//为防止类型不匹配，一般会添加类型校验
//				if (array[i].IsString())
//				{
//					std::cout << "StringArray[" << i << "] = " << array[i].GetString() << std::endl;
//				}
//			}
//		}
//		//5.4 混合型
//		if (doc.HasMember("MixedArray") && doc["MixedArray"].IsArray())
//		{
//			const rapidjson::Value& array = doc["MixedArray"];
//			size_t len = array.Size();
//			for (size_t i = 0; i < len; i++)
//			{
//				//为防止类型不匹配，一般会添加类型校验
//				if (array[i].IsString())
//				{
//					std::cout << "MixedArray[" << i << "] = " << array[i].GetString() << std::endl;
//				}
//				else if (array[i].IsBool())
//				{
//					std::cout << "MixedArray[" << i << "] = " << array[i].GetBool() << std::endl;
//				}
//				else if (array[i].IsInt())
//				{
//					std::cout << "MixedArray[" << i << "] = " << array[i].GetInt() << std::endl;
//				}
//				else if (array[i].IsDouble())
//				{
//					std::cout << "MixedArray[" << i << "] = " << array[i].GetDouble() << std::endl;
//				}
//			}
//		}
//		//5.5 结构体数组类型
//		if (doc.HasMember("People") && doc["People"].IsArray())
//		{
//			const rapidjson::Value& array = doc["People"];
//			size_t len = array.Size();
//			for (size_t i = 0; i < len; i++)
//			{
//				const rapidjson::Value& object = array[i];
//				//为防止类型不匹配，一般会添加类型校验
//				if (object.IsObject())
//				{
//					std::cout << "ObjectArray[" << i << "]: ";
//					if (object.HasMember("name") && object["name"].IsString())
//					{
//						std::cout << "name=" << object["name"].GetString();
//					}
//					if (object.HasMember("age") && object["age"].IsInt())
//					{
//						std::cout << ", age=" << object["age"].GetInt();
//					}
//					if (object.HasMember("sex") && object["sex"].IsBool())
//					{
//						std::cout << ", sex=" << (object["sex"].GetBool() ? "男" : "女") << std::endl;
//					}
//				}
//			}
//		}
//	}
//	/**
//	*    最后注意：因为rapidjson不会做安全校验，所以要自己做安全校验，以int整型为例
//	* “if(object.HasMember("age") && object["age"].IsInt()) {}”
//	* 这句校验很重要，既要校验有该子段，也要校验类型正确，否则会引发程序崩溃
//	*/
//}
//
//
////遍历解析 用于不知道name的前提下
//void JsonProcess::parse_unknow_name(std::string data)
//{
//	// 这个是用于遍历json数组，用于不知道name的前提下
//	//std::string data = "{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}";
//
//	rapidjson::Document dom;
//	if (!dom.Parse(data.data()).HasParseError())
//	{
//		for (rapidjson::Value::ConstMemberIterator iter = dom.MemberBegin(); iter != dom.MemberEnd(); ++iter)
//		{
//			std::string name = (iter->name).GetString();
//			const rapidjson::Value& value = iter->value;
//			if (value.IsString())
//			{
//				LOG(INFO) << name << " : " << value.GetString();
//			}
//			else if (value.IsInt())
//			{
//				LOG(INFO) << name << " : " << value.GetInt();
//			}
//			else if (value.IsBool())
//			{
//				LOG(INFO) << name << " : " << value.GetBool();
//			}
//		}
//	}
//}
//
//void JsonProcess::writeJson()
//{
//
//	std::cout << "-----------writeJson-----------" << std::endl;
//	rapidjson::StringBuffer strBuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//
//	writer.StartObject();
//
//	//1. 整数类型
//	writer.Key("Int");
//	writer.Int(1);
//
//	//2. 浮点类型
//	writer.Key("Double");
//	writer.Double(12.0000001);
//
//	//3. 字符串类型
//	writer.Key("String");
//	writer.String("This is a string");
//
//	//4. 结构体类型
//	writer.Key("Object");
//	writer.StartObject();
//	writer.Key("name");
//	writer.String("qq849635649");
//	writer.Key("age");
//	writer.Int(25);
//	writer.EndObject();
//
//	//5. 数组类型
//	//5.1 整型数组
//	writer.Key("IntArray");
//	writer.StartArray();
//	//顺序写入即可
//	writer.Int(10);
//	writer.Int(20);
//	writer.Int(30);
//	writer.EndArray();
//
//	//5.2 浮点型数组
//	writer.Key("DoubleArray");
//	writer.StartArray();
//	for (int i = 1; i < 4; i++)
//	{
//		writer.Double(i * 1.0);
//	}
//	writer.EndArray();
//
//	//5.3 字符串数组
//	writer.Key("StringArray");
//	writer.StartArray();
//	writer.String("one");
//	writer.String("two");
//	writer.String("three");
//	writer.EndArray();
//
//	//5.4 混合型数组
//	//这说明了，一个json数组内容是不限制类型的
//	writer.Key("MixedArray");
//	writer.StartArray();
//	writer.String("one");
//	writer.Int(50);
//	writer.Bool(false);
//	writer.Double(12.005);
//	writer.EndArray();
//
//	//5.5 结构体数组
//	writer.Key("People");
//	writer.StartArray();
//	for (int i = 0; i < 3; i++)
//	{
//		writer.StartObject();
//		writer.Key("name");
//		writer.String("qq849635649");
//		writer.Key("age");
//		writer.Int(i * 10);
//		writer.Key("sex");
//		writer.Bool((i % 2) == 0);
//		writer.EndObject();
//	}
//	writer.EndArray();
//
//	writer.EndObject();
//
//	std::string data = strBuf.GetString();
//	std::cout << data << std::endl;
//}
//
///**
//* {"Int":1,
//*  "Double":12.0000001,
//*  "String":"This is a string",
//*  "Object":{"name":"qq849635649","age":25},
//*  "IntArray":[10,20,30],
//*  "DoubleArray":[1.0,2.0,3.0],
//*  "StringArray":["one","two","three"],
//*  "MixedArray": ["one",50,false,12.005],
//*  "People":[{"name":"qq849635649","age":0,"sex":true},
//*            {"name":"qq849635649","age":10,"sex":false},
//*            {"name":"qq849635649","age":20,"sex":true}]}
//*/
//
//
