#pragma once

enum class BarrierState {
    Closed,
    Opening,
    Open,
    Closing,
    Error
};

class Barrier {
    public:
        void requestOpen();
        void close();
        BarrierState getState() const;
};