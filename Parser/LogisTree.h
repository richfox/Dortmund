//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)


//  (  表达式的根 %铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1) ) 
//               |                        |                         |
//             %铁路                      +                        %空运       
//      /        |         \                                        |
// 中通6666      +    圆通YT(8888 + 5641)                        JD0001-1-1
//                    /            \
//                 圆通YT        8888 + 5641
//                              /     |     \
//                           8888     +     5641



#pragma once
#include <string>


namespace XFU
{
   enum class NodeType
   {
      Undef = -1,
      Keyword,  //%Foo
      Text, //中通6666
      Operator, //+
      Expr //8888 + 5641
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

   class LogisTreeText final : public LogisTreeNode
   {
   public:
      LogisTreeText(const std::wstring& text)
         :LogisTreeNode(NodeType::Text),
         _text(text)
      {}

      const std::wstring& GetText() const
      {
         return _text;
      }

   private:
      std::wstring _text;
   };

   class LogisTreeOperator final : public LogisTreeNode
   {
   public:
      LogisTreeOperator(const std::wstring& op)
         :LogisTreeNode(NodeType::Operator),
         _op(op)
      {}

      const std::wstring& GetOperator() const
      {
         return _op;
      }

   private:
      std::wstring _op;
   };

   class LogisTreeKey final : public LogisTreeNode
   {

   };
}