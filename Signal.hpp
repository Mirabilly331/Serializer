//
//  Signal.hpp
//  TestBalls
//
//  Created by William Mirabella on 8/21/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#pragma once

#include "Record.hpp"

class Signal : public Record
{
public:
    
    Signal(std::istream& istr);
    Signal(const MTime& time,
           const std::string& symbol,
           const double price,
           const int code);
    
    void serialize(std::ostream& ostr) const;
    static Serializable* create(std::istream& istr);
    
    std::tuple<MTime, std::string, double, int> get_data() const;
    
private:
    std::string sg_symbol;
    double      sg_price;
    int         sg_code;
    
};