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
    if (head->next == nullptr)
    {
        head->id = id;
        head->next = new Computer;
        head = head->next;
    }
    else
        cout << "Node not at the end!\n";
}

void printCon(Computer *&node)
{
    Computer *temp = node;
    cout << "\nDisplaying Information for Node:\nConnection IDs: [";

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
    Computer *tracker = ptr;

    addConnection(ptr, 12);
    addConnection(ptr, 13);
    addConnection(ptr, 14);
    printCon(tracker);
    printCon(tracker);

    delete ptr;
}