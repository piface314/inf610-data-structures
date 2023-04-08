#include <iostream>
#include "list.hpp"
#include "static-list.hpp"
#include "static-link-list.hpp"


int main(int argc, char const *argv[]) {
    StaticList<int> static_list(10);
    StaticLinkList<int> static_link_list(10);
    List<int> *lists[] = {&static_list, &static_link_list};
    for (auto list : lists)
        test_list(*list);
    
    return 0;
}
