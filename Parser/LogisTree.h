//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)


#pragma once

enum class NodeType
{
   Undef = -1,
   Leaf,
   Key  //%Foo()
};

class LogisTreeNode abstract
{
public:
   LogisTreeNode()
      :_type(NodeType::Undef)
   {}

   explicit LogisTreeNode(const NodeType type)
      :_type(type)
   {}

   NodeType GetType() const
   {
      return _type;
   }

private:
   NodeType _type;
};
