//
//  Quote.hpp
//  TestBalls
//
//  Created by William Mirabella on 8/21/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#pragma once

#include "Record.hpp"

class Quote : public Record
{
public:
    
    Quote(std::istream& istr);
    Quote(const MTime& time,
          const std::string& symbol,
          const double ask_price,
          const double bid_price,
          const int bid_size,
          const int ask_size);
    
    void serialize(std::ostream& ostr) const;
    static Serializable* create(std::istream& istr);
    
    std::tuple<MTime, std::string, double, double, int, int> get_data() const;
    
private:
    std::string qt_symbol;
    double      qt_bid_price;
    double      qt_ask_price;
    int         qt_bid_size;
    int         qt_ask_size;
};