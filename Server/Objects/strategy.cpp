#include "strategy.h"

Strategy::Strategy(StrategyType type, double x, double y)
    : m_type(type)
    , num1(x)
    , num2(y)
{
}

void Strategy::applyStrategy(double &price, int &num)
{
    switch(m_type)
    {
    case DirectDiscount:
    {
        price = price * num1 / 100.0;
        break;
    }
    case FullReduction:
    {
        if (price * num > num1) {
            price -= num2 / num;
        }
        break;
    }
    case BuyFree:
    {
        if (num > num1) {
            num += num2;
        }
        break;
    }
    case FlashSale:
    {
        price = num1;
        break;
    }
    }
}
