#include <iostream>
#include "list.hpp"
#include "static-list.hpp"


int main(int argc, char const *argv[]) {
    StaticList<int> static_list(10);
    List<int> *lists[] = {&static_list};
    for (auto list : lists)
        test_list(*list);
    
    return 0;
}
