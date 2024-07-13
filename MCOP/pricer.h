#ifndef PRICER_H
#define PRICER_H

#include <random>
#include <cmath>
#include <algorithm>

double generateGaussianNoise(double mean, double stddev);
double callOptionPayoff(double S, double K);
double putOptionPayoff(double S, double K);
double monteCarloOptionPricing(double S0, double K, double r, double sigma, double T, int numSimulations, bool isCallOption);

#endif // PRICER_H
