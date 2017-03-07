#ifndef _ABSTRACTFACTORY_H_
#define _ABSTRACTFACTORY_H_
class AbstractProductA;
class AbstractProductB;
/*
是将这一组对象的创建封装到一个用于创建对象的类（ConcreteFactory）中，维护这样一个创建类总比维护n多相关对象的创建过程要简单的多
*/
class AbstractFactory
{
public:
	virtual ~AbstractFactory();
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;
protected:
	AbstractFactory();
private:
};
class ConcreteFactory1:public AbstractFactory
{
public:
	ConcreteFactory1();
	~ConcreteFactory1();
	AbstractProductA* CreateProductA();
	AbstractProductB* CreateProductB();
protected:
private:
};
class ConcreteFactory2:public AbstractFactory
{
public:
	ConcreteFactory2();
	~ConcreteFactory2();
	AbstractProductA* CreateProductA();
	AbstractProductB* CreateProductB();
protected:
private:
};
#endif //~_ABSTRACTFACTORY_H_