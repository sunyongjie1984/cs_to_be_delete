class book {
public:
	// book(int i) : x(i) { }
	explicit book(int i) : x(i) { }
	int x;
};
void func(book a) { }
int main()
{
	book a(3);
	func(a);
	func(3); // error, because of explicit
	return 0;
}
