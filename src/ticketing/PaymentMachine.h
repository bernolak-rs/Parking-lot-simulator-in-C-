#include "Ticket.h"
#include "PricingPolicy.h"
#include <memory>

typedef std::chrono::system_clock::time_point c_time;

class PaymentMachine
{
private:
    std::unique_ptr<PricingPolicy> pricingPolicy;

public:
    explicit PaymentMachine(std::unique_ptr<PricingPolicy> pricingPolicy)
        : pricingPolicy(std::move(pricingPolicy))
    {
    }

    double calculatePrice(const Ticket& ticket, c_time exitTime) const
    {
        return pricingPolicy->calculatePrice(
            ticket.getEntryTime(),
            exitTime
        );
    }
};
