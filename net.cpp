#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

/*

Homework [3]
- A Computer Network is stored in the following format: an array, called net, of
pointers where each pointer is the head of a list.

- The list at index i contains the ids of all the computers to which computer i
is connected; the order of the ids in a list does not matter.

- A class which stores a network is defined below.
*/

std::vector<int> extractNum(std::string line)
{
  std::vector<int> num_vec;
  std::stringstream buffer;
  int i = 0, num;

  while (line[i] != 0)
  {
    if (isdigit(line[i]))
      buffer << line[i];

    i++;

    if (line[i] == ' ' || line[i] == 0)
    {
      buffer >> num;
      buffer.clear();
      buffer.str("");
      if (num)
        num_vec.push_back(num);
      num = 0;
    }
  }
  return num_vec;
}

class Network
{

  struct Computer
  {
    int id;
    Computer *next;
    // method to enable if(n[i][j]) cout<<"i and j are connected.
    bool operator[](int j)
    {
      if (id == j)
        return 1;

      Computer *ptr = next;

      while (1)
      {
        if (ptr->id == j)
          return 1;

        ptr = ptr->next;

        if (!ptr)
          return 0;
      }
    }
  };

  // add id into the list pointed to by head
  std::vector<Computer *> net;

  void addConnection(Computer *&head, int id)
  {
    bool is_duplicate = false;
    Computer *temp = new Computer;
    temp->id = id;
    temp->next = nullptr;

    if (head == nullptr)
      head = temp;

    else
    {
      Computer *tracker = head;

      while (tracker->next != nullptr)
      {

        if (tracker->id == id || tracker->next->id == id)
        {
          is_duplicate = true;
          break;
        }

        tracker = tracker->next;
      }

      if (!is_duplicate)
        tracker->next = temp;
    }
  }

public:
  Network() {}

  // *:  FIX: getline, more than one digit in stream
  Network(std::string fn)
  {
    std::string temp;
    net.resize(10, nullptr); // Intitial size for vector
    std::ifstream fin(fn);
    int index = 0;

    while (fin >> index)
    {
      getline(fin, temp, '\n');
      // fin.getline(temp, '\n');
      std::vector<int> j = extractNum(temp);
      for (int i = 0; i < j.size(); i++)
        addConnection(net[index], j[i]);
    }
    fin.close();
  }

  Network(const Network &obj)
  {
    net.resize(obj.net.size(), nullptr);
    std::vector<Computer *> tmp = obj.net;
    for (int i = 0; i < tmp.size(); i++)
    {
      if (!tmp[i])
        continue;
      while (tmp[i])
      {
        addConnection(net[i], tmp[i]->id);
        tmp[i] = tmp[i]->next;
      }
    }
  }

  const Network &operator=(const Network &obj)
  {

    if (this != &obj)
    { // Self-assessment check
      for (int i = 0; i < net.size(); i++)
      {
        if (!net[i])
          continue;

        Computer *t1 = net[i], *temp = t1;

        while (t1)
        {
          temp = t1->next;
          delete t1;
          t1 = temp;
        }
        delete t1;
      }

      net.clear();
    }

    net.resize(obj.net.size(), nullptr);
    std::vector<Computer *> tmp = obj.net;
    for (int i = 0; i < tmp.size(); i++)
    {
      if (!tmp[i])
        continue;
      while (tmp[i])
      {
        addConnection(net[i], tmp[i]->id);
        tmp[i] = tmp[i]->next;
      }
    }

    return *this;
  }

  // create net array of size, with no connections
  Network(int size)
  {
    net.resize(size, nullptr);
  }

  // connect computers x and y
  // use the utility method addConnection
  void addConnection(int x, int y)
  {
    Computer *link1 = net[x], *link2 = net[y];

    while (link2)
    {
      addConnection(link1, link2->id);
      link2 = link2->next;
    }

    link2 = net[y]; // reset link2 node pointer

    while (link1)
    {
      addConnection(link2, link1->id);
      link1 = link1->next;
    }
  }

  // merge two networks (take union)
  // computers, connections in any one of the networks appear in result
  Network operator+(const Network &obj)
  {
    int threshold = obj.net.size(), init_size = net.size();

    if (init_size > threshold)
      threshold = init_size;

    for (int i = 0; i < threshold; i++)
    {
      Computer *def = obj.net[i];
      while (def)
      {
        addConnection(net[i], def->id);
        def = def->next;
      }
    }
    cout << *this;

    return *this;
  }

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
  Computer &operator[](int i) { return *net[i]; }

  // add another computer to the network
  Network operator++(int)
  {
    net.resize(net.size() + 1, nullptr);
    return *this;
  }

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
    for (int i = 0; i < net.size(); i++)
    {
      if (!net[i])
        continue;

      Computer *t1 = net[i], *temp;

      while (t1)
      {

        temp = t1->next;
        delete t1;
        t1 = temp;
      }

      delete t1;
    }
    net.clear();
  }
};

std::ostream &operator<<(std::ostream &out, Network &obj)
{
  const int SIZE = obj.net.size();
  printf("| Displaying Information For Nodes (%d - %d) |\n", 0, SIZE - 1);

  for (int i = 0; i < SIZE; i++)
  {
    if (!obj.net[i])
    {
      out << "\n>>> Node No. [" << i << "] is empty\n";
      continue;
    }

    out << "\n>>> Node No. [" << i << "]\nConnection IDs: [";
    while (obj.net[i])
    {
      if (obj.net[i]->next == nullptr)
        out << obj.net[i]->id;

      else
        out << obj.net[i]->id << ", ";

      obj.net[i] = obj.net[i]->next;
    }

    out << "]\n";
  }

  out << endl;
  return out;
}

int main()
{
  Network my_obj("testing.txt"), obj1("testing1.txt");
  Network test = my_obj + obj1;
  // cout << test;
}
