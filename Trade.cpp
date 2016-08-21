//
//  Trade.cpp
//  Serializer
//
//  Created by William Mirabella on 8/21/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#include "Trade.hpp"


constexpr int mySerialID = 0x4;
static SerializerInitializer S(mySerialID, Trade::create);

Trade::Trade(const MTime& time,
               const std::string& symbol,
               const double price,
               const char condition)
:   Record(time),
    tr_symbol(symbol),
    tr_price(price),
    tr_condition(condition)
{
    
}

Trade::Trade(std::istream& istr)
{
    char line[16];
    memset(line, 0x0, 16);
    
    MTime* timex = dynamic_cast<MTime*>(Serializable::unserialize(istr));
    r_time = *timex;
    
    size_t symbol_length;
    istr.read((char *)(&symbol_length), sizeof(symbol_length));
    istr.read(line, symbol_length);
    tr_symbol = std::string(line);
    
    istr.read((char *)(&tr_price), sizeof(tr_price));
    istr.read((char *)(&tr_condition), sizeof(tr_condition));
}

void Trade::serialize(std::ostream& ostr)  const
{
    ostr.write((const char *)(&mySerialID), sizeof(mySerialID));
    
    r_time.serialize(ostr);
    
    size_t symbol_length = tr_symbol.length();
    ostr.write((const char *)(&symbol_length), sizeof(symbol_length));
    ostr.write((const char *)(tr_symbol.c_str()), symbol_length);
    
    ostr.write((const char *)(&tr_price), sizeof(tr_price));
    ostr.write((const char *)(&tr_condition), sizeof(tr_condition));
}

Serializable* Trade::create(std::istream& istr)
{
    return new Trade(istr);
}

std::tuple<MTime, std::string, double, char> Trade::get_data() const
{
    return std::tuple<MTime, std::string, double, int>(r_time, tr_symbol, tr_price, tr_condition);
}
