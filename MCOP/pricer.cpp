#include "pricer.h"

double generateGaussianNoise(double mean, double stddev) {
    static std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

double callOptionPayoff(double S, double K) {
    return std::max(S - K, 0.0);
}

double putOptionPayoff(double S, double K) {
    return std::max(K - S, 0.0);
}

double monteCarloOptionPricing(double S0, double K, double r, double sigma, double T, int numSimulations, bool isCallOption) {
    double payoffSum = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * generateGaussianNoise(0.0, 1.0));
        double payoff = isCallOption ? callOptionPayoff(ST, K) : putOptionPayoff(ST, K);
        payoffSum += payoff;
    }

    double averagePayoff = payoffSum / static_cast<double>(numSimulations);
    return std::exp(-r * T) * averagePayoff;
}
