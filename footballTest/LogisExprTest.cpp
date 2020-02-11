//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################


#include "stdafx.h"
#include "LogisExprTest.h"
#include "..\Parser\LogisTree.h"
#include "..\Parser\LogisTokenizer.h"
#include "..\Parser\LogisParser.h"
#include "..\Parser\LogisVisitor.h"



using namespace std;
using namespace logis;

CPPUNIT_TEST_SUITE_REGISTRATION(LogisExprTest);


void LogisExprTest::setUp()
{}

void LogisExprTest::tearDown()
{}


void LogisExprTest::test()
{
   vector<wstring> tokens;

   tokens = run_logis_tokenizer(L"  ");
   CPPUNIT_ASSERT(tokens.empty());

   tokens = run_logis_tokenizer(L"%A(1)");
   CPPUNIT_ASSERT(tokens.size() == 4);
   CPPUNIT_ASSERT(tokens[3] == L")");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   shared_ptr<LogisTreeNode> tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"%A(1)");
   //      Root
   //       |
   //      Exp
   //      /  \
   //    KExp  PExp  
   //      |
   //     Exp
   //     /  \
   //   Text  PExp
   CPPUNIT_ASSERT(get_tree_height(tree) == 4); //Root
   CPPUNIT_ASSERT(get_tree_height(tree->GetChild(0)) == 3); //Exp: %A(1)
   CPPUNIT_ASSERT(get_tree_height(tree->GetChild(0)->GetChild(0)) == 2); //KExp: %A
   CPPUNIT_ASSERT(get_tree_height(tree->GetChild(0)->GetChild(1)) == 0); //PExp: null
   CPPUNIT_ASSERT(get_tree_height(tree->GetChild(0)->GetChild(0)->GetChild(0)) == 1); //Exp
   CPPUNIT_ASSERT(get_tree_height(tree->GetChild(0)->GetChild(0)->GetChild(0)->GetChild(0)) == 0); //Text: 1
   CPPUNIT_ASSERT(get_tree_height(tree->GetChild(0)->GetChild(0)->GetChild(0)->GetChild(1)) == 0); //PExp: null
   CPPUNIT_ASSERT(tree->GetChildren().size() == 1); //Root
   CPPUNIT_ASSERT(tree->GetChild(0)->GetChildren().size() == 2); //Exp: %A(1)
   CPPUNIT_ASSERT(tree->GetChild(0)->GetChild(0)->GetChildren().size() == 1); //KExp: %A
   CPPUNIT_ASSERT(tree->GetChild(0)->GetChild(1)->GetChildren().size() == 0); //PExp: null
   CPPUNIT_ASSERT(tree->GetChild(0)->GetChild(0)->GetChild(0)->GetChildren().size() == 2); //Exp
   CPPUNIT_ASSERT(tree->GetChild(0)->GetChild(0)->GetChild(0)->GetChild(0)->GetChildren().size() == 0); //Text: 1
   CPPUNIT_ASSERT(tree->GetChild(0)->GetChild(0)->GetChild(0)->GetChild(1)->GetChildren().size() == 0); //PExp: null

   tokens = run_logis_tokenizer(L"yt");
   CPPUNIT_ASSERT(tokens.size() == 1);
   CPPUNIT_ASSERT(tokens[0] == L"yt");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"yt");
   CPPUNIT_ASSERT(get_tree_height(tree) == 2);

   tokens = run_logis_tokenizer(L"(yt)");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"(yt)");
   CPPUNIT_ASSERT(get_tree_height(tree) == 4);

   tokens = run_logis_tokenizer(L"zhongtong6666 + YT8888");
   CPPUNIT_ASSERT(tokens.size() == 3);
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"zhongtong6666+YT8888");
   CPPUNIT_ASSERT(get_tree_height(tree) == 3);

   tokens = run_logis_tokenizer(L"%R(zhongtong6666) + %A(YT8888)");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"%R(zhongtong6666)+%A(YT8888)");
   CPPUNIT_ASSERT(get_tree_height(tree) == 5);

   tokens = run_logis_tokenizer(L"%A(%T(%S(t + B)))");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"%A(%T(%S(t+B)))");
   CPPUNIT_ASSERT(get_tree_height(tree) == 9);

   tokens = run_logis_tokenizer(L"%A(%T(%S(t)+ B))");
   auto s = tokens.size();
   CPPUNIT_ASSERT(tokens[s-1] == L")");
   CPPUNIT_ASSERT(tokens[s-2] == L")");
   CPPUNIT_ASSERT(tokens[s-3] == L"B");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"%A(%T(%S(t)+B))");
   CPPUNIT_ASSERT(get_tree_height(tree) == 8);

   tokens = run_logis_tokenizer(L"%A(%T(%S(t)))+ B");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"%A(%T(%S(t)))+B");
   CPPUNIT_ASSERT(get_tree_height(tree) == 8);

   tokens = run_logis_tokenizer(L"(%A(%T(%S(t)))+ B)");
   CPPUNIT_ASSERT(tokens[0] == L"(");
   CPPUNIT_ASSERT(tokens[1] == L"%A");
   CPPUNIT_ASSERT(tokens[2] == L"(");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"(%A(%T(%S(t)))+B)");
   CPPUNIT_ASSERT(get_tree_height(tree) == 10);

   tokens = run_logis_tokenizer(L"%A(%T(%S(t))) + ( B)");
   CPPUNIT_ASSERT(test_logis_parser(tokens)==true);
   tree = run_logis_parser(tokens);
   CPPUNIT_ASSERT(run_logis_visitor(tree) == L"%A(%T(%S(t)))+(B)");
   

   tokens = run_logis_tokenizer(L"%R(zhongtong6666 + YT(8888 + 5641)) + %A(JD0001-1-1)");
   CPPUNIT_ASSERT(tokens.size() == 16);
   auto tokens2 = run_logis_tokenizer(L"  %R ( zhongtong6666 +  YT(  8888  +  5641  )  ) + %A(JD0001-1-1)  ");
   CPPUNIT_ASSERT(tokens.size() == 16);
   CPPUNIT_ASSERT(tokens == tokens2);
}