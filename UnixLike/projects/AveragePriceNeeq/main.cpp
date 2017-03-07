#include <iostream>
unsigned int ap(unsigned int unSaleComparePrice, unsigned int unBuyComparePrice, unsigned int priceStep)
{
    return ((unSaleComparePrice + unBuyComparePrice + priceStep) / (2 *priceStep))*priceStep;
}

int main()
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    std::cout << "please input three integr, price1, price2, pricestep" << std::endl;
    std::cin >> a >> b >> c;

    std::cout << "average price is " << ap(a, b, c) << std::endl;
    return 0;
}

