//
//  peir.h
//  OOP Homework Project
//
//  Created by Мирослав Николов on 17.06.15.
//  Copyright (c) 2015 г. Мирослав Николов. All rights reserved.
//

#ifndef __OOP_Homework_Project__peir__
#define __OOP_Homework_Project__peir__

#include <stdio.h>

template <typename T1, typename T2, typename T3>
struct peir {
public:
    peir()
    {
    }
    peir(T1 value1)
    {
        first = value1;
    }
    peir(T1 value1, T2 value2)
    {
        first = value1;
        second = value2;
    }
    peir(T1 value1, T2 value2, T3 value3)
    {
        first = value1;
        second = value2;
        third = value3;
    }
    T1 first;
    T2 second;
    T3 third;
};

#endif /* defined(__OOP_Homework_Project__peir__) */
