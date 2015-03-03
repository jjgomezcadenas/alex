#ifndef LOGUTIL_
#define LOGUTIL_
/*
 LOGUTIL: Utilities for Logging

 JJGC, July, 2014.
*/


#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <string>

 using std::string; 

namespace alex {
	void InitLoggerRoot();
	void InitLogger(std::string logger);
	void SetDebugLevelRoot(std::string debugLevel);
	void SetDebugLevel(string debugLevel, string logger);
	std::string GetDebugLevel(string logger);
	log4cpp::Category& GetLogger(std::string logger);
  	log4cpp::Category& GetLoggerRoot();

}
#endif