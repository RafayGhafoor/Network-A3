#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream fin("testing.txt");

  int index = 0;
  char temp[200];
  int net[100];
  int x = 0;

  while (!fin.eof()) {
    fin.getline(temp, 200, '\n');

    for (int i = 0; temp[i] != 0; i++)
      if (temp[i] != ' ')
        net[x++] = temp[i] - 48;
  }

  for (int i = 0; i < 8; i++)
    cout << net[i] << " ";

  fin.close();
}