enum class Signal {
    Buy,
    Sell,
    Hold
};

class Strategy {
    protected:
        Strategy() = default;
    public:
        virtual ~Strategy() = default;
        virtual Signal generate_signal(int index) = 0;
};