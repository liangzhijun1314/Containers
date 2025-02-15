#define _CRT_SECURE_NO_WARNINGS
#include "parseJson.h"
#include <iostream>
#include <string>
#include <time.h>
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"


using namespace std;
using namespace rapidjson;

std::string parseJson::getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

std::string parseJson::readfile(std::string &fileName) {
	FILE *fp = fopen(fileName.c_str(), "rb");
	if (!fp) {
		std::cout << "open failed! file:" << fileName << std::endl;
		return "";
	}
	fseek(fp, 0, SEEK_END);
	int32_t fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = new char[fsize + 0x1000];
	if (NULL == buf)
	{
		std::cout << fileName << "not enough mem." << std::endl;
		return "";
	}
	size_t ret = fread(buf, 1, fsize, fp);
	if (ret != fsize)
		std::cout << "failed to read : " << fsize << "read : " << ret;
		
	buf[ret] = 0;
	fclose(fp);

	string result;
	if (ret >= 0) {
		result.append(buf, 0, ret);
	}
	delete[]buf;
	return result;
}
void parseJson::parserRegist(std::string data)
{
	std::cout << "-----------parserRegist-----------" << std::endl;
	//std::string data = readfile("reg.json");

	// test Json
	//std::string data =
	//	"{\"mac\":\"123456\","
	//	"\"ip\":\"10.10.10.1\","
	//	"\"port\":80,"
	//	"\"type\":1,"
	//	"\"card\":[{\"pos\":0,\"age\":0,\"status\":1,\"channel\" : 255}],"
	//	"\"callback\":\"/test.jsp\","
	//	"\"time\" : \"2019-05-12 11:20:00\"}";

	//创建解析对象
	rapidjson::Document doc;
	//首先进行解析，没有解析错误才能进行具体字段的解析
	if (!doc.Parse(data.data()).HasParseError())
	{
		if (doc.HasMember("mac") && doc["mac"].IsString())
		{
			cout << "mac = " << doc["mac"].GetString() << endl;
		}

		if (doc.HasMember("ip") && doc["ip"].IsString())
		{
			cout << "ip = " << doc["ip"].GetString() << endl;
		}

		if (doc.HasMember("port") && doc["port"].IsInt())
		{
			std::cout << "port = " << doc["port"].GetInt() << std::endl;
		}

		if (doc.HasMember("type") && doc["type"].IsInt())
		{
			std::cout << "type = " << doc["type"].GetInt() << std::endl;
		}


		if (doc.HasMember("card") && doc["card"].IsArray())
		{
			const rapidjson::Value& array = doc["card"];
			size_t len = array.Size();
			for (size_t i = 0; i < len; i++)
			{
				const rapidjson::Value& object = array[i];
				//为防止类型不匹配，一般会添加类型校验
				if (object.IsObject())
				{
					cout << "ObjectArray[" << i << "]: ";

					if (object.HasMember("pos") && object["pos"].IsInt())
					{
						cout << ", pos=" << object["pos"].GetInt();
					}
					if (object.HasMember("age") && object["age"].IsInt())
					{
						cout << ", age=" << object["age"].GetInt();
					}
					if (object.HasMember("status") && object["status"].IsInt())
					{
						cout << ", status=" << object["status"].GetInt();
					}
					if (object.HasMember("channel") && object["channel"].IsInt())
					{
						cout << ", channel=" << object["channel"].GetInt() << endl;
					}

				}
			}
		}


		if (doc.HasMember("callback") && doc["callback"].IsString())
		{
			cout << "callback = " << doc["callback"].GetString() << endl;
		}

		if (doc.HasMember("time") && doc["time"].IsString())
		{
			cout << "time = " << doc["time"].GetString() << endl;
		}
	}

}

