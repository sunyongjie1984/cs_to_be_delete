class cin_to_cout 
{
public:
	cin_to_cout(int temp): a(temp) { }
	friend std::ostream& operator>>(std::ostream&, cin_to_cout&);
private:
	int a;
};

std::ostream& operator>>(std::ostream& os, cin_to_cout& object)
{
	os << object.a;
	return os;
}
	