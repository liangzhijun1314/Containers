#include "stdafx.h"
#include "glog/logging.h"


void init_glog(const char* logpath, const char* appname)
{
	google::InitGoogleLogging(appname);

	std::string _strLog(logpath);
	_strLog += appname;

	std::string _strLogFile;

	_strLogFile = _strLog + ".INFO-";
	google::SetLogDestination(google::GLOG_INFO, _strLogFile.c_str());
	_strLogFile = _strLog + ".WARNING-";
	google::SetLogDestination(google::GLOG_WARNING, _strLogFile.c_str());
	_strLogFile = _strLog + ".ERROR-";
	google::SetLogDestination(google::GLOG_ERROR, _strLogFile.c_str());
	_strLogFile = _strLog + ".FATAL-";
	google::SetLogDestination(google::GLOG_FATAL, _strLogFile.c_str());

	_strLogFile = appname;
	LOG(INFO) << _strLogFile.c_str() << " start";

	google::FlushLogFiles(google::GLOG_INFO);
}