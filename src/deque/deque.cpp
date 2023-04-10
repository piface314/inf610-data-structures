#include "deque.hpp"

void test_deque(Deque<char> &deque) {
    std::cout << deque << std::endl;
    
    std::cout << "Enqueuing C, A, T, S at back:\n";
    deque.enqueue_back('C');
    deque.enqueue_back('A');
    deque.enqueue_back('T');
    deque.enqueue_back('S');
    std::cout << deque << std::endl;
    
    std::cout << "Dequeuing 1 from front:\n";
    deque.dequeue_front();
    std::cout << deque << std::endl;

    std::cout << "Enqueuing M and Z at front:\n";
    deque.enqueue_front('M');
    deque.enqueue_front('Z');
    std::cout << deque << std::endl;

    std::cout << "Element at front?:\n";
    std::cout << deque.peek_front() << std::endl;
    std::cout << "Element at back?:\n";
    std::cout << deque.peek_back() << std::endl;

    std::cout << "Dequeuing 2 from back:\n";
    deque.dequeue_back();
    deque.dequeue_back();
    std::cout << deque << std::endl;

    std::cout << "Enqueuing X, L, R, O, U, W, J alternated, front then back:\n";
    deque.enqueue_front('X');
    deque.enqueue_back('L');
    deque.enqueue_front('R');
    deque.enqueue_back('O');
    deque.enqueue_front('U');
    deque.enqueue_back('W');
    deque.enqueue_front('J');
    std::cout << deque << std::endl;

    std::cout << "Dequeuing 2 from front:\n";
    deque.dequeue_front();
    deque.dequeue_front();
    std::cout << deque << std::endl;

    std::cout << "Dequeuing all:\n";
    while (deque.size() > 0)
        deque.dequeue_back();
    std::cout << deque << std::endl;

    std::cout << "Enqueuing P and Q at front:\n";
    deque.enqueue_front('P');
    deque.enqueue_front('Q');
    std::cout << deque << std::endl;

    std::cout << std::endl;
}