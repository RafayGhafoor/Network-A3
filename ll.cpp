#include <iostream>
using namespace std;

// Junaid's Work
class Node
{
  public:
    int id;
    Node *next;
};

class list
{
    Node *head;
    Node *tail;

  public:
    list()
    {
        head = nullptr;
        tail = nullptr;
    }
    Node *gethead() const { return head; }

    list(const list &obj)
    {
        Node *temp = head;
        Node *tempDel;
        while (temp != nullptr)
        {
            tempDel = temp;
            temp = temp->next;
            delete tempDel;
        }
        head = nullptr;
        tail = nullptr;
        temp = obj.gethead();
        while (temp != nullptr)
        {
            add(temp->id);
            temp = temp->next;
        }
    }

    void add(const int para);
    void print();
    ~list()
    {
        Node *temp = head;
        Node *tempDel;
        while (temp != nullptr)
        {
            tempDel = temp;
            temp = temp->next;
            delete tempDel;
        }
        head = nullptr;
        tail = nullptr;
    }
};
void list::print()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->id << " ";
        temp = temp->next;
    }
}
void list::add(const int para)
{
    Node *temp = new Node();
    temp->id = para;
    if (head == nullptr)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        Node *locator = head;
        while (locator->next != nullptr)
        {
            locator = locator->next;
        }
        locator->next = temp;
        tail = temp;
    }
}
int main()
{
    list obj, obj1;
    for (int i = 0; i < 10; i++)
    {
        obj.add(i + 1);
    }
    obj1 = obj;
    obj1.print();
    return 0;
}