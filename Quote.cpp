//
//  Quote.cpp
//  TestBalls
//
//  Created by William Mirabella on 8/21/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#include "Quote.hpp"


constexpr int mySerialID = 0x3;
static SerializerInitializer S(mySerialID, Quote::create);

Quote::Quote(const MTime& time,
             const std::string& symbol,
             const double bid_price,
             const double ask_price,
             const int bid_size,
             const int ask_size)
: Record(time),
  qt_symbol(symbol),
  qt_bid_price(bid_price),
  qt_ask_price(ask_price),
  qt_bid_size(bid_size),
  qt_ask_size(ask_size)
{
    
}

Quote::Quote(std::istream& istr)
{
    char line[16];
    memset(line, 0x0, 16);
    
    MTime* timex = dynamic_cast<MTime*>(Serializable::unserialize(istr));
    r_time = *timex;
    
    size_t symbol_length;
    istr.read((char *)(&symbol_length), sizeof(symbol_length));
    istr.read(line, symbol_length);
    qt_symbol = std::string(line);
    
    istr.read((char *)(&qt_bid_price), sizeof(qt_bid_price));
    istr.read((char *)(&qt_ask_price), sizeof(qt_ask_price));
    
    istr.read((char *)(&qt_bid_size), sizeof(qt_bid_size));
    istr.read((char *)(&qt_ask_size), sizeof(qt_ask_size));
    
}

void Quote::serialize(std::ostream& ostr)  const
{
    ostr.write((const char *)(&mySerialID), sizeof(mySerialID));
    
    r_time.serialize(ostr);
    
    size_t symbol_length = qt_symbol.length();
    ostr.write((const char *)(&symbol_length), sizeof(symbol_length));
    ostr.write((const char *)(qt_symbol.c_str()), symbol_length);
    
    ostr.write((const char *)(&qt_bid_price), sizeof(qt_bid_price));
    ostr.write((const char *)(&qt_ask_price), sizeof(qt_ask_price));
    
    ostr.write((const char *)(&qt_bid_size), sizeof(qt_bid_size));
    ostr.write((const char *)(&qt_ask_size), sizeof(qt_ask_size));
}


Serializable* Quote::create(std::istream& istr)
{
    return new Quote(istr);
}

std::tuple<MTime, std::string, double, double, int, int> Quote::get_data() const
{
    return std::tuple<MTime, std::string, double, double, int, int>(r_time,
                                                                    qt_symbol,
                                                                    qt_bid_price,
                                                                    qt_ask_price,
                                                                    qt_bid_size,
                                                                    qt_ask_size);
    
}


