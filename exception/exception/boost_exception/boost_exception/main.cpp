#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/exception/current_exception_cast.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/enable_current_exception.hpp>
#include <boost/exception/enable_error_info.hpp>
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_at_line.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <boost/exception/errinfo_file_handle.hpp>
#include <boost/exception/errinfo_file_name.hpp>
#include <boost/exception/errinfo_file_open_mode.hpp>
#include <boost/exception/errinfo_nested_exception.hpp>
#include <boost/exception/errinfo_type_info_name.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/info_tuple.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/throw_exception.hpp>

struct exception_base: virtual std::exception, virtual boost::exception { };
struct io_error: virtual exception_base { };
struct file_read_error: virtual io_error { };

typedef boost::error_info<struct tag_errno_code, int> errno_code;

void read_file(FILE* f)
{
    char buf[26];
    int count = 26;
    size_t nr = fread(buf, 1, 50, f);
    std::cout << buf << std::endl;
    if(ferror(f))
    {
        throw file_read_error() << errno_code(errno);
    }
}

int main()
{
    FILE *stream;
    char list[30];
    int  i, numread, numwritten;
    if(fopen_s(&stream, "fread.out", "w+t") == 0)
    {
        for (i = 0; i < 25; i++)
            list[i] = (char)('a' + i);
        numwritten = fwrite(list, sizeof(char), 25, stream);
        printf("Wrote %d items\n", numwritten);
        fclose(stream);
    }
    else
        printf("Problem opening the file\n");

    if(fopen_s(&stream, "fread.out", "r+t") == 0)
    {
        // Attempt to read in 25 characters 
        read_file(stream);
        numread = fread( list, sizeof(char), 25, stream);
        printf("Number of items read = %d\n", numread);
        printf("Contents of buffer = %.25s\n", list);
        fclose(stream);
    }
    else
        printf("File could not be opened\n");
    return 0;
}
