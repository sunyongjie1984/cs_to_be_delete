/* 

  Liyang Yu, Jan 9th, 2004, version 0.0

  this is to implement the domain and IP address resolution. 

  3 cases are considered:

  1. a host name is given (a host name looks like "www.delta.com"), query
     the IP address of the host

  2. an IP address is given (an IP address looks like 10.6.17.184), query
     the host name

  in the above two cases, the IP address and the host name are the same thing: 
  since IP address is hard to remember, they are usually aliased by a name, and this 
  name is known as the host name.

  3. nothing is given. in other words, we don't know the host name or the IP address.
     in this case, the standard host name for the current processor is used
     
*/

#ifndef _myHostInfo
#define _myHostInfo

#include <string>
using namespace std;

// this version is for both Windows and UNIX, the following line
// specifies that this is for WINDOWS
#ifndef WINDOWS_XP
	#define WINDOWS_XP
#endif

// #include <XPCException.h>  // add this later

#ifdef UNIX
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
#else
    #include <winsock2.h>
#endif
#include <stdio.h>
    
enum hostType {NAME, ADDRESS};
const int HOST_NAME_LENGTH = 64;

class myHostInfo
{

private:

	#ifdef UNIX
		char searchHostDB;     // search the host database flag
	#endif

	struct hostent *hostPtr;    // Entry within the host address database

public:

    // Default constructor
    myHostInfo();

    // Retrieves the host entry based on the host name or address
    myHostInfo(string& hostName, hostType type);
 
    // Destructor.  Closes the host entry database.
    ~myHostInfo()
    {
		#ifdef UNIX
			endhostent();
		#endif
    }

	#ifdef UNIX

		// Retrieves the next host entry in the database
		char getNextHost();

		// Opens the host entry database
		void openHostDb()
		{
			endhostent();
			searchHostDB = 1;
			sethostent(1);
		}

	#endif

    // Retrieves the hosts IP address
    char* getHostIPAddress() 
    {
        struct in_addr *addr_ptr;
		// the first address in the list of host addresses
        addr_ptr = (struct in_addr *)*hostPtr->h_addr_list;
		// changed the address format to the Internet address in standard dot notation
        return inet_ntoa(*addr_ptr);
    }    
    
    // Retrieves the hosts name
    char* getHostName()
    {
        return hostPtr->h_name;
    }

private:

	#ifdef WINDOWS_XP
		void detectErrorGethostbyname(int*,string&);
		void detectErrorGethostbyaddr(int*,string&);
	#endif
};

#endif
