//
//  Signal.cpp
//  TestBalls
//
//  Created by William Mirabella on 8/21/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#include "Signal.hpp"

constexpr int mySerialID = 0x2;
static SerializerInitializer S(mySerialID, Signal::create);

Signal::Signal(const MTime& time,
               const std::string& symbol,
               const double price,
               const int code)
: Record(time),
  sg_symbol(symbol),
  sg_price(price),
  sg_code(code)
{
    
}

Signal::Signal(std::istream& istr)
{
    char line[16];
    memset(line, 0x0, 16);
    
    MTime* timex = dynamic_cast<MTime*>(Serializable::unserialize(istr));
    r_time = *timex;
    
    size_t symbol_length;
    istr.read((char *)(&symbol_length), sizeof(symbol_length));
    istr.read(line, symbol_length);
    sg_symbol = std::string(line);
    
    istr.read((char *)(&sg_price), sizeof(sg_price));
    istr.read((char *)(&sg_code), sizeof(sg_code));
}

void Signal::serialize(std::ostream& ostr)  const
{
    ostr.write((const char *)(&mySerialID), sizeof(mySerialID));
    
    r_time.serialize(ostr);
    
    size_t symbol_length = sg_symbol.length();
    ostr.write((const char *)(&symbol_length), sizeof(symbol_length));
    ostr.write((const char *)(sg_symbol.c_str()), symbol_length);
    
    ostr.write((const char *)(&sg_price), sizeof(sg_price));
    ostr.write((const char *)(&sg_code), sizeof(sg_code));
}

Serializable* Signal::create(std::istream& istr)
{
    return new Signal(istr);
}

std::tuple<MTime, std::string, double, int> Signal::get_data() const
{
    return std::tuple<MTime, std::string, double, int>(r_time, sg_symbol, sg_price, sg_code);
}





