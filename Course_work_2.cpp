#include "interface.hpp"

int main()
{
    query *q = new query();
    function* func = new function(q);
    interface i = interface(func);
    i.start_programm();
    return 0;
}
