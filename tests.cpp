#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Computer {
  int id;
  Computer *next;
};

std::vector<Computer *> net;

void addConnection(Computer *&head, int id) {

  while (head)
    head = head->next; // Reach last node

  head = new Computer;
  head->id = id;
  head->next = nullptr;
}

void printCon(Computer *&node) {
  while (node) {
    cout << "Connection ID: " << node->id << endl;
    node = node->next;
  }
}

int main() {
  Computer *ptr = new Computer, *tracker = ptr;
  addConnection(ptr, 12);
  addConnection(ptr, 13);
  addConnection(ptr, 14);
  printCon(ptr);
  delete ptr;
}