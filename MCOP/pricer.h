#ifndef PRICER_H
#define PRICER_H

#include <vector>
#include <thread>

struct Contract {
    double premium;
    int dte;
    double delta;
    double gamma;
    double theta;
    double vega;
    double rho;
    double implied_volatility;
    double intrinsic_value;
};

class Pricer {
public:
    Pricer(double spot, double strike, double rate, double volatility, double time, int simulations);
    double calculateOptionPrice(bool isCall);
    Contract calculateGreeks(bool isCall);
    Contract blackScholesOptionPricing(double S0, double K, double r, double sigma, double T, bool isCallOption);

private:
    double spot;
    double strike;
    double rate;
    double volatility;
    double time;
    int simulations;

    double normalRandom();
    double simulateOnePath(bool isCall);
    void worker(int start, int end, double &result, bool isCall);
    double erf(double x);
    double cumulativeStandardNormal(double x);  // Add this declaration
};

#endif // PRICER_H
