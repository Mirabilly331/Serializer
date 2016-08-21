//
//  MTime.cpp
//  TestBalls
//
//  Created by William Mirabella on 8/13/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#include <stdexcept>
#include <iomanip>
#include <cmath>

#include "MTime.hpp"


constexpr int mySerialID = 0x1;
static SerializerInitializer S(mySerialID, MTime::create);

MTime::MTime() :  mt_microseconds(0) {  }

MTime::MTime(const int year,const int month,const int day,const int hour,const int minute,const double seconds)
{
    if(year < 1970)
        throw std::invalid_argument("MTime: year!");
    
    if((month < 1) || (month > 12))
        throw std::invalid_argument("MTime: month!");

    if((day < 1) || (day > 31))
        throw std::invalid_argument("MTime: day!");
    if((month == 2) && (day > 28))
        if( (year % 4 != 0) || (year % 100 == 0))
            throw std::invalid_argument("MTime: February date > 28, not a leap year!");
    if((day > 30) && ((month == 9) || (month == 4) || (month == 6) || (month == 11)) )
        throw std::invalid_argument("MTime: 31 day in 30 day month!");

    if( (hour < 0) || (hour > 24))
        throw std::invalid_argument("MTime: hour");
    
    if( (minute < 0) || (minute > 59))
        throw std::invalid_argument("MTime: minute");
    
    if( (seconds < 0) || (seconds > 59))
        throw std::invalid_argument("MTime: seconds");
    
    mt_microseconds = (days_from_civil(year, month, day) * 86400 + hour*3600.00 + minute* 60.00) * 1000000 + (seconds * 1000000);
}

Serializable* MTime::create(std::istream& istr)
{
    return new MTime(istr);
}

MTime::MTime(std::istream& istr)
{
    istr.read((char*)(&mt_microseconds), sizeof(mt_microseconds));
}

void MTime::serialize(std::ostream& ostr) const
{
    ostr.write((const char *)(&mySerialID), sizeof(mySerialID));
    ostr.write((const char *)(&mt_microseconds), sizeof(mt_microseconds));
}

long MTime::microseconds_from_epoch() const noexcept { return mt_microseconds; }

std::tuple<int, int, int, int, int, double>
MTime::get_time() const noexcept
{
    
    //First calculate the days and get the yyyy-mm-dd
    int leftover = static_cast<int>(mt_microseconds / 1000000);
    int days  = leftover / 86400;
    std::tuple<int, unsigned, unsigned> date = civil_from_days(days);
    
    leftover %= 86400;
    int hours = leftover / 3600;
    leftover %= 3600;
    int mins  = leftover / 60;
    leftover %= 60;
    double secs = leftover;
    double microseconds = static_cast<double>(mt_microseconds % 1000000);
    microseconds = microseconds / 1000000.0;
    secs += microseconds;

    return std::tuple<int, int, int, int, int, double>(std::get<0>(date),
                                                       std::get<1>(date),
                                                       std::get<2>(date),
                                                       hours,
                                                       mins,
                                                       secs);
}


// The following two functions courtesy of Howard Hinnant
// http://howardhinnant.github.io/date_algorithms.html

// Returns number of days since civil 1970-01-01.  Negative values indicate
//    days prior to 1970-01-01.
// Preconditions:  y-m-d represents a date in the civil (Gregorian) calendar
//                 m is in [1, 12]
//                 d is in [1, last_day_of_month(y, m)]
//                 y is "approximately" in
//                   [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
//                 Exact range of validity is:
//                 [civil_from_days(numeric_limits<Int>::min()),
//                  civil_from_days(numeric_limits<Int>::max()-719468)]
int MTime::days_from_civil(int y, unsigned m, unsigned d) const noexcept
{
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
                  "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<int>::digits >= 20,
                  "This algorithm has not been ported to a 16 bit signed integer");
    y -= m <= 2;
    const int era = (y >= 0 ? y : y-399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
    const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  // [0, 365]
    const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
    return era * 146097 + static_cast<int>(doe) - 719468;
}

// Returns year/month/day triple in civil calendar
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
std::tuple<int, unsigned, unsigned>
MTime::civil_from_days(int z) const noexcept
{
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
                  "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<int>::digits >= 20,
                  "This algorithm has not been ported to a 16 bit signed integer");
    z += 719468;
    const int era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
    const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
    const int y = static_cast<int>(yoe) + era * 400;
    const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
    const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
    const unsigned d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
    const unsigned m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
    return std::tuple<int, unsigned, unsigned>(y + (m <= 2), m, d);
}


    