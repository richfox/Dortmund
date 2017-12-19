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
#include "boost/graph/adjacency_list.hpp"


namespace XFU
{
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::undirectedS> undirectedGraph;
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::directedS> directedGraph;
   typedef boost::adjacency_list<boost::listS,boost::vecS,boost::bidirectionalS> bidirectedGraph;

   undirectedGraph __declspec(dllexport) create_undirected_graph();
   directedGraph __declspec(dllexport) create_directed_graph();
   bidirectedGraph __declspec(dllexport) create_bidirected_graph();
}
