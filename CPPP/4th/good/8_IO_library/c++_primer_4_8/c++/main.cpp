/* C++ 版本 */
#include <iostream>
#include <limits> // 为了使用numeric_limits

using std::cout;
using std::endl;
using std::cin;
int main( )
{
	int value; 
	for (;;) {
		cout << "Enter an integer: ";
		cin >> value;
		/* 读到非法字符后，输入流将处于出错状态，
		* 为了继续获取输入，首先要调用clear函数
		* 来清除输入流的错误标记，然后才能调用
		* ignore函数来清除输入缓冲区中的数据。 */
		cin.clear( );
		/* numeric_limits<streamsize>::max( ) 返回缓冲区的大小。
		* ignore 函数在此将把输入缓冲区中的数据清空。
		* 这两个函数的具体用法请自行查询。 */
		cin.ignore( std::numeric_limits<std::streamsize>::max( ), '\n' ); 
		cout << value << '\n'; 
	}
	return 0;
}