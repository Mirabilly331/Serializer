//
//  Record.cpp
//  TestBalls
//
//  Created by William Mirabella on 8/15/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#include "Record.hpp"

Record::Record() { }

Record::Record(const MTime& mt)
{
    r_time = mt;
}

Record::~Record()  {}

const MTime& Record::get_time() const
{
    return r_time;
}