std::string parseJson::writeRegist()
{
	std::cout << "-----------writeRegist-----------" << std::endl;
	
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	writer.Key("mac");
	writer.String("123456");

	writer.Key("ip");
	writer.String("10.10.10.1");

	writer.Key("port");
	writer.Int(80);

	writer.Key("type");
	writer.Int(1);

	writer.Key("card");
	writer.StartArray();
	for (int i = 0; i < 1; i++)
	{
		writer.StartObject();
		writer.Key("pos");
		writer.Int(0);
		writer.Key("status");
		writer.Int(1);
		writer.Key("channel");
		writer.Int((255));
		writer.EndObject();
	}
	writer.EndArray();


	writer.Key("callback");
	writer.String("/test.jsp");

	writer.Key("time");
	writer.String(getTime().c_str());

	writer.EndObject();

	std::string strData = strBuf.GetString();
	std:: cout << strData << std::endl;

	return  strData;
}

void parseJson::parserHeart(std::string data)
{

	std::cout << "-----------parserHeart-----------" << std::endl;
	// test json 
	//std::string data = "{\"pk\":\"123456\",\"time\":\"2019-05-12 11:20:00\"}";

	parse_unknow_name(data);
}

std::string parseJson::writeHeart()
{
	std::cout << "-----------writeHeart-----------" << std::endl;
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	writer.Key("pk");
	writer.String("123456");

	writer.Key("time");
	writer.String("getTime().c_str()");

	writer.EndObject();

	std::string strData = strBuf.GetString();
	std::cout << strData << std::endl;

	return  strData;
}

void parseJson::parseNodeStatusReport(std::string data)
{
	std::cout << "-----------parseNodeStatusReport-----------" << std::endl;
	//test json
	//std::string data =
	//	"{\"pk\": 123,"
	//	"\"status\":1,"
	//	"\"time\":\"2019-05-12 11:20:00\","
	//	"\"desc\":\"板卡1\","
	//	"\"card\":[{"
	//	"\"pos\":1,"
	//	"\"status\":1,"
	//	"\"channel\":125}]}";

	//创建解析对象
	rapidjson::Document doc;
	//首先进行解析，没有解析错误才能进行具体字段的解析
	if (!doc.Parse(data.data()).HasParseError())
	{
		if (doc.HasMember("pk") && doc["pk"].IsInt())
		{
			cout << "pk = " << doc["pk"].GetInt() << endl;
		}

		if (doc.HasMember("status") && doc["status"].IsInt())
		{
			std::cout << "status = " << doc["status"].GetInt() << std::endl;
		}

		if (doc.HasMember("time") && doc["time"].IsString())
		{
			cout << "time = " << doc["time"].GetString() << endl;
		}

		if (doc.HasMember("desc") && doc["desc"].IsString())
		{
			cout << "desc = " << doc["desc"].GetString() << endl;
		}


		if (doc.HasMember("card") && doc["card"].IsArray())
		{
			const rapidjson::Value& array = doc["card"];
			size_t len = array.Size();
			for (size_t i = 0; i < len; i++)
			{
				const rapidjson::Value& object = array[i];
				//为防止类型不匹配，一般会添加类型校验
				if (object.IsObject())
				{
					cout << "ObjectArray[" << i << "]: ";

					if (object.HasMember("pos") && object["pos"].IsInt())
					{
						cout << ", pos=" << object["pos"].GetInt();
					}
					if (object.HasMember("status") && object["status"].IsInt())
					{
						cout << ", status=" << object["status"].GetInt();
					}
					if (object.HasMember("channel") && object["channel"].IsInt())
					{
						cout << ", channel=" << object["channel"].GetInt() << endl;
					}
				}
			}
		}
	}
}

