#include "queue.hpp"

void test_queue(Queue<char> &queue) {
    std::cout << queue << std::endl;
    
    std::cout << "Enqueuing C, A, T, S:\n";
    queue.enqueue('C');
    queue.enqueue('A');
    queue.enqueue('T');
    queue.enqueue('S');
    std::cout << queue << std::endl;
    
    std::cout << "Dequeuing 1:\n";
    queue.dequeue();
    std::cout << queue << std::endl;

    std::cout << "Enqueuing M and Z:\n";
    queue.enqueue('M');
    queue.enqueue('Z');
    std::cout << queue << std::endl;

    std::cout << "Element at front?:\n";
    std::cout << queue.peek() << std::endl;

    std::cout << "Dequeuing 2:\n";
    queue.dequeue();
    queue.dequeue();
    std::cout << queue << std::endl;

    std::cout << "Enqueuing X, L, R, O, U, W, J:\n";
    queue.enqueue('X');
    queue.enqueue('L');
    queue.enqueue('R');
    queue.enqueue('O');
    queue.enqueue('U');
    queue.enqueue('W');
    queue.enqueue('J');
    std::cout << queue << std::endl;

    std::cout << "Dequeuing 2:\n";
    queue.dequeue();
    queue.dequeue();
    std::cout << queue << std::endl;

    std::cout << "Dequeuing all:\n";
    while (queue.size() > 0)
        queue.dequeue();
    std::cout << queue << std::endl;

    std::cout << "Enqueuing P and Q:\n";
    queue.enqueue('P');
    queue.enqueue('Q');
    std::cout << queue << std::endl;

    std::cout << std::endl;
}