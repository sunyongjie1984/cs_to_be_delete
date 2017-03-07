#include "exlogger.h"
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/filesystem.hpp>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>

ExLogger *ExLogger::mInstance;
typedef std::stringstream stream_type;
typedef std::map<boost::thread::id, stream_type*> stream_map_type;

#define CHECK_MAP(MAP, KEY, DEFAULT_VALUE)\
if (MAP.find(KEY) == MAP.end())\
{\
	MAP[KEY] = DEFAULT_VALUE;\
}

class ExLogger::Implementation
{
public:
	Implementation()
	: mIsThrowExceptions(true)
	{
	}

	std::string getDateTimeAsString()
	{
		std::string tDateTimeString = to_simple_string(boost::posix_time::microsec_clock::local_time());
		std::string::size_type tLastIndexOfDot =  tDateTimeString.find_last_of('.');
		tDateTimeString = tDateTimeString.substr(0, tLastIndexOfDot);

		std::string::size_type tIndexOfColumn = tDateTimeString.find_first_of(':');
		while(tIndexOfColumn != std::string::npos)
		{
			tDateTimeString[tIndexOfColumn] = '\'';
			tIndexOfColumn = tDateTimeString.find_first_of(':');
		}
		return tDateTimeString;
	}

	std::string getTimeAsString()
	{
		std::string tTimeString = to_simple_string(boost::posix_time::microsec_clock::local_time());
		std::string::size_type tLastIndexOfDot =  tTimeString.find_first_of(' ');
		tTimeString = tTimeString.substr(tLastIndexOfDot+1);

		//std::string::size_type tIndexOfColumn = tTimeString.find_first_of(':');
		//while(tIndexOfColumn != std::string::npos)
		//{
		//	tTimeString[tIndexOfColumn] = '\'';
		//	tIndexOfColumn = tTimeString.find_first_of(':');
		//}

		return tTimeString;
	}

	stream_map_type mTempStreams;
	bool mIsThrowExceptions;
	boost::mutex mMutex;
};

ExLogger &ExLogger::instance()
{
	if (mInstance == NULL)
	{
		mInstance = new ExLogger();
	}

	return *mInstance;
}

void ExLogger::destroy()
{
	if ( mInstance != NULL )
	{
		delete mInstance;
		mInstance = NULL;
	}
}

ExLogger::ExLogger()
: mImpl(new Implementation())
{
}

ExLogger::~ExLogger()
{
	delete mImpl;
}

ExLogger & ExLogger::operator<<( char ch )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << ch ;
	return *this;
}

ExLogger & ExLogger::operator<<( signed short i )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << i ;
	return *this;
}

ExLogger & ExLogger::operator<<( unsigned short i )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << i ;
	return *this;
}

ExLogger & ExLogger::operator<<( signed int i )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << i;
	return *this;
}

ExLogger & ExLogger::operator<<( unsigned int i )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << i;
	return *this;
}

ExLogger & ExLogger::operator<<( signed long i )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << i;
	return *this;
}

ExLogger & ExLogger::operator<<( unsigned long i )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << i;
	return *this;
}

ExLogger & ExLogger::operator<<( float f )
{	
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << f;
	return *this;
}

ExLogger & ExLogger::operator<<( double f )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << f;
	return *this;
}

ExLogger & ExLogger::operator<<( const std::string& s )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << s;
	return *this;
}

ExLogger & ExLogger::operator<<( const char* c )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)
	*mImpl->mTempStreams[boost::this_thread::get_id()] << c ;
	return *this;
}

ExLogger & ExLogger::operator<<( const ExLoggerEndLine& pEndL )
{
	boost::mutex::scoped_lock lock(mImpl->mMutex);
	static std::ofstream debugLogFile;

	if (!debugLogFile.is_open())
	{
		if ( !boost::filesystem::exists(LOG_DIRECTORY) ) 
		{
			boost::filesystem::create_directories(LOG_DIRECTORY);
		}

		std::stringstream logFilePath;
		logFilePath << LOG_DIRECTORY << "/Exceptions_" << mImpl->getDateTimeAsString().c_str() << ".txt";
		debugLogFile.open(logFilePath.str().c_str());
	}

	CHECK_MAP(mImpl->mTempStreams, boost::this_thread::get_id(), new stream_type)

	std::stringstream ss;
	ss << boost::this_thread::get_id();

	debugLogFile<< mImpl->getTimeAsString().c_str() << " Thread ID:" << ss.str().c_str() 
				<< " :" << mImpl->mTempStreams[boost::this_thread::get_id()]->str().c_str() << std::endl;

	mImpl->mTempStreams[boost::this_thread::get_id()]->str("");

	return *this;
}

bool ExLogger::isThrowExceptions() const
{
	return mImpl->mIsThrowExceptions;
}

void ExLogger::setIsThrowExceptions( bool pIsThrowExceptions )
{
	mImpl->mIsThrowExceptions = pIsThrowExceptions;
}