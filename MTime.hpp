//
//  MTime.hpp
//  TestBalls
//
//  Created by William Mirabella on 8/13/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//
#pragma once

#include <tuple>
#include "Serializable.hpp"

class MTime : public Serializable
{
public:
    MTime();
    MTime(const int year,const int month,const int day,const int hour,const int minute,const double seconds);
    
    long microseconds_from_epoch() const noexcept;
    std::tuple<int, int, int, int, int, double> get_time() const noexcept;
    
    void serialize(std::ostream& ostr) const;
    static Serializable* create(std::istream& istr);
    
private:
    
    MTime(std::istream& istr);
    
    long mt_microseconds;
    
    int days_from_civil(int y, unsigned m, unsigned d) const noexcept;
    std::tuple<int, unsigned, unsigned>civil_from_days(int z) const noexcept;
    
};
