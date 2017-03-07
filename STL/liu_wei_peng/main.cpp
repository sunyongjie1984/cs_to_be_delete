namespace MyPrj
{
	namespace detail
	{
		template<typename InputIter>
		InputIter skip(InputIter iter, InputIter end, typename InputIter::value_type c = ' ')
		{
			while(iter != end && *iter == c)
				++iter;
			return iter;
		}
	} // namespace detail

	template<typename SequenceT, typename StringT>
	inline  SequenceT& split(SequenceT& seq, StringT s, typename StringT::value_type delim)
	{
		typename StringT::iterator end   = s.end(),
			start  = detail::skip(s.begin(),end,delim),
			over  = start;

		for(;start != end;++over)
		{
			if(*over == delim || over == end) 
			{
				seq.push_back(StringT(start,over));
				start = over = detail::skip(over,end,delim);
			}
		}
		return seq;
	}
} // namespace MyProj

int main()
{
	return 0;
}
//本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/pongba/archive/2006/09/23/1268134.aspx