#ifndef STRATEGY_H
#define STRATEGY_H


class Strategy
{
public:
    enum StrategyType{
        DirectDiscount,
        FullReduction,
        BuyFree,
        FlashSale
    };
    Strategy(StrategyType type, double x, double y);
    void applyStrategy(double &price, int &num);

private:
    StrategyType m_type;
    double num1;
    double num2;
};

#endif // STRATEGY_H
