//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "BoostGraphLibrary.h"
#include <tuple>
#include <iostream>


using namespace std;
using namespace XFU;
using namespace boost;



undirectedGraph XFU::create_undirected_graph()
{
   undirectedGraph g;
   add_edge(0,1,g);
   add_edge(0,3,g);
   add_edge(1,2,g);
   add_edge(2,3,g);

   undirectedGraph::vertex_iterator vertexIt, vertexEnd;
   undirectedGraph::adjacency_iterator neighbourIt, neighbourEnd;

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

directedGraph XFU::create_directed_graph()
{
   directedGraph g;
   add_edge(0,1,g);
   add_edge(0,3,g);
   add_edge(1,2,g);
   add_edge(2,3,g);

   directedGraph::vertex_iterator vertexIt, vertexEnd;
   directedGraph::out_edge_iterator outedgeIt, outedgeEnd;

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

bidirectedGraph XFU::create_bidirected_graph()
{
   bidirectedGraph g;
   add_edge(0,1,g);
   add_edge(0,3,g);
   add_edge(1,2,g);
   add_edge(2,3,g);

   bidirectedGraph::vertex_iterator vertexIt, vertexEnd;
   bidirectedGraph::in_edge_iterator inedgeIt, inedgeEnd;
   bidirectedGraph::out_edge_iterator outedgeIt, outedgeEnd;

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