std::string parseJson::writeNodeStatusReport()
{
	std::cout << "-----------writeNodeStatusReport-----------" << std::endl;
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	writer.Key("pk");
	writer.Int(123456);

	writer.Key("status");
	writer.Int(123456);

	writer.Key("time");
	writer.String("getTime().c_str()");

	writer.Key("desc");
	writer.String("板卡1");

	writer.Key("card");
	writer.StartArray();
	for (int i = 0; i < 1; i++)
	{
		writer.StartObject();
		writer.Key("pos");
		writer.Int(0);
		writer.Key("status");
		writer.Int(1);
		writer.Key("channel");
		writer.Int((125));
		writer.EndObject();
	}
	writer.EndArray();

	writer.EndObject();

	std::string strData = strBuf.GetString();
	std::cout << strData << std::endl;

	return  strData;
}
void parseJson::parseSingleCheck(std::string data)
{
	std::cout << "-----------parseSingleCheck-----------" << std::endl;
	// test json 
	//std::string data = "{\"pk \":123456,\"server_pk\":123,\"server_pos\":1,\"server_channel\":15}";

	parse_unknow_name(data);
}

std::string parseJson::writeSingleCheck()
{
	std::cout << "-----------writeSingleCheck-----------" << std::endl;
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	writer.Key("pk");
	writer.Int(123456);

	writer.Key("server_pk");
	writer.Int(123);

	writer.Key("server_pos");
	writer.Int(1);

	writer.Key("server_channel");
	writer.Int(15);

	writer.EndObject();

	std::string strData = strBuf.GetString();
	std::cout << strData << std::endl;

	return  strData;
}

void parseJson::parseCarSendTask(std::string data)
{
	std::cout << "-----------parseCarSendTask-----------" << std::endl;
	// test json 
	/*
{
	"job_ID": 62,
	"type": 1,
	"start_time": "2019-07-11 09:24:24",
	"point": {
		"point_list": [{
			"point_id": 8,
			"point_pos": "120",
			"server_pk": 8,
			"server_pos": 1,
			"server_channel": 4
		},
		{
			"point_id": 9,
			"point_pos": "220",
			"server_pk": 8,
			"server_pos": 1,
			"server_channel": 2
		},
		{
			"point_id": 6,
			"point_pos": "110",
			"server_pk": 8,
			"server_pos": 1,
			"server_channel": 16
		},
		{
			"point_id": 4,
			"point_pos": "121",
			"server_pk": 8,
			"server_pos": 1,
			"server_channel": 64
		},
		{
			"point_id": 7,
			"point_pos": "210",
			"server_pk": 8,
			"server_pos": 1,
			"server_channel": 8
		},
		{
			"point_id": 1,
			"point_pos": "221",
			"server_pk": 8,
			"server_pos": 1,
			"server_channel": 1
		},
		{
			"point_id": 12,
			"point_pos": "122",
			"server_pk": 8,
			"server_pos": 4,
			"server_channel": 15
		},
		{
			"point_id": 13,
			"point_pos": "222",
			"server_pk": 8,
			"server_pos": 4,
			"server_channel": 240
		}]
	}
}
	*/

	// 读取文件中的json
	//std::string strFile = "E:\\CTVIT_Work\\Work\\Http_Demo\\Http_Server\\Http_Server\\cardSendTask.json";
	//data = readfile(strFile);


	//创建解析对象
	rapidjson::Document doc;
	//首先进行解析，没有解析错误才能进行具体字段的解析
	if (!doc.Parse(data.data()).HasParseError())
	{
		if (doc.HasMember("job_ID") && doc["job_ID"].IsInt())
		{
			std::cout << "job_ID = " << doc["job_ID"].GetInt() << std::endl;
		}
		if (doc.HasMember("type") && doc["type"].IsInt())
		{
			std::cout << "type = " << doc["type"].GetInt() << std::endl;
		}

		if (doc.HasMember("start_time") && doc["start_time"].IsString())
		{
			std::cout << "start_time = " << doc["start_time"].GetString() << std::endl;
		}

		if (doc.HasMember("point") && doc["point"].IsObject())
		{
			const rapidjson::Value& point = doc["point"];

			const rapidjson::Value& pointlist = point["point_list"];
			size_t lenlist = pointlist.Size();
			for (size_t nplist = 0; nplist < lenlist; nplist++)
			{

				const rapidjson::Value& object = pointlist[nplist];
				//为防止类型不匹配，一般会添加类型校验
				if (object.IsObject())
				{
					std::cout << "pointlistArray[" << nplist << "]: ";

					if (object.HasMember("point_id") && object["point_id"].IsInt())
					{
						cout << ", point_id=" << object["point_id"].GetInt();
					}
					if (object.HasMember("point_pos") && object["point_pos"].IsString())
					{
						cout << ", point_pos=" << object["point_pos"].GetString();
					}
					if (object.HasMember("server_pk") && object["server_pk"].IsInt())
					{
						cout << ", server_pk=" << object["server_pk"].GetInt() << endl;
					}

					if (object.HasMember("server_pos") && object["server_pos"].IsInt())
					{
						cout << ", server_pos=" << object["server_pos"].GetInt() << endl;
					}

					if (object.HasMember("server_channel") && object["server_channel"].IsInt())
					{
						cout << ", server_channel=" << object["server_channel"].GetInt() << endl;
					}
				}
			}
		}
	}
}
std::string parseJson::writeCarSendTask()
{
	std::cout << "-----------writeCarSendTask-----------" << std::endl;
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	writer.Key("job_ID");
	writer.Int(62);

	writer.Key("type");
	writer.Int(1);

	writer.Key("start_time");
	writer.String(getTime().c_str());


	writer.Key("point");
	writer.StartObject();
	
	writer.Key("point_list");
	writer.StartArray();
	for (int i = 0; i < 8; i++)
	{
		writer.StartObject();
		writer.Key("point_id");
		writer.Int(8);
		writer.Key("point_pos");
		writer.String("120");
		writer.Key("server_pk");
		writer.Int(8);
		writer.Key("server_pos");
		writer.Int(1);
		writer.Key("server_channel");
		writer.Int(4);
		writer.EndObject();
	}
	writer.EndArray();

	writer.EndObject();

	writer.EndObject();


	std::string strData = strBuf.GetString();
	std::cout << strData << std::endl;

	return  strData;
}

