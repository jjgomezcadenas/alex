#include "LogUtil.h"

using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;

// {
//             "FATAL", "ALERT", "CRIT", "ERROR", "WARN",
//             "NOTICE", "INFO", "DEBUG", "NOTSET", "UNKNOWN" 
//         }

// enum    PriorityLevel { 
//   EMERG = 0, FATAL = 0, ALERT = 100, CRIT = 200, 
//   ERROR = 300, WARN = 400, NOTICE = 500, INFO = 600, 
//   DEBUG = 700, NOTSET = 800 
// }

namespace alex {

  void InitLoggerRoot()
  {
    log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
    appender1->setLayout(new log4cpp::BasicLayout());
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog.addAppender(appender1);
    klog.setPriority(log4cpp::Priority::DEBUG);
  }

  void InitLogger(std::string logger)
  {
    log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
    appender1->setLayout(new log4cpp::BasicLayout());
    log4cpp::Category& klog = log4cpp::Category::getInstance(logger);
    klog.addAppender(appender1);
    klog.setPriority(log4cpp::Priority::DEBUG);
  }

  log4cpp::Category& GetLogger(std::string logger)
  {
    log4cpp::Category& klog = log4cpp::Category::getInstance(logger);
    return klog;
  }

  log4cpp::Category& GetLoggerRoot()
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    return klog;
  }

  void SetDebugLevelRoot(string debugLevel) 
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    // klog << log4cpp::Priority::DEBUG 
    //       << "In DebugSvc::Configure SetLogger to " << debugLevel;

    if(debugLevel == "FATAL")
      klog.setPriority(log4cpp::Priority::FATAL);
    else if (debugLevel == "ERROR")
      klog.setPriority(log4cpp::Priority::ERROR);
   else if (debugLevel == "WARN")
      klog.setPriority(log4cpp::Priority::WARN);
    else if (debugLevel == "NOTICE")
      klog.setPriority(log4cpp::Priority::NOTICE);
    else if (debugLevel == "INFO")
      klog.setPriority(log4cpp::Priority::INFO);
    else
      klog.setPriority(log4cpp::Priority::DEBUG);
  }

  void SetDebugLevel(string debugLevel, string logger) 
  {
    log4cpp::Category& klog = log4cpp::Category::getInstance(logger);
    // klog << log4cpp::Priority::DEBUG 
    //       << "In SetDebugLevel " << logger << " set debug level to " << debugLevel;

    if(debugLevel == "FATAL")
      klog.setPriority(log4cpp::Priority::FATAL);
    else if (debugLevel == "ERROR")
      klog.setPriority(log4cpp::Priority::ERROR);
   else if (debugLevel == "WARN")
      klog.setPriority(log4cpp::Priority::WARN);
    else if (debugLevel == "NOTICE")
      klog.setPriority(log4cpp::Priority::NOTICE);
    else if (debugLevel == "INFO")
      klog.setPriority(log4cpp::Priority::INFO);
    else
      klog.setPriority(log4cpp::Priority::DEBUG);
  }
  string GetDebugLevel(string logger) 
  {
    log4cpp::Category& klog = log4cpp::Category::getInstance(logger);
    return log4cpp::Priority::getPriorityName(klog.getPriority());
  }

}
