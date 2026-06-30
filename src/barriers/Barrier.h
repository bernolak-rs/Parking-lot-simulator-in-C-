#pragma once

enum class BarrierState {
    Closed,
    Opening,
    Open,
    Closing,
    Error
};

class Barrier {
    private:
        BarrierState state;

    public:
        Barrier() : state(BarrierState::Closed) {};
        bool requestOpen();
        bool close();
        BarrierState getState() const { return this->state; };
};