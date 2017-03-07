#include <iostream>
#include <stdexcept>
#include <limits> // 为了使用numeric_limits

using namespace std;
int main()
{
	int ival;
	while (cin >> ival, !cin.eof())
	{
		if (cin.bad())
		{
			throw runtime_error("IO stream corrupted");
			return 1;
		}
		if (cin.fail()) // 这种方法在widows下可以成功，当linux时不能成功，可能差别在于一种是阻塞，一种非阻塞
		{				// 缓冲区中的数据是怎么清空的差别
			cerr << "bad data, try again\n";
			cin.clear();
			cin.sync();
			//cin.clear(istream::failbit); // 不行，不知道怎么回事
			continue;
		}

		//if (cin.fail()) // no
		//{				
		//	cerr << "bad data, try again\n";
		//	//cin.clear();
		//	cin.clear(istream::failbit); 
		//	cin.clear(istream::badbit);		

		//	continue;
		//}

		//if (cin.fail()) // no
		//{				
		//	cerr << "bad data, try again\n";
		//	//cin.clear();
		//	cin.setstate(istream::badbit | istream::failbit);
		//	cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' );
		//	continue;
		//}
	}
	return 0;
}	