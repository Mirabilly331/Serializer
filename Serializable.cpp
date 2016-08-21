//
//  Serializable.cpp
//  TestBalls
//
//  Created by William Mirabella on 8/14/16.
//  Copyright © 2016 Big Dick 6. All rights reserved.
//

#include <stdexcept>
#include <iostream>

#include "Serializable.hpp"


std::map<int, Serializable::Factory> Serializable::object_creation_map;

Serializable* Serializable::unserialize(std::istream& istr)
{
    int serial_id = 0;
    istr.read((char*)(&serial_id), sizeof(int));
    if(object_creation_map.count(serial_id) == 0)
        throw std::invalid_argument("object serial_id not in object_creation_map");
    
    return object_creation_map[serial_id](istr);
}

void Serializable::AddFactoryToMap(const int serialId, Serializable::Factory f)
{
    object_creation_map[serialId] = f;
}


SerializerInitializer::SerializerInitializer(const int serialId, Serializable::Factory f)
{
    Serializable::AddFactoryToMap(serialId, f);
}
