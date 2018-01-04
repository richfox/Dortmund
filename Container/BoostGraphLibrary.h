//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################
//BGL
//http://www.boost.org/doc/libs/1_45_0/libs/graph/doc/index.html
//https://www.ibm.com/developerworks/cn/aix/library/au-aix-boost-graph/index.html



#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/depth_first_search.hpp"
#include "boost/graph/breadth_first_search.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/property_map/property_map.hpp"


namespace XFU
{
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::undirectedS> UndirectedGraph;
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::directedS> DirectedGraph;
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::bidirectionalS> BidirectedGraph;
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t,int>> EdgeWeightGraph;
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::directedS,boost::no_property,boost::property<boost::edge_weight_t,int>> DirectedEdgeWeightGraph;

   UndirectedGraph __declspec(dllexport) create_undirected_graph();
   DirectedGraph __declspec(dllexport) create_directed_graph();
   EdgeWeightGraph __declspec(dllexport) create_directed_edge_weight_graph();
   BidirectedGraph __declspec(dllexport) create_bidirected_graph();

   struct VertexProperty
   {
      VertexProperty()
      {}

      VertexProperty(int i,const std::string& n)
         :_index(i),_name(n)
      {}

      size_t _index;
      std::string _name;
   };

   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::undirectedS,VertexProperty> MyGraph;
   typedef boost::graph_traits<MyGraph>::vertex_descriptor MyVertex; 
   typedef boost::graph_traits<MyGraph>::edge_descriptor MyEdge;
   typedef boost::graph_traits<MyGraph>::vertices_size_type MySize;

   //Depth First Search Visitor
   template<typename C>
   class DFSVisitor : public boost::default_dfs_visitor
   {
      typedef typename boost::property_traits<C>::value_type T;

   public:
      DFSVisitor(C map,T& t)
         :_map(map),_time(t)
      {}

      template<typename V,typename G>
      void discover_vertex(V v, const G& g) const
      {
         boost::put(_map,v,_time++);
      }

   private:
      C _map;
      T& _time;
   };

   //Breadth First Search Visitor
   template<typename C>
   class BFSVisitor : public boost::default_bfs_visitor
   {
      typedef typename boost::property_traits<C>::value_type T;

   public:
      BFSVisitor(C map,T& t)
         :_map(map),_time(t)
      {}

      template<typename V,typename G>
      void discover_vertex(V v,const G& g) const
      {
         boost::put(_map,v,_time++);
      }

   private:
      C _map;
      T& _time;
   };

   MyGraph create_my_graph();

   std::string __declspec(dllexport) dfs();
   std::string __declspec(dllexport) bfs();
   std::vector<size_t> __declspec(dllexport) dijkstra();
}
