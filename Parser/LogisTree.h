//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)


//  (  表达式的根 %铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1) ) 
//               |                                    |             |
//             %铁路                                  +           %空运       
//      /        |         \                                        |
// 中通6666      +    圆通YT(8888 + 5641)                        JD0001-1-1
//                    /            \
//                 圆通YT        8888 + 5641
//                              /     |     \
//                           8888     +     5641


//语法
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

      const std::shared_ptr<LogisTreeNode>& GetChild(int idx) const
      {
         return _children[idx];
      }

      const std::vector<std::shared_ptr<LogisTreeNode>>& GetChildren() const
      {
         return _children;
      }

      virtual std::wstring ToString() const;

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
         :LogisTreeNode(LogisNodeType::Exp),
         _keyword(L""),
         _text(L"")
      {}

      ~LogisTreeNodeExp()
      {}

      void SetKeyword(const std::wstring& keyword)
      {
         _keyword = keyword;
      }

      const std::wstring GetKeyword() const
      {
         return _keyword;
      }

      void SetText(const std::wstring& text)
      {
         _text = text;
      }

      const std::wstring GetText() const
      {
         return _text;
      }

      std::wstring ToString() const;

   private:
      std::wstring _keyword;
      std::wstring _text;
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

      std::wstring ToString() const;
   };


   //Exp'' -> keyword (Exp)
   //       | Text
   class LogisTreeNodeExp2 final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp2()
         :LogisTreeNode(LogisNodeType::Exp2),
         _keyword(L""),
         _text(L"")
      {}

      ~LogisTreeNodeExp2()
      {}

      void SetKeyword(const std::wstring& keyword)
      {
         _keyword = keyword;
      }

      const std::wstring GetKeyword() const
      {
         return _keyword;
      }

      void SetText(const std::wstring& text)
      {
         _text = text;
      }

      const std::wstring GetText() const
      {
         return _text;
      }

      std::wstring ToString() const;

   private:
      std::wstring _keyword;
      std::wstring _text;
   };


   //Text -> Header Factor
   //      | Factor
   class LogisTreeNodeText final : public LogisTreeNode
   {
   public:
      LogisTreeNodeText()
         :LogisTreeNode(LogisNodeType::Text),
         _header(L"")
      {}

      ~LogisTreeNodeText()
      {}

      void SetHeader(const std::wstring& header)
      {
         _header = header;
      }

      const std::wstring GetHeader() const
      {
         return _header;
      }

      std::wstring ToString() const;

   private:
      std::wstring _header;
   };


   //Factor -> ( sn Tail )
   //        | sn
   class LogisTreeNodeFactor final : public LogisTreeNode
   {
   public:
      LogisTreeNodeFactor()
         :LogisTreeNode(LogisNodeType::Factor),
         _lbracket(false)
      {}

      ~LogisTreeNodeFactor()
      {}

      void SetLbracket()
      {
         _lbracket = true;
      }

      bool HasLbracket() const
      {
         return _lbracket;
      }

      std::wstring ToString() const;

   private:
      bool _lbracket;
   };


   //Tail -> + sn Tail
   //      | null
   class LogisTreeNodeTail final : public LogisTreeNode
   {
   public:
      LogisTreeNodeTail()
         :LogisTreeNode(LogisNodeType::Tail),
         _sn(L"")
      {}

      ~LogisTreeNodeTail()
      {}

      void SetSn(const std::wstring& sn)
      {
         _sn = sn;
      }

      const std::wstring GetSn() const
      {
         return _sn;
      }

      std::wstring ToString() const;

   private:
      std::wstring _sn;
   };
}