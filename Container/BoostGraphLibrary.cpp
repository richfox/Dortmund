//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "BoostGraphLibrary.h"
#include <tuple>



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
   const char* name[] = {"A","B","C","D","E","F","G","H"};
   

   MyGraph g(H);
   boost::property_map<MyGraph,size_t VertexProperty::*>::type getidx = get(&VertexProperty::_index,g);
   boost::property_map<MyGraph,string VertexProperty::*>::type getname = get(&VertexProperty::_name,g);


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

void XFU::dfs(const MyGraph& g)
{
   DFSVisitor vis;
   depth_first_search(g,visitor(vis));
}

void XFU::bfs()
{
   MyGraph& g = create_my_graph();

   vector<graph_traits<MyGraph>::vertices_size_type> map(num_vertices(g));
   graph_traits<MyGraph>::vertices_size_type time = 0;
   BFSVisitor<graph_traits<MyGraph>::vertices_size_type*> vis(&map[0],time);
   breadth_first_search(g,0,visitor(vis));

   boost::property_map<MyGraph,size_t VertexProperty::*>::type getidx = boost::get(&VertexProperty::_index,g);
   boost::property_map<MyGraph,string VertexProperty::*>::type getname = boost::get(&VertexProperty::_name,g);

   for (int i=0; i<num_vertices(g); i++)
      cout << getname[map[i]] << map[i] << boost::get(getidx,map[i]) << " ";
   cout << endl;
}