#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Computer
{
    int id;
    Computer *next;
};

std::vector<Computer *> net;

void addConnection(Computer *&head, int id)
{
    Computer *reset = head;

    while (head->next != nullptr)
        head = head->next;

    head->id = id;
    head->next = new Computer;
    head = head->next;

    head = reset;
}

void printCon(Computer *&node)
{
    Computer *temp = node;
    cout << "\n>>> Displaying Information for Node:\nConnection IDs: [";

    while (temp)
    {
        if (temp->id)
            if (temp->next->next == nullptr)
                cout << temp->id;
            else
                cout << temp->id << ", ";

        temp = temp->next;
    }
    cout << "]\n";
}

int main()
{
    Computer *ptr = new Computer;

    addConnection(ptr, 12);
    addConnection(ptr, 13);
    addConnection(ptr, 14);
    printCon(ptr);

    addConnection(ptr, 19);
    addConnection(ptr, 12);
    addConnection(ptr, 10);

    printCon(ptr);

    delete ptr;
}