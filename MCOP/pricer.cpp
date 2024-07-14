#include "pricer.h"
#include <cmath>
#include <random>
#include <algorithm>

Pricer::Pricer(double spot, double strike, double rate, double volatility, double time, int simulations)
    : spot(spot), strike(strike), rate(rate), volatility(volatility), time(time), simulations(simulations) {}

double Pricer::calculateOptionPrice(bool isCall) {
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<double> results(numThreads, 0.0);

    int simsPerThread = simulations / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int start = i * simsPerThread;
        int end = (i == numThreads - 1) ? simulations : start + simsPerThread;
        threads.emplace_back(&Pricer::worker, this, start, end, std::ref(results[i]), isCall);
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    double sum = 0.0;
    for (const auto &res : results) {
        sum += res;
    }

    return (sum / simulations) * exp(-rate * time);
}

double Pricer::normalRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<> d(0, 1);
    return d(gen);
}

double Pricer::simulateOnePath(bool isCall) {
    double ST = spot * exp((rate - 0.5 * volatility * volatility) * time + volatility * sqrt(time) * normalRandom());
    if (isCall) {
        return std::max(ST - strike, 0.0);
    } else {
        return std::max(strike - ST, 0.0);
    }
}

void Pricer::worker(int start, int end, double &result, bool isCall) {
    double sum = 0.0;
    for (int i = start; i < end; ++i) {
        sum += simulateOnePath(isCall);
    }
    result = sum;
}

Contract Pricer::blackScholesOptionPricing(double S0, double K, double r, double sigma, double T, bool isCallOption) {
    Contract con;
    int days_till_expiry = T * 365.2425;
    con.dte = days_till_expiry;

    if (isCallOption) {
        double d1 = (log(S0 / K) + (r + ((sigma * sigma) / 2)) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - (sigma * std::sqrt(T));

        con.premium = S0 * cumulativeStandardNormal(d1) - K * std::exp(-r * T) * cumulativeStandardNormal(d2);
        con.delta = cumulativeStandardNormal(d1);
        con.gamma = cumulativeStandardNormal(d1) / (S0 * sigma * std::sqrt(T));
        con.theta = (-(S0 * cumulativeStandardNormal(d1) * sigma) / (2 * std::sqrt(T))) - (r * K * std::exp(-r * T) * cumulativeStandardNormal(d2));
        con.vega = S0 * cumulativeStandardNormal(d1) * std::sqrt(T);
        con.rho = K * T * std::exp(-r * T) * cumulativeStandardNormal(d2);
        con.implied_volatility = sigma - ((con.premium - (con.premium - 0.01)) / (con.vega));
        con.intrinsic_value = std::max(S0 - K, 0.0);

    } else {
        double d1 = (log(S0 / K) + (r + ((sigma * sigma) / 2)) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - (sigma * std::sqrt(T));

        con.premium = K * std::exp(-r * T) * cumulativeStandardNormal(-d2) - S0 * cumulativeStandardNormal(-d1);
        con.delta = cumulativeStandardNormal(d1) - 1;
        con.gamma = cumulativeStandardNormal(d1) / (S0 * sigma * std::sqrt(T));
        con.theta = (-(S0 * cumulativeStandardNormal(d1) * sigma) / (2 * std::sqrt(T))) + (r * K * std::exp(-r * T) * cumulativeStandardNormal(-d2));
        con.vega = S0 * cumulativeStandardNormal(d1) * std::sqrt(T);
        con.rho = -K * T * std::exp(-r * T) * cumulativeStandardNormal(-d2);
        con.implied_volatility = sigma - (((con.premium - 0.01) - con.premium) / (con.vega));
        con.intrinsic_value = std::max(K - S0, 0.0);
    }

    return con;
}

Contract Pricer::calculateGreeks(bool isCall) {
    return blackScholesOptionPricing(spot, strike, rate, volatility, time, isCall);
}

double Pricer::erf(double x) {
    const double A1 = 0.254829592;
    const double A2 = -0.284496736;
    const double A3 = 1.421413741;
    const double A4 = -1.453152027;
    const double A5 = 1.061405429;
    const double P = 0.3275911;

    int sign = (x >= 0) ? 1 : -1;
    x = fabs(x);

    double t = 1.0 / (1.0 + P * x);
    double y = 1.0 - (((((A5 * t + A4) * t) + A3) * t + A2) * t + A1) * t * exp(-x * x);

    return sign * y;
}

double Pricer::cumulativeStandardNormal(double x) {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}
