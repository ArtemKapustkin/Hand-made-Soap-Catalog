#include "interface.hpp"
#if _MSC_VER >= 1932
#    pragma comment(linker, "/alternatename:__imp___std_init_once_complete=__imp_InitOnceComplete")
#    pragma comment(linker, "/alternatename:__imp___std_init_once_begin_initialize=__imp_InitOnceBeginInitialize")
#endif
int main()
{
    query *q = new query();
    function* func = new function(q);
    interface i = interface(func);
    i.start_programm();
    return 0;
}
