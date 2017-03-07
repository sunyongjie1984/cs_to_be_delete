#ifndef _FACTORY_H_
#define _FACTORY_H_


class Product;

/*
我们经常就是声明一个创建对象的接口，并封装了对象的创建过程。
*/

class Factory
{
public:
	virtual ~Factory() = 0;
	virtual Product* CreateProduct() = 0;
protected:
	Factory();
private:
};

class ConcreteFactory:public Factory
{
public:
	~ConcreteFactory();
	ConcreteFactory();
	Product* CreateProduct();
protected:
private:
};
#endif //~_FACTORY_H_