//
//  main.cpp
//  Emojibin
//
//  Created by macbook on 19.05.2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <iostream>

#include <iostream>
#include <cstring>
#include "translator.h"

int main ()
{
    translator translator;
    translator.make_input_buffer ();
    translator.translate ();
    translator.make_output_file ();
    system ("chmod 777 ./run");
    return 0;
}
