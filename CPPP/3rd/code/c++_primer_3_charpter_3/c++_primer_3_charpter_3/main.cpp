#include "CString.h"
int main()
{
	//CString str1;
	//CString str2;
	//if (str1 == str2)
	//{
	//	std::cout << "I love China" << std::endl;
	//}

	//CString str3;
	//std::cin >> str3;
	//std::cout << str3 << std::endl;

	//CString str4(str3);  // 都调用拷贝构造函数
	//CString str5 = str3; // 拷贝构造函数

	//CString str6;		 // 赋值操作符
	//str6 = str3;		 // 就是说，赋值操作符有两种可能，一种是调用拷贝构造函数，一种是调用赋值操作符
	
	int aCnt = 0;
	int eCnt = 0;
	int iCnt = 0;
	int oCnt = 0;
	int uCnt = 0;
	int theCnt = 0;
	int itCnt = 0;
	int wdCnt = 0;
	int notVowel = 0;
	
	CString buf;
	CString the("the");
	CString it("it");
	/*	输入缓冲是行缓冲。当从键盘上输入一串字符并按回车后，这些字符会首先被送到输入缓冲区中存储。每当按下回车键后，
cin.get()   就会检测输入缓冲区中是否有了可读的数据。cin.get()   还会对键盘上是否有作为流结束标志的   Ctrl+Z   或者   Ctrl+D  
键按下作出检查，其检查的方式有两种：阻塞式以及非阻塞式。 
阻塞式检查方式指的是只有在回车键按下之后才对此前是否有   Ctrl+Z   组合键按下进行检查，非阻塞式样指的是按下   Ctrl+D   
之后立即响应的方式。如果在按   Ctrl+D   之前已经从键盘输入了字符，则   Ctrl+D的作用就相当于回车，
即把这些字符送到输入缓冲区供读取使用，此时Ctrl+D不再起流结束符的作用。如果按   Ctrl+D   之前没有任何键盘输入，
则   Ctrl+D   就是流结束的信号。 
Windows系统中一般采用阻塞式检查   Ctrl+Z、Unix/Linux系统下一般采用非阻塞式的检查   Ctrl+D。楼主是在Windows系统下
，因此使用阻塞式的   Ctrl+Z   来标识流的结束。 
这种阻塞式的方式有一个特点：只有按下回车之后才有可能检测在此之前是否有Ctrl+Z按下。还有一个特点就是：
如果输入缓冲区中有可读的数据则不会检测Ctrl+Z（因为有要读的数据，还不能认为到了流的末尾）。还有一点需要知道：
Ctrl+Z产生的不是一个普通的ASCII码值，也就是说它产生的不是一个字符，所以不会跟其它从键盘上输入的字符一样能够存放在输入缓冲区。
明白了这几点之后就可以来解释楼主提出的问题了。 
从键盘上输入abcd^z   加   回车之后在Windows系统上是这样处理的：由于回车的作用，前面的   abcd  
等字符被送到输入缓冲区（注意：上面说过了，^z不会产生字符，所以更不会存储到输入缓冲区，缓冲区中没有   ^z   的存在）。
这时，cin.get()   检测到输入缓冲区中已经有数据存在（因此不再检查是否有   ^z   的输入），于是从缓冲中读取相应的数据。
如果都读取完了，则输入缓冲区重新变为空，cin.get()   等待新的输入。可见，尽管有   ^z   按下，但是由于在此之前还有其它输入字符（abcd）
，所以流也不会结束。 
因此，输入流结束的条件就是：^z   之前不能有任何字符输入（回车除外），否则   ^z   起不到流结束的作用。 
半小时后我就结贴。希望各位还对这个问题有迷惑都可以来看看！*/ 
	while(std::cin >> buf)
	{
		++wdCnt;
		std::cout << buf << ' ';
		if (wdCnt %12 == 0)
		{
			std::cout << std::endl;
		}

		if (buf == the || buf == "the")
		{
			++ theCnt;
		}
		else if (buf == it || buf == "it")
		{
			++itCnt;
		}

		for (int ix = 0; ix < buf.size(); ix++)
		{
			switch(buf[ix])
			{
			case 'a': 
			case 'A':
				++aCnt;
				break;
			case 'e': 
			case 'E':
				++eCnt;
				break;
			case 'i': 
			case 'I':
				++iCnt; 
				break;
			case 'o':
			case 'O': 
				++oCnt;
				break;
			case 'u':
			case 'U':
				++uCnt;
				break;
			default:
				++notVowel;
				break;
			}
		}
	}
	std::cout << "\n\n" 
		<< "Word read: " << wdCnt << "\n\n"
		<< "the/The: " << theCnt << '\n'
		<< "it/It: " << itCnt << "\n\n"
		<< "non-vowels read: " << notVowel << "\n\n"
		<< "a: " << aCnt << '\n'
		<< "e: " << eCnt << '\n'
		<< "i: " << iCnt << '\n'
		<< "o: " << oCnt << '\n'
		<< "u: " << uCnt << std::endl;
	return 0;
}