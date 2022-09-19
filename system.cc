#include "system.h"
#include <iostream>

__BEGIN_API

void System::init() {
    db<CPU>(TRC)<<"System::init()\n";
    setvbuf(stdout, 0, _IONBF, 0);
}

__END_API