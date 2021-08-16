//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "BoostGraphLibrary.h"
#include <tuple>

#include "boost/pending/indirect_cmp.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "boost/graph/kruskal_min_spanning_tree.hpp"
#include "boost\graph\topological_sort.hpp"


using namespace std;
using namespace XFU;
using namespace boost;



UndirectedGraph XFU::create_undirected_graph()
{
   UndirectedGraph g;
   add_edge(0,1,g);
   add_edge(0,3,g);
   add_edge(1,2,g);
   add_edge(2,3,g);

   UndirectedGraph::vertex_iterator vertexIt, vertexEnd;
   UndirectedGraph::adjacency_iterator neighbourIt, neighbourEnd;

   std::tie(vertexIt,vertexEnd) = vertices(g);
   for (; vertexIt!=vertexEnd; vertexIt++)
   {
      cout << *vertexIt << " is connected with "; 
      std::tie(neighbourIt,neighbourEnd) = adjacent_vertices(*vertexIt,g); 
      for (; neighbourIt!=neighbourEnd; neighbourIt++) 
         cout << *neighbourIt << " "; 
      cout << "\n"; 
   }

   return g;
}

DirectedGraph XFU::create_directed_graph()
{
   DirectedGraph g;
   add_edge(0,1,g);
   add_edge(0,3,g);
   add_edge(1,2,g);
   add_edge(2,3,g);

   DirectedGraph::vertex_iterator vertexIt, vertexEnd;
   DirectedGraph::out_edge_iterator outedgeIt, outedgeEnd;

   std::tie(vertexIt,vertexEnd) = vertices(g);
   for (; vertexIt!=vertexEnd; vertexIt++)
   {
      cout << "outgoing edges for " << *vertexIt << ": ";
      std::tie(outedgeIt,outedgeEnd) = out_edges(*vertexIt,g);
      for(; outedgeIt!=outedgeEnd; outedgeIt++)
      { 
         cout << *outedgeIt << " ";
      }
      cout << "\n";
   }

   return g;
}

EdgeWeightGraph XFU::create_directed_edge_weight_graph()
{
   EdgeWeightGraph g;
   add_edge(0,1,8,g);
   add_edge(0,3,18,g);
   add_edge(1,2,20,g);
   add_edge(2,3,2,g);

   return g;
}

BidirectedGraph XFU::create_bidirected_graph()
{
   BidirectedGraph g;
   add_edge(0,1,g);
   add_edge(0,3,g);
   add_edge(1,2,g);
   add_edge(2,3,g);

   BidirectedGraph::vertex_iterator vertexIt, vertexEnd;
   BidirectedGraph::in_edge_iterator inedgeIt, inedgeEnd;
   BidirectedGraph::out_edge_iterator outedgeIt, outedgeEnd;

   std::tie(vertexIt,vertexEnd) = vertices(g);
   for (; vertexIt!=vertexEnd; vertexIt++)
   {
      cout << "incoming edges for " << *vertexIt << ": ";
      std::tie(inedgeIt,inedgeEnd) = in_edges(*vertexIt,g);
      for(; inedgeIt!=inedgeEnd; inedgeIt++)
      { 
         cout << source(*inedgeIt,g) << "-->" << target(*inedgeIt,g) << " ";
      }
      cout << "\n";

      cout << "outgoing edges for " << *vertexIt << ": ";
      std::tie(outedgeIt,outedgeEnd) = out_edges(*vertexIt,g);
      for(; outedgeIt!=outedgeEnd; outedgeIt++)
      { 
         cout << source(*outedgeIt,g) << "-->" << target(*outedgeIt,g) << " ";
      }
      cout << "\n";
   }
   return g;
}



MyGraph XFU::create_my_graph()
{
   //https://www.youtube.com/watch?v=bIA8HEEUxZI
   //B--------F
   //| \      | \        
   //|  \     |  \       
   //|   \    |   C      
   //|    A   |   |      
   //E    |\  |   H
   // \   | \ |
   //  \  |  \|
   //   \ |   D
   //    \|
   //     G

   enum : int {A,B,C,D,E,F,G,H};

   const string name[] = {"A","B","C","D","E","F","G","H"};
   
   

   MyGraph g;
   //boost::property_map<MyGraph,size_t VertexProperty::*>::type getidx = get(&VertexProperty::_index,g);
   //boost::property_map<MyGraph,string VertexProperty::*>::type getname = get(&VertexProperty::_name,g);


   MyVertex va = add_vertex(VertexProperty(A,name[A]),g);
   MyVertex vb = add_vertex(VertexProperty(B,name[B]),g);
   MyVertex vc = add_vertex(VertexProperty(C,name[C]),g);
   MyVertex vd = add_vertex(VertexProperty(D,name[D]),g);
   MyVertex ve = add_vertex(VertexProperty(E,name[E]),g);
   MyVertex vf = add_vertex(VertexProperty(F,name[F]),g);
   MyVertex vg = add_vertex(VertexProperty(G,name[G]),g);
   MyVertex vh = add_vertex(VertexProperty(H,name[H]),g);


   add_edge(va,vb,g);
   add_edge(va,vd,g);
   add_edge(va,vg,g);
   add_edge(vb,ve,g);
   add_edge(vb,vf,g);
   add_edge(vc,vf,g);
   add_edge(vc,vh,g);
   add_edge(vd,vf,g);
   add_edge(ve,vg,g);

   return g;
}