std::string parseJson::writeCarStopTask()
{
	std::cout << "-----------writeCarStopTask-----------" << std::endl;
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	writer.Key("job_id");
	writer.Int(123456);

	writer.Key("type");
	writer.Int(1);

	writer.Key("end_time");
	writer.String(getTime().c_str());

	writer.EndObject();

	std::string strData = strBuf.GetString();
	std::cout << strData << std::endl;

	return  strData;
}

void parseJson::parseCarStopTask(std::string data)
{
	std::cout << "-----------parseCarStopTask-----------" << std::endl;
	// test json
	//std::string data = "{\"job_id\":123456,\"type\":1,\"end_time\":\"2019-05-12 11:20:00\"}";

	parse_unknow_name(data);

}

void parseJson::parse() 
{
	std::cout << "-----------parse-----------" << std::endl;
	std::string data =
		"{\"Int\":1,"
		"\"Double\":12.0000001,"
		"\"String\":\"This is a string\","
		"\"Object\":{\"name\":\"qq849635649\",\"age\":25},"
		"\"IntArray\":[10,20,30],"
		"\"DoubleArray\":[1.0,2.0,3.0],"
		"\"StringArray\":[\"one\",\"two\",\"three\"],"
		"\"MixedArray\":[\"one\",50,false,12.005],"
		"\"People\":[{\"name\":\"qq849635649\",\"age\":0,\"sex\":true},"
		"{\"name\":\"qq849635649\",\"age\":10,\"sex\":false},"
		"{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}]}";

	//创建解析对象
	rapidjson::Document doc;
	//首先进行解析，没有解析错误才能进行具体字段的解析
	if (!doc.Parse(data.data()).HasParseError())
	{
		//1. 解析整数
		if (doc.HasMember("Int") && doc["Int"].IsInt())
		{
			std::cout << "Int = " << doc["Int"].GetInt() << std::endl;
		}
		//2. 解析浮点型
		if (doc.HasMember("Double") && doc["Double"].IsDouble())
		{
			cout << "Double = " << doc["Double"].GetDouble() << endl;
		}
		//3. 解析字符串
		if (doc.HasMember("String") && doc["String"].IsString())
		{
			cout << "String = " << doc["String"].GetString() << endl;
		}
		//4. 解析结构体
		if (doc.HasMember("Object") && doc["Object"].IsObject())
		{
			const rapidjson::Value& object = doc["Object"];
			if (object.HasMember("name") && object["name"].IsString())
			{
				cout << "Object.name = " << object["name"].GetString() << endl;
			}
			if (object.HasMember("age") && object["age"].IsInt())
			{
				cout << "Object.age = " << object["age"].GetInt() << endl;
			}
		}
		//5. 解析数组类型
		//5.1 整型数组类型
		if (doc.HasMember("IntArray") && doc["IntArray"].IsArray())
		{
			//5.1.1 将字段转换成为rapidjson::Value类型
			const rapidjson::Value& array = doc["IntArray"];
			//5.1.2 获取数组长度
			size_t len = array.Size();
			//5.1.3 根据下标遍历，注意将元素转换为相应类型，即需要调用GetInt()
			for (size_t i = 0; i < len; i++)
			{
				cout << "IntArray[" << i << "] = " << array[i].GetInt() << endl;
			}
		}
		//5.2 浮点型数组类型
		if (doc.HasMember("DoubleArray") && doc["DoubleArray"].IsArray())
		{
			const rapidjson::Value& array = doc["DoubleArray"];
			size_t len = array.Size();
			for (size_t i = 0; i < len; i++)
			{
				//为防止类型不匹配，一般会添加类型校验
				if (array[i].IsDouble())
				{
					cout << "DoubleArray[" << i << "] = " << array[i].GetDouble() << endl;
				}
			}
		}
		//5.3 字符串数组类型
		if (doc.HasMember("StringArray") && doc["StringArray"].IsArray())
		{
			const rapidjson::Value& array = doc["StringArray"];
			size_t len = array.Size();
			for (size_t i = 0; i < len; i++)
			{
				//为防止类型不匹配，一般会添加类型校验
				if (array[i].IsString())
				{
					cout << "StringArray[" << i << "] = " << array[i].GetString() << endl;
				}
			}
		}
		//5.4 混合型
		if (doc.HasMember("MixedArray") && doc["MixedArray"].IsArray())
		{
			const rapidjson::Value& array = doc["MixedArray"];
			size_t len = array.Size();
			for (size_t i = 0; i < len; i++)
			{
				//为防止类型不匹配，一般会添加类型校验
				if (array[i].IsString())
				{
					cout << "MixedArray[" << i << "] = " << array[i].GetString() << endl;
				}
				else if (array[i].IsBool())
				{
					cout << "MixedArray[" << i << "] = " << array[i].GetBool() << endl;
				}
				else if (array[i].IsInt())
				{
					cout << "MixedArray[" << i << "] = " << array[i].GetInt() << endl;
				}
				else if (array[i].IsDouble())
				{
					cout << "MixedArray[" << i << "] = " << array[i].GetDouble() << endl;
				}
			}
		}
		//5.5 结构体数组类型
		if (doc.HasMember("People") && doc["People"].IsArray())
		{
			const rapidjson::Value& array = doc["People"];
			size_t len = array.Size();
			for (size_t i = 0; i < len; i++)
			{
				const rapidjson::Value& object = array[i];
				//为防止类型不匹配，一般会添加类型校验
				if (object.IsObject())
				{
					cout << "ObjectArray[" << i << "]: ";
					if (object.HasMember("name") && object["name"].IsString())
					{
						cout << "name=" << object["name"].GetString();
					}
					if (object.HasMember("age") && object["age"].IsInt())
					{
						cout << ", age=" << object["age"].GetInt();
					}
					if (object.HasMember("sex") && object["sex"].IsBool())
					{
						cout << ", sex=" << (object["sex"].GetBool() ? "男" : "女") << endl;
					}
				}
			}
		}
	}
	/**
	*    最后注意：因为rapidjson不会做安全校验，所以要自己做安全校验，以int整型为例
	* “if(object.HasMember("age") && object["age"].IsInt()) {}”
	* 这句校验很重要，既要校验有该子段，也要校验类型正确，否则会引发程序崩溃
	*/
}


