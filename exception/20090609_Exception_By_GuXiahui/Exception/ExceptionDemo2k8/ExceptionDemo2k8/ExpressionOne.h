#pragma once

class ExpressionOne  
{
public:
	ExpressionOne();
	virtual ~ExpressionOne();
	ExpressionOne operator+(const ExpressionOne& i);
};
