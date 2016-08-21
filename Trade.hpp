//
//  Trade.hpp
//  Serializer
//
//  Created by William Mirabella on 8/21/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#pragma once

#include "Record.hpp"

class Trade : public Record
{
public:
    
    Trade(std::istream& istr);
    Trade(const MTime& time,
          const std::string& symbol,
          const double price,
          const char condition);
    
    void serialize(std::ostream& ostr) const;
    static Serializable* create(std::istream& istr);
    
    std::tuple<MTime, std::string, double, char> get_data() const;
    
private:
    std::string tr_symbol;
    double      tr_price;
    char        tr_condition;
    
};