//遍历解析 用于不知道name的前提下
void parseJson::parse_unknow_name(std::string data)
{
	// 这个是用于遍历json数组，用于不知道name的前提下
	//std::string data = "{\"name\":\"qq849635649\",\"age\":20,\"sex\":true}";

	rapidjson::Document dom;
	if (!dom.Parse(data.data()).HasParseError())
	{
		for (rapidjson::Value::ConstMemberIterator iter = dom.MemberBegin(); iter != dom.MemberEnd(); ++iter)
		{
			std::string name = (iter->name).GetString();
			const rapidjson::Value& value = iter->value;
			if (value.IsString())
			{
				std::cout << name << " : " << value.GetString() << std::endl;
			}
			else if (value.IsInt())
			{
				std::cout << name << " : " << value.GetInt() << std::endl;
			}
			else if (value.IsBool())
			{
				std::cout << name << " : " << value.GetBool() << std::endl;
			}
		}
	}
}

void parseJson::writeJson()
{

	std::cout << "-----------writeJson-----------" << std::endl;
	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

	writer.StartObject();

	//1. 整数类型
	writer.Key("Int");
	writer.Int(1);

	//2. 浮点类型
	writer.Key("Double");
	writer.Double(12.0000001);

	//3. 字符串类型
	writer.Key("String");
	writer.String("This is a string");

	//4. 结构体类型
	writer.Key("Object");
	writer.StartObject();
	writer.Key("name");
	writer.String("qq849635649");
	writer.Key("age");
	writer.Int(25);
	writer.EndObject();

	//5. 数组类型
	//5.1 整型数组
	writer.Key("IntArray");
	writer.StartArray();
	//顺序写入即可
	writer.Int(10);
	writer.Int(20);
	writer.Int(30);
	writer.EndArray();

	//5.2 浮点型数组
	writer.Key("DoubleArray");
	writer.StartArray();
	for (int i = 1; i < 4; i++)
	{
		writer.Double(i * 1.0);
	}
	writer.EndArray();

	//5.3 字符串数组
	writer.Key("StringArray");
	writer.StartArray();
	writer.String("one");
	writer.String("two");
	writer.String("three");
	writer.EndArray();

	//5.4 混合型数组
	//这说明了，一个json数组内容是不限制类型的
	writer.Key("MixedArray");
	writer.StartArray();
	writer.String("one");
	writer.Int(50);
	writer.Bool(false);
	writer.Double(12.005);
	writer.EndArray();

	//5.5 结构体数组
	writer.Key("People");
	writer.StartArray();
	for (int i = 0; i < 3; i++)
	{
		writer.StartObject();
		writer.Key("name");
		writer.String("qq849635649");
		writer.Key("age");
		writer.Int(i * 10);
		writer.Key("sex");
		writer.Bool((i % 2) == 0);
		writer.EndObject();
	}
	writer.EndArray();

	writer.EndObject();

	string data = strBuf.GetString();
	cout << data << endl;
}

/**
* {"Int":1,
*  "Double":12.0000001,
*  "String":"This is a string",
*  "Object":{"name":"qq849635649","age":25},
*  "IntArray":[10,20,30],
*  "DoubleArray":[1.0,2.0,3.0],
*  "StringArray":["one","two","three"],
*  "MixedArray": ["one",50,false,12.005],
*  "People":[{"name":"qq849635649","age":0,"sex":true},
*            {"name":"qq849635649","age":10,"sex":false},
*            {"name":"qq849635649","age":20,"sex":true}]}
*/


