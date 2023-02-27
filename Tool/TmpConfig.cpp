#include "stdafx.h"
#include "TmpConfig.h"
#include "path.h"


#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>


using namespace std;
using namespace XFU;
namespace pt = boost::property_tree;


wstring TmpConfig::_fname = L"xfu_setting.xml";

template<typename T>
const T TmpConfig::load_tmp_setting(const wstring& node)
{
   pt::wptree tree;
   wstring tpath = XFUPath::GetSystemTempPath();
   wifstream ifs(tpath + _fname);
   pt::read_xml(ifs,tree);

   return tree.get<T>(node);
}

template<typename T>
void TmpConfig::save_tmp_setting(const T& setting,const wstring& node)
{
   pt::wptree tree;
   wstring tpath = XFUPath::GetSystemTempPath();

   if (!XFUPath::Exist(tpath + _fname))
   {
      XFUPath::Create(tpath);
      tree.put(node,setting);
      wofstream ofs(tpath + _fname);
      pt::write_xml(ofs,tree);
   }
   else
   {
      wifstream ifs(tpath + _fname);
      pt::read_xml(ifs,tree);

      wofstream ofs(tpath + _fname);
      tree.add(node,setting);
      pt::write_xml(ofs,tree);
   }
}

//Explizite Instantiierungen
template void TmpConfig::save_tmp_setting<int>(const int& setting,const std::wstring& node);
template const int TmpConfig::load_tmp_setting<int>(const std::wstring& node);
template void TmpConfig::save_tmp_setting<wstring>(const wstring& setting,const std::wstring& node);
template const wstring TmpConfig::load_tmp_setting<wstring>(const std::wstring& node);