#include "stdafx.h"
#include "TmpConfig.h"
#include "..\Tool\path.h"


#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>


using namespace std;
using namespace XFU;
namespace pt = boost::property_tree;


wstring TmpConfig::_fname = L"xfu_setting.xml";
wstring TmpConfig::_path = XFUPath::GetSystemTempPath();


template<typename T>
const T TmpConfig::load_tmp_setting(const wstring& node)
{
   pt::wptree tree;
   wifstream ifs(_path + _fname);
   pt::read_xml(ifs,tree);

   return tree.get<T>(node);
}

template<typename T>
void TmpConfig::save_tmp_setting(const T& setting,const wstring& node)
{
   pt::wptree tree;

   if (!XFUPath::Exist(_path + _fname))
   {
      XFUPath::Create(_path);
      tree.add(node,setting);
      wofstream ofs(_path + _fname);
      pt::write_xml(ofs,tree);
   }
   else
   {
      wifstream ifs(_path + _fname);
      pt::read_xml(ifs,tree);

      wofstream ofs(_path + _fname);
      tree.add(node,setting);
      pt::write_xml(ofs,tree);
   }
}

template<typename T>
void TmpConfig::edit_tmp_setting(const T& setting,const wstring& node)
{
   pt::wptree tree;

   if (!XFUPath::Exist(_path + _fname))
   {
      XFUPath::Create(_path);
      tree.put(node,setting);
      wofstream ofs(_path + _fname);
      pt::write_xml(ofs,tree);
   }
   else
   {
      wifstream ifs(_path + _fname);
      pt::read_xml(ifs,tree);

      wofstream ofs(_path + _fname);
      tree.put(node,setting);
      pt::write_xml(ofs,tree);
   }
}


bool TmpConfig::has_tmp_setting(const std::wstring& node)
{
   if (!XFUPath::Exist(_path + _fname))
      return false;

   pt::wptree tree;
   wifstream ifs(_path + _fname);
   pt::read_xml(ifs,tree);

   if (tree.get_child_optional(node))
      return true;

   return false;
}

void TmpConfig::delete_tmp_setting()
{
   DeleteFileW((_path + _fname).c_str());
}

//Explizite Instantiierungen
template const int UTIL_FUNC TmpConfig::load_tmp_setting<int>(const std::wstring& node);
template void UTIL_FUNC TmpConfig::save_tmp_setting<int>(const int& setting,const std::wstring& node);
template void UTIL_FUNC TmpConfig::edit_tmp_setting<int>(const int& setting,const std::wstring& node);
template const wstring UTIL_FUNC TmpConfig::load_tmp_setting<wstring>(const std::wstring& node);
template void UTIL_FUNC TmpConfig::save_tmp_setting<wstring>(const wstring& setting,const std::wstring& node);
template void UTIL_FUNC TmpConfig::edit_tmp_setting<wstring>(const wstring& setting,const std::wstring& node);