//
//  Record.hpp
//  TestBalls
//
//  Created by William Mirabella on 8/15/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#pragma once

#include <tuple>

#include "Serializable.hpp"
#include "MTime.hpp"

class Record : public Serializable
{
public:
    Record();
    Record(const MTime& mt);
    
    virtual ~Record();
    
    const MTime& get_time() const;
    
    // virtual const MTime& get_data() const;
    
protected:
    MTime r_time;
    
};


