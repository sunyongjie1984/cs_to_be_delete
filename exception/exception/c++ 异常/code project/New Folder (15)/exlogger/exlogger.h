#pragma once
#ifndef EXLOGGER_H 
#define EXLOGGER_H

#define EXLOG_ENABLED

#define THROW_EXLOG_EXCEPTIONS
#define LOG_DIRECTORY "logs"

#include <exception>
#include <string>

struct ExLoggerEndLine
{
};
#define EXLOG_ENDL ExLoggerEndLine()

#ifdef EXLOG_ENABLED

	#define EXLOG ExLogger::instance()

	#define EXLOG_START \
		try\
		{

	#define EXLOG_END \
		}catch (const std::exception& e)\
		{\
			ExLogger::instance() << "\n\tException in: " << __FILE__ << ", Line: " <<__LINE__ << ", Function:" << __FUNCSIG__ << "\n\tException is: "<< e.what() <<\
									"\n\tSource file last compiled at " << __TIME__<< " on date: "<< __DATE__ << ExLoggerEndLine();\
			if(ExLogger::instance().isThrowExceptions())\
			{\
				throw e; \
			}\
		}catch (...)\
		{\
			ExLogger::instance() << "\n\tUnknown Exception in: " << __FILE__ << ", Line: " <<__LINE__ << ", Function:" << __FUNCSIG__ <<\
									"\n\tSource file last compiled at " << __TIME__<< " on date: "<< __DATE__ << ExLoggerEndLine();\
			if(ExLogger::instance().isThrowExceptions())\
			{\
				throw std::exception(""); \
			}\
		}

	#define EXLOG_END_WITH_RETURN(X) \
		}catch (const std::exception& e)\
		{\
			ExLogger::instance() << "\n\tException in: " << __FILE__ << ", Line: " <<__LINE__ << ", Function:" << __FUNCSIG__ << "\n\tException is: "<< e.what() <<\
									"\n\tSource file last compiled at " << __TIME__<< " on date: "<< __DATE__ << ExLoggerEndLine(); \
			if(ExLogger::instance().isThrowExceptions())\
			{\
				throw e; \
			}\
			return X;\
		}catch (...)\
		{\
			ExLogger::instance() << "\n\tUnknown Exception in: " << __FILE__ << ", Line: " <<__LINE__ << ", Function:" << __FUNCSIG__ <<\
									"\n\tSource file last compiled at " << __TIME__<< " on date: "<< __DATE__ << ExLoggerEndLine(); \
			if(ExLogger::instance().isThrowExceptions())\
			{\
				throw std::exception(""); \
			}\
			return X;\
		}
#else
	#define EXLOG ;/##/
	#define EXLOG_ENDL /##/
	#define EXLOG_START /##/
	#define EXLOG_END /##/
	#define EXLOG_END_WITH_RETURN /##/
#endif

class __declspec(dllexport) ExLogger
{
public:
	/*instance function of ExLogger*/
	static ExLogger& instance();
	static void destroy();
	bool isThrowExceptions() const;
	void setIsThrowExceptions(bool pIsThrowExceptions);
	~ExLogger();

	ExLogger &operator<<(char ch);
	ExLogger &operator<<(signed short i);
	ExLogger &operator<<(unsigned short i);
	ExLogger &operator<<(signed int i);
	ExLogger &operator<<(unsigned int i);
	ExLogger &operator<<(signed long i);
	ExLogger &operator<<(unsigned long i);
	ExLogger &operator<<(float f);
	ExLogger &operator<<(double f);
	ExLogger &operator<<(const std::string& s);	
	ExLogger &operator<<(const char* c);
	ExLogger &operator<<(const void* ptr);
	ExLogger &operator<<(const ExLoggerEndLine& pEndL);

private:
	/*Private Constructor of ExLogger for singleton*/
	ExLogger();
	static ExLogger * mInstance;
	class Implementation;
	Implementation* mImpl;
};

#endif // EXLOGGER_H