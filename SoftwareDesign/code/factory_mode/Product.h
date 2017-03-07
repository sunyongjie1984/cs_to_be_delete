#ifndef _PRODUCT_H_
#define _PRODUCT_H_

/*
为了提高内聚（Cohesion）和松耦合（Coupling），我们经常会抽象出一些类的公共接口以形成抽象基类或者接口。
这样我们可以通过声明一个指向基类的指针来指向实际的子类实现，达到了多态的目的。
*/
class Product
{
public:
	virtual ~Product() = 0;
protected:
	Product();
private:
};

class ConcreteProduct:public Product
{
public:
	~ConcreteProduct();
	ConcreteProduct();
protected:
private:

};
#endif //~_PRODUCT_H_

