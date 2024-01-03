#include <queue>
#include <iostream>

template<typename T>
class Stack
{
private:
    std::queue<T> q1; // These queues are where the stack's elements 
    std::queue<T> q2; // are to be saved.

public:
    bool empty() const {
        return q1.empty() && q2.empty();
    }

    int size() const {
        return q1.size() + q2.size();
    }

    const T& top() {
        if(q2.empty()){
            while(!q1.empty()){
                T element = q1.front();
                q1.pop();
                q2.push(element);
            }
        }
        return q2.back();
    }
    
    void push(const T &val) {
        q1.push(val);
    }

    void pop() {
        if(q2.empty()){
            while(!q1.empty()){
                T element = q1.front();
                q1.pop();
                if(!q1.empty())
                    q2.push(element);
            }
        } else {
            q2.pop();
        }
    }
};

int main() {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Top element: " << stack.top() << std::endl;
    stack.pop();
    std::cout << "Top element after pop: " << stack.top() << std::endl;
    std::cout << "Size of the stack: " << stack.size() << std::endl;
    std::cout << "Is the stack empty: " << (stack.empty() ? "Yes" : "No") << std::endl;

    return 0;
}