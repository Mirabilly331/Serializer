#include <iostream>
#include <iomanip>

#include "MTime.hpp"
#include "Signal.hpp"
#include "Quote.hpp"
#include "Trade.hpp"

void print_time(const MTime& M1)
{
    // std::cout << M1.microseconds_from_epoch() << std::endl;
    std::tuple<int, int, int, int, int, double> dateTime = M1.get_time();
    std::cout << std::get<0>(dateTime) << "-" << std::get<1>(dateTime) << "-" << std::get<2>(dateTime);
    std::cout << " " << std::get<3>(dateTime) << ":" << std::get<4>(dateTime) << ":";
    std::cout << std::fixed << std::get<5>(dateTime);
}


void print_signal(const Signal& S)
{
    std::tuple<MTime, std::string, double, int>  signal_data = S.get_data();
    
    print_time(std::get<0>(signal_data));
    
    std::cout << " ";
    std::cout << std::get<1>(signal_data) << " ";
    std::cout << std::get<2>(signal_data) << " ";
    std::cout << std::get<3>(signal_data);
    
    
}

void print_quote(const Quote& Q)
{
    std::tuple<MTime, std::string, double, double, int, int>  quote_data = Q.get_data();
    
    print_time(std::get<0>(quote_data));
    
    std::cout << " ";
    std::cout << std::get<1>(quote_data) << " ";
    std::cout << std::get<2>(quote_data) << " ";
    std::cout << std::get<3>(quote_data) << " ";
    std::cout << std::get<4>(quote_data) << " ";
    std::cout << std::get<5>(quote_data);
    
    
}

void print_trade(const Trade& T)
{
    std::tuple<MTime, std::string, double, char>  trade_data = T.get_data();
    
    print_time(std::get<0>(trade_data));
    
    std::cout << " ";
    std::cout << std::get<1>(trade_data) << " ";
    std::cout << std::get<2>(trade_data) << " ";
    std::cout << std::get<3>(trade_data) ;
}

void print_record(Serializable* R)
{
    MTime* pM = dynamic_cast<MTime*>(R);
    if(pM != nullptr)
    {
        print_time(*pM);
        std::cout << std::endl;
        return;
    }
    Signal* pS = dynamic_cast<Signal*>(R);
    if(pS != nullptr)
    {
        print_signal(*pS);
        std::cout << std::endl;
        return;
    }
    Quote* pQ = dynamic_cast<Quote*>(R);
    if(pQ != nullptr)
    {
        print_quote(*pQ);
        std::cout << std::endl;
        return;
    }
    Trade* pT = dynamic_cast<Trade*>(R);
    if(pT != nullptr)
    {
        print_trade(*pT);
        std::cout << std::endl;
        return;
    }
    throw std::runtime_error("print_record: Object not in table");
    
}

int main(int argc, const char * argv[])
{
    MTime M1(2016, 8, 14, 10, 52, 18.250125);
    MTime M2(2017, 9, 14, 11, 52, 9.12345);
    MTime M3(2013, 12, 30, 11, 52, 22.2222);
    MTime M4(2015, 9, 14, 11, 52, 9.12345);
    Signal S1(M1, "CSX", 18.36125, 1);
    Signal S2(M2, "MSFT", 77.1234, 2);
    
    Quote Q1(M3, "XOM", 101.23, 101.55, 1000, 12000);
    Trade T1(M4, "GOOG", 121.76767, 'X');
    
    std::ofstream ofs("test.bin", std::ofstream::out|std::ofstream::binary);
    S1.serialize(ofs);
    S2.serialize(ofs);
    Q1.serialize(ofs);
    T1.serialize(ofs);
    ofs.close();
    
    std::ifstream ifs("test.bin", std::ofstream::in|std::ofstream::binary);
    Record *pS1 = dynamic_cast<Record*>(Serializable::unserialize(ifs));
    Record *pS2 = dynamic_cast<Record*>(Serializable::unserialize(ifs));
    Record *pS3 = dynamic_cast<Record*>(Serializable::unserialize(ifs));
    Record *pS4 = dynamic_cast<Record*>(Serializable::unserialize(ifs));
    ifs.close();

    print_record(pS1);
    print_record(pS2);
    print_record(pS3);
    print_record(pS4);


    return 0;
}














