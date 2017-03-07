#include<iostream> 
#include<iomanip> 
#include<vector> 

using std::cin; 
using std::cout; 
using std::endl; 
using std::vector; 
using std::ios; 

int main() 
{ 
	vector<double> vec; 
	double buf; 
	cout<<"请输入您要处理的数据(Ctrl+Z结束输入)"<<endl; 
	while(cin>>buf) 
	{ 
		vec.push_back(buf); 
	} 

	for(vector<double>::iterator i=vec.begin();i!=vec.end();++i) 
	{ 
		cout << std::setiosflags(ios::fixed)
			<<std::setiosflags(ios::right)
			<<std::setprecision(5)
			<< std::setw(20) << *i << endl; 
	} 
	return 0; 
} 