#include <iostream>
class CBook {
public:
	CBook()
    {
        i = 10;
        j = 20;
    }
	int GetJ()              // 这样定义表示“命令”子类继承这个函数，没有什么说的。
    {
        return j;
    }
    virtual int GetIJ()     // 这样定义表示“期望”子类覆盖它，没有什么说的。
    {
        return i + j;
    }
	virtual int GetI() = 0; // 这样定义表示“命令”子类覆盖它，没有什么说的。

protected:
	int i;
	int j;
};

class CBookChild : public CBook {
public:
	int GetJ()  // 子类继承这个函数，没有听众我的命令。这是C++语言允许的的错误。 
    {
        return j + 1;
    }
    int GetIJ() // 你覆盖了我，符合了我的期望，可是如果你没有覆盖我，我也不怪你。
    {
        return i + j + 1;
    }
	int GetI()  // 你覆盖了我，这是你的任务，听从了我的命令。你不覆盖我，那是c++语言不允许的错误。
    {
        return i + 1;
    }
};

int main()
{
//  CBook* p = new CBook(); // 不能实例化对象
	CBook* p = new CBookChild();
	CBookChild* q = new CBookChild();
	std::cout << p->GetJ()  << std::endl;
    std::cout << p->GetIJ() << std::endl;
	std::cout << p->GetI()  << std::endl;

	std::cout << q->GetJ()  << std::endl;
    std::cout << q->GetIJ() << std::endl;
    std::cout << q->GetI()  << std::endl;
	return 0;
}
