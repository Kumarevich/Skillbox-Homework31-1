#include <iostream>

class Toy
{
    std::string name;
public:
    void print_name() {
        std::cout << name << std::endl;
    }

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
    void print_info() {
        std::cout << *count << std::endl;
        toy->print_name();
    }

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

    Shared_ptr_toy& operator = (const Shared_ptr_toy& other)
    {
        if (this == &other) return *this;
        if (toy != nullptr) this->toy = nullptr;
        --this->count;
        if (*count <= 0) delete this->toy;
        toy = other.toy;
        count = other.count;
        ++*count;
    }
};

Shared_ptr_toy* make_shared(std::string name)
{
    Shared_ptr_toy* ptr = new Shared_ptr_toy(new Toy(name));
    return ptr;
}

Shared_ptr_toy* make_shared(Toy* toy)
{
    Shared_ptr_toy* ptr = new Shared_ptr_toy(toy);
    return ptr;
}

Shared_ptr_toy* make_shared(Shared_ptr_toy& _ptr)
{
    Shared_ptr_toy* ptr = new Shared_ptr_toy(_ptr);
    return ptr;
}

int main() {
    Shared_ptr_toy* ptr1 = make_shared("Toy1");
    Toy* toy = new Toy("Toy2");
    Shared_ptr_toy* ptr2 = make_shared(toy);
    Shared_ptr_toy* ptr3 = make_shared(*ptr2);
    Shared_ptr_toy* ptr4 = make_shared("Toy3");
    ptr4->operator = (*ptr1);
    delete ptr1;
    ptr1 = nullptr;
    delete ptr2;
    ptr2 = nullptr;
    delete ptr3;
    ptr3 = nullptr;
    delete ptr4;
    ptr4 = nullptr;
    return 0;
}
