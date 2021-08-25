//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "BoostGrahpLibraryTest.h"
#include "..\Container\BoostGraphLibrary.h"

using namespace std;
using namespace XFU;
using namespace boost;

CPPUNIT_TEST_SUITE_REGISTRATION(BGLTest);



void BGLTest::test()
{
   cout << "\r\ntest boost graph library...\r\n" << endl;

   const UndirectedGraph& udgraph = create_undirected_graph();
   CPPUNIT_ASSERT(num_vertices(udgraph)==4);
   CPPUNIT_ASSERT(num_edges(udgraph)==4);

   const DirectedGraph& dgraph = create_directed_graph();
   CPPUNIT_ASSERT(out_degree(0,dgraph)==2);

   BidirectedGraph& bdgraph = create_bidirected_graph();
   CPPUNIT_ASSERT(out_degree(0,bdgraph)==2);
   CPPUNIT_ASSERT(in_degree(0,bdgraph)==0);
   clear_vertex(0,bdgraph);
   remove_vertex(0,bdgraph);
   remove_edge(1,2,bdgraph);
   CPPUNIT_ASSERT(num_vertices(bdgraph)==3);
   CPPUNIT_ASSERT(num_edges(bdgraph)==1);


   cout << "BFS discovery order: " << endl;
   CPPUNIT_ASSERT(bfs()=="ABDGEFCH");

   cout << "DFS discovery order: " << endl;
   CPPUNIT_ASSERT(dfs()=="ABEGFCHD");

   const auto distance = dijkstra();
   CPPUNIT_ASSERT(distance[4]==-1);
   CPPUNIT_ASSERT(distance[6]==70);

   const auto treeweight = kruskal();
   CPPUNIT_ASSERT(treeweight==24);

   bool res = toposort();
   CPPUNIT_ASSERT(res==true);

   res = canonical();
   CPPUNIT_ASSERT(res==true);
}