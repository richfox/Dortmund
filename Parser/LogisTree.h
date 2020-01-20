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

//递归下降分析器的构造方法就是为每一个非终结符写一个递归函数，
//函数中对该非终结符可能转换成的所有情况的第一个token进行判断，然后做出对应的处理
//消除左递归后的文法
//Exp -> keyword (Exp) Exp'
//     | Text Exp'
//Exp' -> + Exp''
//      | null
//Exp'' -> keyword (Exp)
//       | Text
//Text -> Header Factor
//      | Factor
//Factor -> ( sn Tail )
//        | sn
//Tail -> + sn Tail
//      | null

#pragma once

#include <string>
#include <vector>
#include <memory>


namespace XFU
{
   enum class LogisNodeType
   {
      Undef = -1,
      Root,
      Exp,
      Exp1,
      Exp2,
      Text,
      Factor,
      Tail
   };

   class LogisTreeNode
   {
   public:
      LogisTreeNode()
         :_type(LogisNodeType::Undef),
         _children()
      {}

      explicit LogisTreeNode(const LogisNodeType type)
         :_type(type),
         _children()
      {}

      LogisTreeNode(const LogisNodeType type,const std::shared_ptr<LogisTreeNode>& child)
         :_type(type),
         _children(1,child)
      {}

      LogisTreeNode(const LogisNodeType type,const std::vector<std::shared_ptr<LogisTreeNode>>& children)
         :_type(type),
         _children(children)
      {}

      virtual ~LogisTreeNode()
      {}

      const LogisNodeType GetType() const
      {
         return _type;
      }

      void AddChild(const std::shared_ptr<LogisTreeNode>& child)
      {
         _children.push_back(child);
      }

      bool HasChild() const
      {
         return !_children.empty();
      }

      std::shared_ptr<LogisTreeNode> GetChild(int idx) const
      {
         return _children[idx];
      }

   private:
      LogisNodeType _type;
      std::vector<std::shared_ptr<LogisTreeNode>> _children;
   };


   //Exp -> keyword (Exp) Exp'
   //     | Text Exp'
   class LogisTreeNodeExp final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp()
         :LogisTreeNode(LogisNodeType::Exp)
      {}

      ~LogisTreeNodeExp()
      {}
   };


   //Exp' -> + Exp''
   //      | null
   class LogisTreeNodeExp1 final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp1()
         :LogisTreeNode(LogisNodeType::Exp1)
      {}

      ~LogisTreeNodeExp1()
      {}
   };


   //Exp'' -> keyword (Exp)
   //       | Text
   class LogisTreeNodeExp2 final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp2()
         :LogisTreeNode(LogisNodeType::Exp2)
      {}

      ~LogisTreeNodeExp2()
      {}
   };


   //Text -> Header Factor
   //      | Factor
   class LogisTreeNodeText final : public LogisTreeNode
   {
   public:
      LogisTreeNodeText()
         :LogisTreeNode(LogisNodeType::Text)
      {}

      ~LogisTreeNodeText()
      {}
   };


   //Factor -> ( sn Tail )
   //        | sn
   class LogisTreeNodeFactor final : public LogisTreeNode
   {
   public:
      LogisTreeNodeFactor()
         :LogisTreeNode(LogisNodeType::Factor)
      {}

      ~LogisTreeNodeFactor()
      {}
   };


   //Tail -> + sn Tail
   //      | null
   class LogisTreeNodeTail final : public LogisTreeNode
   {
   public:
      LogisTreeNodeTail()
         :LogisTreeNode(LogisNodeType::Tail)
      {}

      ~LogisTreeNodeTail()
      {}
   };
}