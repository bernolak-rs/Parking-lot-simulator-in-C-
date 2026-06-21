#pragma once
#include <chrono>
#include <cmath>

typedef std::chrono::system_clock::time_point c_time;

/**
 * Implemented with Strategy pattern.
 * Defined interface PricingPolicy and implemented different pricing policies
 */
class PricingPolicy
{
public:
    virtual ~PricingPolicy() = default;

    virtual double calculatePrice(c_time entryTime, c_time exitTime) const = 0;
};



class HourlyPricingPolicy : public PricingPolicy
{
private:
    double firstHourPrice;
    double nextHourPrice;

public:
    HourlyPricingPolicy(double firstHourPrice, double nextHourPrice)
        : firstHourPrice(firstHourPrice),
          nextHourPrice(nextHourPrice)
    {
    }

    double calculatePrice(c_time entryTime, c_time exitTime) const override
    {
        auto durationMinutes = 
            std::chrono::duration_cast<std::chrono::minutes>(exitTime - entryTime).count();

        if (durationMinutes <= 0)
        {
            return 0.0;
        }

        int hours = static_cast<int>(std::ceil(durationMinutes / 60.0));

        if (hours <= 1)
        {
            return firstHourPrice;
        }

        return firstHourPrice + (hours - 1) * nextHourPrice;
    }
};

class FlatRatePricingPolicy : public PricingPolicy
{
private:
    double price;

public:
    explicit FlatRatePricingPolicy(double price)
        : price(price)
    {
    }

    double calculatePrice(c_time entryTime, c_time exitTime) const override
    {
        return price;
    }
};
