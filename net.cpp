#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

/*

- A Computer Network is stored in the following format: an array, called net, of
pointers where each pointer is the head of a list.

- The list at index i contains the ids of all the computers to which computer i
is connected; the order of the ids in a list does not matter.

- A class which stores a network is defined below.
*/

class Network
{

  struct Computer
  {
    int id;
    Computer *next;
    // method to enable if(n[i][j]) cout<<"i and j are connected.
    bool operator[](int j);
  };

  // add id into the list pointed to by head
  std::vector<Computer *> net;

  void addConnection(Computer *&head, int id)
  {
    Computer *reset = head;

    while (head->next != nullptr)
      head = head->next;

    head->id = id;
    head->next = new Computer;
    head = head->next;
    head->next = nullptr;
    head = reset;
  }

public:
  Network() {}

  Network(std::string fn)
  {
    char temp[200];
    net.resize(3, nullptr); // Intitial size for vector
    std::ifstream fin(fn);
    int index = 0;

    while (fin >> index)
    {

      net[index] = new Computer;
      fin.getline(temp, 200, '\n');

      for (int i = 0; temp[i]; i++)
        if (temp[i] != ' ')
          addConnection(net[index], (temp[i] - 48));
    }
    fin.close();
  }

  Network(const Network &obj);

  const Network &operator=(const Network &obj);

  // create net array of size, with no connections
  Network(int size)
  {
    Computer cp;
    net.resize(size, nullptr);
  }

  // connect computers x and y
  // use the utility method addConnection
  void addConnection(int x, int y);

  // merge two networks (take union)
  // computers, connections in any one of the networks appear in result
  Network operator+(const Network &obj);

  // intersect two networks (extract the common core)
  // links and computers present in both networks appear in the result
  Network operator*(const Network &obj);
  // Remove the common connections of obj and this network

  // Remove the common connections of obj and this network
  Network operator-(const Network &obj);

  // Take complement of the Network
  // Returns a network with the same computers
  // but which contains complementary connections
  // resultant contains connections which are absent in this network
  Network operator-();

  friend std::ostream &operator<<(std::ostream &out, Network &obj);

  // method to enable if(n[i][j]) cout<<"i and j are connected.
  Computer &operator[](int i);

  // add another computer to the network
  Network operator++(int);

  // logical methods
  // subNetwork returns true if obj is a sub-network of this network
  bool subNetwork(const Network &obj);

  // get all neighbors of computer nid
  std::vector<int> getNeighbours(int nid);

  // get all unique neighbors-of-neighbors of computer nid
  std::vector<int> getNeighboursofNeighbours(int nid);

  // returns all computers in order of their number of neighbors
  // computer with most neighbors comes first and so on
  std::vector<int> orderOfDegree();

  // Suggest connection
  // Returns two unconnected computers with most common neighbors
  std::vector<int> suggestConnection();

  ~Network()
  {
    cout << "Helo";
    // for (int i = 0; i < net.size(); i++)
    // {
    // cout << "Deleting " << i << endl;
    // Computer *t1 = net[i];
    // Computer *temp = net[i];

    // while (t1->next)
    // {
    //   temp = t1->next;
    //   delete t1->next;
    //   t1->next = temp;
    // }
    // }
  }
};

std::ostream &operator<<(std::ostream &out, Network &obj)
{

  for (int i = 0; i < obj.net.size(); i++)
  {
    out << "\n>>> Displaying Information for Node [" << i
        << "]\nConnection IDs: [";

    if (obj.net[i])
    {

      while (obj.net[i])
      {

        if (obj.net[i]->next == nullptr)
          out << obj.net[i]->id;
        else
          out << obj.net[i]->id << ", ";

        obj.net[i] = obj.net[i]->next;
      }
    }
    out << "]\n";
  }

  return out;
}

int main()
{
  Network my_obj("testing.txt");
  cout << my_obj;
}