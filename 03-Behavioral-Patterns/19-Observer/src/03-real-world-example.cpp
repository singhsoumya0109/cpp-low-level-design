#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

// Real-world: Stock Market Ticker Feed
struct StockQuote {
    std::string symbol;
    double price;
};

class IStockSubscriber {
public:
    virtual ~IStockSubscriber() = default;
    virtual void on_price_update(const StockQuote& quote) = 0;
};

class StockTickerExchange {
    std::unordered_map<std::string, std::vector<std::weak_ptr<IStockSubscriber>>> subscribers_;
public:
    void subscribe(const std::string& symbol, std::shared_ptr<IStockSubscriber> sub) {
        subscribers_[symbol].push_back(sub);
    }

    void publish_price(const std::string& symbol, double price) {
        StockQuote quote{symbol, price};
        auto it = subscribers_.find(symbol);
        if (it != subscribers_.end()) {
            for (auto sub_it = it->second.begin(); sub_it != it->second.end(); ) {
                if (auto s = sub_it->lock()) {
                    s->on_price_update(quote);
                    ++sub_it;
                } else {
                    sub_it = it->second.erase(sub_it);
                }
            }
        }
    }
};

class TradingBot : public IStockSubscriber {
    std::string id_;
    double buy_threshold_;
public:
    TradingBot(std::string id, double thresh) : id_(std::move(id)), buy_threshold_(thresh) {}
    void on_price_update(const StockQuote& quote) override {
        if (quote.price <= buy_threshold_) {
            std::cout << "[Bot " << id_ << "] BUY SIGNAL: " << quote.symbol << " @ $" << quote.price << "\n";
        }
    }
};

int main() {
    StockTickerExchange exchange;
    auto bot1 = std::make_shared<TradingBot>("Alpha", 150.0);
    auto bot2 = std::make_shared<TradingBot>("Beta", 140.0);

    exchange.subscribe("AAPL", bot1);
    exchange.subscribe("AAPL", bot2);

    std::cout << "Publishing AAPL price $145.00:\n";
    exchange.publish_price("AAPL", 145.00);

    std::cout << "\nPublishing AAPL price $135.00:\n";
    exchange.publish_price("AAPL", 135.00);
    return 0;
}
