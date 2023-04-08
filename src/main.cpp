#include <iostream>
#include "list.hpp"
#include "static-list.hpp"
#include "static-link-list.hpp"
#include "linked-list.hpp"
#include "llinked-list.hpp"
#include "hlinked-list.hpp"


int main(int argc, char const *argv[]) {
    StaticList<char> static_list(10);
    StaticLinkList<char> static_link_list(10);
    LinkedList<char> linked_list;
    LLinkedList<char> llinked_list;
    HLinkedList<char> hlinked_list;
    List<char> *lists[] = {
        &static_list,
        &static_link_list,
        &linked_list,
        &llinked_list,
        &hlinked_list
    };
    for (auto list : lists)
        test_list(*list);
    
    return 0;
}
