enum class Signal {
    Buy,
    Sell,
    Hold
};

class Strategy {
    protected:
        Strategy() = default;
    public:
        virtual ~Strategy() = 0;
        virtual Signal generate_signal(int pos);
};