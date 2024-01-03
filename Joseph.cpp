#include<iostream>
#include<algorithm> // <--- Add this line
#include<list>
#include<iterator>
#include<string>

class SEQ {
    int i;
public:
    SEQ(int n): i(n) {}
    int operator()() {
        return i++;
    }
};

void print_underlined_string(const std::string &message) {
    std::cout << message << std::endl;
    std::cout << std::string(message.size(),'-') << std::endl;
}

void print_list(const std::list<int> &collection, const unsigned &eliminations, int num_cols) {
    std::string message;
    if(eliminations == 0)
        message = "Initial group of people";
    else
        message = "After eliminating " + std::to_string(eliminations) + " people";
    print_underlined_string(message);
    int col = 0;
    for(int id: collection) {
        std::cout << id << ' ';
        if(++col % num_cols == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    int N = 41, M = 3, print_freq = 13, num_cols = 12;
    std::list<int> people;
    std::generate_n(std::back_inserter(people), N, SEQ(1));
    auto it = people.begin();
    int eliminations = 0;
    print_list(people, eliminations, num_cols);
    while(people.size() > 1) {
        for(int i = 0; i < M; i++) {
            it++;
            if(it == people.end()) it = people.begin(); // loop back to start if reached end
        }
        it = people.erase(it);
        if(it == people.end()) it = people.begin(); // loop back to start if reached end
        if(++eliminations % print_freq == 0)
            print_list(people, eliminations, num_cols);
    }
    print_list(people, eliminations, num_cols);
    return 0;
}