#include "engine.h"
#include "core/base/macro.h"

#include <cassert>
#include <iostream>

int main()
{
    Untitled::UntitledEngine engine;

    engine.init("untitled.yml");
    engine.run();
    engine.shutdown();

    return 0;
}