string XFU::dfs()
{
   string order;

   MyGraph& g = create_my_graph();
   size_t N = num_vertices(g);

   // a vector to hold the discover time property for each vertex
   vector<MySize> dtime(N);
   MySize time = 0;
   DFSVisitor<MySize*> vis(&dtime[0],time);
   depth_first_search(g,visitor(vis));

   for (size_t i=0; i<N; i++)
   {
      //cout << dtime[i] << g[dtime[i]]._name << " ";
   }

   // use std::sort to order the vertices by their discover time
   vector<MySize> discover_order(N);
   integer_range<size_t> range(0,N);
   copy(range.begin(),range.end(),discover_order.begin());
   sort(discover_order.begin(),discover_order.end(),indirect_cmp<MySize*,less<MySize>>(&dtime[0]));

   for (size_t i=0; i<N; i++)
   {
      cout << discover_order[i] << g[discover_order[i]]._name << " ";
      order += g[discover_order[i]]._name;
   }
   cout << endl;

   return order;
}


string XFU::bfs()
{
   string order;

   MyGraph& g = create_my_graph();
   size_t N = num_vertices(g);

   // a vector to hold the discover time property for each vertex
   vector<MySize> dtime(N);
   MySize time = 0;
   BFSVisitor<MySize*> vis(&dtime[0],time);
   breadth_first_search(g,0,visitor(vis));

   
   for (size_t i=0; i<N; i++)
   {
      //cout << dtime[i] << g[dtime[i]]._name << " ";
   }

   // use std::sort to order the vertices by their discover time
   vector<MySize> discover_order(N);
   integer_range<size_t> range(0,N);
   copy(range.begin(),range.end(),discover_order.begin());
   sort(discover_order.begin(),discover_order.end(),indirect_cmp<MySize*,less<MySize>>(&dtime[0]));

   for (size_t i=0; i<N; i++)
   {
      cout << discover_order[i] << g[discover_order[i]]._name << " ";
      order += g[discover_order[i]]._name;
   }
   cout << endl;

   return order;
}



std::vector<size_t> XFU::dijkstra()
{
  //https://www.youtube.com/watch?v=8Ls1RqHCOPw
  //The time complexity is O(n^2).

  typedef graph_traits<DirectedEdgeWeightGraph>::vertex_descriptor vertex_descriptor;
  typedef std::pair<int, int> Edge;

  enum nodes {A, B, C, D, E, F, G, H, NUM};
  char name[] = "ABCDEFGH";
  Edge edge_array[] = { Edge(A,B), Edge(A,D), Edge(A,G), Edge(B,F), Edge(C,D), Edge(C,F), Edge(C,H),
     Edge(D,C), Edge(D,G), Edge(E,B), Edge(E,G), Edge(F,C), Edge(F,D), Edge(G,A)};
  int weights[] = {20, 80, 90, 10, 10, 50, 20, 10, 20, 50, 30, 10, 40, 20};
  int num_arcs = sizeof(edge_array) / sizeof(Edge);
  DirectedEdgeWeightGraph g(edge_array, edge_array + num_arcs, weights, NUM);
  property_map<DirectedEdgeWeightGraph, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<vertex_descriptor> d(num_vertices(g));
  vertex_descriptor a = vertex(A, g);

  dijkstra_shortest_paths(g, a,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

  std::cout << "distances and parents:" << std::endl;
  graph_traits < DirectedEdgeWeightGraph >::vertex_iterator vi, vend;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi)
  {
    std::cout << "distance(" << name[*vi] << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << std::endl;
  }
  std::cout << std::endl;

  return d;
}

int XFU::kruskal()
{
   //https://www.youtube.com/watch?v=GJ17vvqY6aE

   int sweight = 0;
   typedef graph_traits<EdgeWeightGraph>::edge_descriptor EdgeDescriptor;
   typedef std::pair<int, int> Edge;

   enum nodes {A, B, C, D, E, F, G, H, NUM};
   char name[] = "ABCDEFGH";
   Edge edge_array[] = { Edge(A,B), Edge(A,C), Edge(A,D), Edge(B,D), Edge(B,F), Edge(C,D), Edge(C,F),
      Edge(D,E), Edge(D,F), Edge(D,G), Edge(D,H), Edge(E,H), Edge(F,G), Edge(G,H)};
   int weights[] = {4, 3, 5, 3, 6, 2, 8, 5, 6, 5, 7, 6, 4, 2};

   EdgeWeightGraph g(edge_array,edge_array+_countof(edge_array),weights,NUM);
   property_map<EdgeWeightGraph, edge_weight_t>::type weightmap = get(edge_weight,g);
   vector<EdgeDescriptor> tree;

   kruskal_minimum_spanning_tree(g,std::back_inserter(tree));

   cout << "Print the edges in the MST:" << endl;
   for(vector<EdgeDescriptor>::iterator ei=tree.begin(); ei!=tree.end(); ei++)
   {
      cout << name[source(*ei,g)] << " <--> " << name[target(*ei,g)] << " with weight of " << weightmap[*ei] << endl;
      sweight += weightmap[*ei];
   }

   return sweight;
}

bool XFU::toposort()
{
   bool res = true;

   const DirectedGraph& g = create_directed_graph();
   typedef std::vector<boost::graph_traits<DirectedGraph>::vertex_descriptor> container;
   container c;
   try
   {
      topological_sort(g,std::back_inserter(c));
   }
   catch (...)
   {
      res = false;
   }
      

   cout << "A topological ordering: ";
   for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ii++)
      cout << *ii << " ";
   cout << endl;
   
   return res;
}