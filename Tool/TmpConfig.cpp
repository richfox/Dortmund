#include "stdafx.h"
#include "TmpConfig.h"
#include "path.h"


#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>


using namespace std;
using namespace XFU;
namespace pt = boost::property_tree;


wstring TmpConfig::_fname = L"xfu_setting.xml";


int TmpConfig::load_tmp_setting(const wstring& node)
{
   pt::wptree tree;
   wstring tpath = XFUPath::GetSystemTempPath();
   wifstream ifs(tpath + _fname);
   pt::read_xml(ifs,tree);

   return tree.get<int>(node);
}

void TmpConfig::save_tmp_setting(int setting,const wstring& node)
{
   pt::wptree tree;
   wstring tpath = XFUPath::GetSystemTempPath();

   if (!XFUPath::Exist(tpath + _fname))
   {
      tree.put(node,setting);
      wofstream ofs(tpath + _fname);
      pt::write_xml(ofs,tree);
   }
   else
   {
      wifstream ifs(tpath + _fname);
      pt::read_xml(ifs,tree);

      wofstream ofs(tpath + _fname);
      tree.put(node,setting);
      pt::write_xml(ofs,tree);
   }
}