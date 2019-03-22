#include <iostream>

using namespace std;

struct Computer {
  int id;
  Computer *next;
};

void addConnection(Computer *&head, int id) {
  Computer *temp = head;

  while (head->next)
    head = head->next;

  head->next = new Computer;
  head->next->next = nullptr;
  head->id = id;
  head = temp;
}

void print(Computer *&head) {
  Computer *temp = head;
  cout << "IDS: \n";
  while (head->next) {
    cout << head->id << " ";
    head = head->next;
  }
  head = temp;
}
int main() {
  Computer *ptr = new Computer;
  addConnection(ptr, 3);
  addConnection(ptr, 23);
  addConnection(ptr, 10);

  print(ptr);
  return 0;
}