//Hannah, Emma, Lindsey
//Vertex class 

#include "list.h"
#include <climits>
using namespace std;

class Vertex
{
public:
  int id;
  Vertex* pred;
  List<Vertex> adj_list;
  char color;
  int disc;
  int fin;
  int key;

  bool    operator<     (const Vertex &x) {return this->key <= x.key;}
  bool    operator>     (const Vertex &x) {return this->key > x.key;}
  bool    operator==    (const Vertex &x) {return this->id == x.id;}

  Vertex& operator= (const Vertex& v);

          Vertex        (int name);
          Vertex        (Vertex* v);
          ~Vertex       (void);
private:
  friend ostream& operator<< (ostream& os, const Vertex& v)
  {
    os << "Vertex ID: " << v.id << endl;
    return os;
  }
};

Vertex::Vertex(int name)
{
  id = name;
  pred = NULL;
  color = 'w';
  disc = INT_MAX;
  fin = 0;
  key = INT_MAX;
}

Vertex::Vertex(Vertex* v)
{
  id = v->id;
  pred = v->pred;
  adj_list = v->adj_list;
  color = v->color;
  disc = v->disc;
  fin = v->fin;
}

Vertex::~Vertex ()
{
}

Vertex& Vertex::operator= (const Vertex& v)
{
  this->id = v.id;
  this->pred = v.pred;
  this->adj_list = v.adj_list;
  this->color = v.color;
  this->disc = v.disc;
  this->fin = v.fin;

  return *this;
}

class Edge
{
public:
  int u;    //start Vertex
  int v;    //end Vertex
  int weight;     //weight (u,v)

  Edge()
  {
    u = -1;
    v = -1;
    weight = 0;
  }

  ~Edge()
  {
  }
};
