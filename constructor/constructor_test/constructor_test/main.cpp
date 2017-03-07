class A {
public:
    A() 
    {
        p = this;
    }
    ~A()
    {
        delete p;
        p = 0;
    }
private:
    A* p;
};

int main()
{
    //A a;
    A* p = new A;
    delete p;
}
