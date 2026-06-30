#include "../src/ticketing/PaymentMachine.h"
#include "../src/ticketing/PricingPolicy.h"
#include "../src/ticketing/Ticket.h"

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <optional>

namespace {
c_time atMinute(int minute) {
    return c_time{} + std::chrono::minutes(minute);
}

Ticket makeTicket(c_time entryTime) {
    return Ticket(1, "BA123AA", entryTime, std::nullopt);
}

void assertClose(double actual, double expected) {
    assert(std::fabs(actual - expected) < 0.000001);
}

void testHourlyPolicyReturnsZeroForNoDuration() {
    HourlyPricingPolicy policy(2.0, 1.5);

    assertClose(policy.calculatePrice(atMinute(10), atMinute(10)), 0.0);
    assertClose(policy.calculatePrice(atMinute(20), atMinute(10)), 0.0);
}

void testHourlyPolicyChargesFirstHour() {
    HourlyPricingPolicy policy(2.0, 1.5);

    assertClose(policy.calculatePrice(atMinute(0), atMinute(1)), 2.0);
    assertClose(policy.calculatePrice(atMinute(0), atMinute(60)), 2.0);
}

void testHourlyPolicyRoundsUpPartialHours() {
    HourlyPricingPolicy policy(2.0, 1.5);

    assertClose(policy.calculatePrice(atMinute(0), atMinute(61)), 3.5);
    assertClose(policy.calculatePrice(atMinute(0), atMinute(121)), 5.0);
}

void testFlatRatePolicyAlwaysReturnsSamePrice() {
    FlatRatePricingPolicy policy(7.5);

    assertClose(policy.calculatePrice(atMinute(0), atMinute(0)), 7.5);
    assertClose(policy.calculatePrice(atMinute(0), atMinute(500)), 7.5);
}

void testPaymentMachineUsesPricingPolicy() {
    auto policy = std::make_unique<HourlyPricingPolicy>(3.0, 2.0);
    PaymentMachine machine(std::move(policy));
    auto ticket = makeTicket(atMinute(0));

    assertClose(machine.calculatePrice(ticket, atMinute(61)), 5.0);
}
}

int main() {
    testHourlyPolicyReturnsZeroForNoDuration();
    testHourlyPolicyChargesFirstHour();
    testHourlyPolicyRoundsUpPartialHours();
    testFlatRatePolicyAlwaysReturnsSamePrice();
    testPaymentMachineUsesPricingPolicy();

    std::cout << "PaymentMachineTests passed\n";
    return 0;
}
