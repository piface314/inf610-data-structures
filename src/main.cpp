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
#include "stack/linked-stack.hpp"
#include "stack/double-stack.hpp"
#include "queue/static-queue.hpp"



void lists();
void stacks();
void double_stacks();
void queues();

int main(int argc, char const *argv[]) {
    // lists();
    // stacks();
    // double_stacks();
    queues();
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
    LinkedStack<char> linked_stack;
    Stack<char> *stacks[] = {
        &static_stack,
        &linked_stack
    };
    for (auto stack : stacks)
        test_stack(*stack);
}

void queues() {
    StaticQueue<char> static_queue(10);
    // LinkedQueue<char> linked_queue;
    Queue<char> *queues[] = {
        &static_queue,
        // &linked_queue
    };
    for (auto queue : queues)
        test_queue(*queue);
}

void double_stacks() {
    DoubleStack<char> stack(10);
    std::cout << stack << std::endl;
    
    std::cout << "Pushing left C, A, T, S:\n";
    stack.push('C');
    stack.push('A');
    stack.push('T');
    stack.push('S');
    std::cout << stack << std::endl;
    
    std::cout << "Popping left:\n";
    stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Pushing right M and Z:\n";
    stack.push_r('M');
    stack.push_r('Z');
    std::cout << stack << std::endl;

    std::cout << "Element at left top?:\n";
    std::cout << stack.peek() << std::endl;

    std::cout << "Element at right top?:\n";
    std::cout << stack.peek_r() << std::endl;

    std::cout << "Popping left 2:\n";
    stack.pop();
    stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Pushing right X, L, R:\n";
    stack.push_r('X');
    stack.push_r('L');
    stack.push_r('R');
    std::cout << stack << std::endl;

    std::cout << "Poping left all:\n";
    while (stack.size() > 0)
        stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Pushing left P and Q:\n";
    stack.push('P');
    stack.push('Q');
    std::cout << stack << std::endl;

    std::cout << "Pushing right K, H, B:\n";
    stack.push_r('K');
    stack.push_r('H');
    stack.push_r('B');
    std::cout << stack << std::endl;

    std::cout << "Element at right top?:\n";
    std::cout << stack.peek_r() << std::endl;

    std::cout << "Popping right 2:\n";
    stack.pop_r();
    stack.pop_r();
    std::cout << stack << std::endl;

    std::cout << std::endl;
}