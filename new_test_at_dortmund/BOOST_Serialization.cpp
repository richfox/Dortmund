// new_test_at_dortmund.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atlstr.h"
#include "SeiralUtilFunc.h"

#include <conio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include <boost\filesystem.hpp>
#include <boost\serialization\string.hpp>
#include <boost\archive\binary_iarchive.hpp>
#include <boost\archive\binary_oarchive.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\archive\xml_wiarchive.hpp>
#include <boost\archive\xml_woarchive.hpp>
#include <boost\archive\xml_iarchive.hpp>
#include <boost\archive\xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost\serialization\shared_ptr.hpp>
#include <boost\ptr_container\ptr_vector.hpp>
#include <boost\ptr_container\ptr_map.hpp>
#include <boost\ptr_container\serialize_ptr_vector.hpp>
#include <boost\ptr_container\serialize_ptr_map.hpp>
#include <boost/serialization/level.hpp>
#include <boost\serialization\export.hpp>




using namespace std;


class Attr
{
public:
	Attr()
	{}

	Attr(wstring name,int type)
		:_name(name),_type(type)
	{}

	~Attr()
	{}

	void set_name(wstring name)
	{
		_name = name;
	}

	void set_type(int type)
	{
		_type = type;
	}

private:
	wstring _name;
	int _type;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar,const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(_name);
		ar & BOOST_SERIALIZATION_NVP(_type);
	}
};


class A
{
public:
	A()
	{}

	A(int i,int* ii,float f,std::wstring ws,std::wstring* pws,
		std::map<long,std::vector<std::wstring>> map,
		boost::ptr_vector<int> pvec,
		boost::ptr_map<std::pair<long,std::wstring>,Attr> pmap)
		:_i(i),_ii(ii),_f(f),_ws(ws),_pws(pws),_map(map),_pvec(pvec),_pmap(pmap)
	{
		std::ostringstream os;
		boost::archive::binary_oarchive oa(os);
		oa << *this;
		std::string t = os.str();
	}

private:
	int _i;
	int* _ii;
	float _f;
	std::wstring _ws;
    std::wstring* _pws;
	std::map<long,std::vector<std::wstring>> _map;
	boost::ptr_vector<int> _pvec;
	boost::ptr_map<std::pair<long,std::wstring>,Attr> _pmap;

	friend class boost::serialization::access;

	

	template<typename Archive>
	void serialize(Archive& ar,const unsigned int ver)
	{
		ar & BOOST_SERIALIZATION_NVP(_i);
		ar & BOOST_SERIALIZATION_NVP(_ii);
		ar & BOOST_SERIALIZATION_NVP(_f);
		ar & BOOST_SERIALIZATION_NVP(_ws);
        ar & BOOST_SERIALIZATION_NVP(_pws);
		ar & BOOST_SERIALIZATION_NVP(_map);
		ar & BOOST_SERIALIZATION_NVP(_pvec);
		ar & BOOST_SERIALIZATION_NVP(_pmap);
	}
};

BOOST_CLASS_EXPORT_IMPLEMENT(A)	//这样就可以在任何地方串行化 A 的成员变量

//数组可以直接串行化，指针比须保证有效，所以必须保证在串行化之前经过初始化。
//对于基本类型如int，可以直接串行化，但其指针int*，要当作不可侵入(non intrusive)类型的指针来看待,
//所以需要一个全局serialize函数来说明int*类型的串行化方式
namespace boost
{
	namespace serialization
	{
		template<typename Archive>
		void serialize(Archive& ar,int& g,const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(g);
		}

        template<typename Archive>
        void serialize(Archive& ar,std::wstring& g,const unsigned int version)
        {
           ar & BOOST_SERIALIZATION_NVP(g);
        }
	}
}


int __cdecl _tmain(int argc, _TCHAR* argv[])
{
	

	//boost序列化test.----------------------------------------------------
	std::map<long,std::vector<std::wstring>> langs;
	langs[2052] = std::vector<std::wstring>(1,L"test");
	langs[1031] = std::vector<std::wstring>(2,L"test2");
	langs[1033] = std::vector<std::wstring>(3,L"公交车美眉");
	boost::ptr_vector<int> vec;
	vec.push_back(new int(34));
	int ii = 6;
    std::wstring name = L"fuxiang";
    std::wstring namecode = L"xfu";
	boost::ptr_map<std::pair<long,std::wstring>,Attr> attrs;
	attrs[make_pair(1031,L"$BB")].set_name(L"$BB");
	attrs[make_pair(1031,L"$BB")].set_type(1);
	std::pair<long,wstring> attrid = make_pair(1033,L"STD");
	attrs.insert(attrid,new Attr(L"STD",1));
	attrs.erase(attrid);
	attrs.insert(attrid,new Attr(L"CHANGED",2));


	const A a(1,&ii,1.2222f,name,&namecode,langs,vec,attrs);

	typedef boost::archive::text_iarchive iarchive;
	typedef boost::archive::text_oarchive oarchive;

	//Save
	{
		std::ofstream ofs(L"_a_____________a.txt");
		oarchive oa(ofs);
		oa << a;
	}
	
	//Load
	{
		A a2;
		std::ifstream ifs(L"_a_____________a.txt");
		iarchive ia(ifs);
		ia >> a2;
	}
	

	typedef boost::archive::binary_iarchive biarchive;
	typedef boost::archive::binary_oarchive boarchive;

	{
		std::ofstream ofs2("_b_____________b.txt");
		oarchive oa2(ofs2);
		oa2 << a;
	}

	{
		A a3;
		std::ifstream ifs2("_b_____________b.txt");
		iarchive ia2(ifs2);
		ia2 >> a3;
	}
	

	typedef boost::archive::xml_wiarchive xiarchive;
	typedef boost::archive::xml_woarchive xoarchive;

	{
		std::wofstream ofs("_x_____________x.txt");
		xoarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(a);
	}

	{
		A a4;
		std::wifstream ifs("_x_____________x.txt");
		xiarchive ia(ifs);
		ia >> BOOST_SERIALIZATION_NVP(a4);
	}
	


	_getch();
}

