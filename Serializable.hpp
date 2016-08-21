//
//  Serializable.hpp
//  TestBalls
//
//  Created by William Mirabella on 8/14/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#pragma once

#include <fstream>
#include <map>

class Serializable
{
public:
    
    virtual void serialize(std::ostream& ostr) const = 0;
    
    typedef Serializable* (*Factory)(std::istream&);
    
    static Serializable* unserialize(std::istream& istr);
    
    static void AddFactoryToMap(const int serialId, Serializable::Factory f);
    
    
private:
    static std::map<int, Factory> object_creation_map;
    
};

class SerializerInitializer
{
public:
    SerializerInitializer(const int serialId, Serializable::Factory f);
};

