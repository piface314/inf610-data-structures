#include <iostream>
#include "list/list.hpp"
#include "list/static-list.hpp"
#include "list/static-link-list.hpp"
#include "list/linked-list.hpp"
#include "list/llinked-list.hpp"
#include "list/hlinked-list.hpp"
#include "list/dlinked-list.hpp"
#include "stack/stack.hpp"
#include "stack/static-stack.hpp"


void lists();
void stacks();

int main(int argc, char const *argv[]) {
    stacks();
    return 0;
}

void lists() {
    StaticList<char> static_list(10);
    StaticLinkList<char> static_link_list(10);
    LinkedList<char> linked_list;
    LLinkedList<char> llinked_list;
    HLinkedList<char> hlinked_list;
    DLinkedList<char> dlinked_list;
    List<char> *lists[] = {
        &static_list,
        &static_link_list,
        &linked_list,
        &llinked_list,
        &hlinked_list,
        &dlinked_list
    };
    for (auto list : lists)
        test_list(*list);
    
}

void stacks() {
    StaticStack<char> static_stack(10);
    Stack<char> *stacks[] = {
        &static_stack
    };
    for (auto stack : stacks)
        test_stack(*stack);
}