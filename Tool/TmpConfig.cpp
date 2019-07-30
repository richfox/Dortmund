#include "stdafx.h"
#include "TmpConfig.h"
#include "path.h"


#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>


using namespace std;
using namespace XFU;
namespace pt = boost::property_tree;

template<typename T>
wstring TmpConfig<T>::_fname = L"xfu_setting.xml";

template<typename T>
const T TmpConfig<T>::load_tmp_setting(const wstring& node)
{
   pt::wptree tree;
   wstring tpath = XFUPath::GetSystemTempPath();
   wifstream ifs(tpath + _fname);
   pt::read_xml(ifs,tree);

   return tree.get<T>(node);
}

template<typename T>
void TmpConfig<T>::save_tmp_setting(const T& setting,const wstring& node)
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

//Explizite Instantiierungen
template class TmpConfig<int>;
template class TmpConfig<bool>;
template class TmpConfig<wchar_t*>;