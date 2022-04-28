#include <iostream>

class Toy
{
    std::string name;
public:
    Toy(std::string _name) : name(_name) {};
    Toy(): Toy("RegularToy") {};
    Toy(const Toy& other) : Toy(other.name) {};
    Toy& operator = (const Toy& other)
    {
        if (this == &other) return *this;
        name = other.name;
        return *this;
    }
};

class Shared_ptr_toy
{
private:
    int* count;
    Toy* toy;

public:
    Shared_ptr_toy(Toy* t) : toy(t), count(new int)
    {
        *count = 1;
    }
    ~Shared_ptr_toy()
    {
        --*count;
        if (*count == 0)
        {
            delete toy;
            toy = nullptr;
            delete count;
            count = nullptr;
        }
    }

    Shared_ptr_toy(const Shared_ptr_toy& other)
    {
        count = other.count;
        toy = other.toy;
        ++*count;
    }
};



int main() {
    Shared_ptr_toy* ptr = new Shared_ptr_toy(new Toy());
    Shared_ptr_toy* ptr1 = new Shared_ptr_toy(*ptr);
    delete ptr;
    ptr = nullptr;
    delete ptr1;
    ptr1 = nullptr;
    return 0;
}
