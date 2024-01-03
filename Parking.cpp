#include <iostream>
#include <deque>
#include <stack>
#include <string>
#include <sstream>

class Car {
public:
    Car(int id, std::string license) : id(id), license(license), moves(0) {}

    int id;
    std::string license;
    int moves;
};

class Garage {
private:
    std::deque<Car*> garage;
    int idCount = 1;
public:
    void arrive(std::string license) {
        if (garage.size() == 10) {
            std::cout << "Garage is full. Car " << license << " leaves.\n";
            return;
        }

        Car* car = new Car(idCount++, license);
        garage.push_back(car);
        std::cout << "Car " << license << " arrives.\n";
    }

    void depart(std::string license) {
        std::deque<Car*>::iterator it = garage.begin();
        std::stack<Car*> stack;

        for (; it != garage.end(); ++it) {
            if ((*it)->license == license)
                break;

            stack.push(*it);
        }

        if (it == garage.end()) {
            std::cout << "Car " << license << " cannot depart, not found in garage.\n";
            return;
        }

        Car* car = *it;
        garage.erase(it);

        while (!stack.empty()) {
            stack.top()->moves++;
            garage.push_front(stack.top());
            stack.pop();
        }

        std::cout << "Car " << license << " departs, moved " << car->moves + 1 << " times.\n";
        delete car;
    }
};

void get_input_vals(const std::string &line, char &xact_type, std::string &license) {
    std::stringstream ss(line);
    std::string temp;

    std::getline(ss, temp, ':');
    xact_type = temp[0];

    std::getline(ss, temp, ':');
    license = temp;
}

int main() {
    Garage garage;
    std::string line;

    while (std::getline(std::cin, line)) {
        char xact_type;
        std::string license;
        get_input_vals(line, xact_type, license);

        if (xact_type == 'A')
            garage.arrive(license);
        else if (xact_type == 'D')
            garage.depart(license);
        else
            std::cout << "Invalid transaction type: " << xact_type << '\n';
    }

    return 0;
}