class BaseClass {
public:
	BaseClass() { }
	void f(char *s = "unknow")
	{
		cout << "Function f() in BaseClass called from " << s << endl;
		h();
	}
protected:
	void g(char *s = "unknow")
	{
		cout << "Function g() in BaseClass called from " << s << endl;
	}
private:
	void h()
	{
		cout << "Function h() in BaseClass\n";
	}
};

class Derived1Level1 : public virtual BaseClass {
public:
	void f(char *s = "unknow")
	{
		cout << "Function f() in Derived1level1 called from " << s << endl;
		g("Derived1Level1");
		h("Derived1Level1");
	}
	void h(char *s = "unknow")
	{



