//########################################################
//##                                                    ##
//##        Product:   HiCAD / HeLIOS                   ##
//##        Copyright: by ISD Software & Systeme GmbH   ##
//##        Adress:    Hauert 4                         ##
//##                   44227 Dortmund                   ##
//##                   Germany                          ##
//##        Phone:      (+49) 231 97 93 0               ##
//##        E-Mail:     info@isdCAD.de                  ##
//##                                                    ##
//########################################################

// UtilFunc.h

#pragma once

#include <fstream>
#include <sstream>

#include <boost\archive\binary_iarchive.hpp>
#include <boost\archive\binary_oarchive.hpp>
#include <boost\archive\xml_wiarchive.hpp>
#include <boost\archive\xml_woarchive.hpp>


namespace _Serialization
{
	template <class T>
	std::string save_binary_string(const T& t)
	{
		std::ostringstream oss;
		boost::archive::binary_oarchive oa(oss);
		oa << t;
		return oss.str();
	}

	template <class T>
	void save_binary_file(const T& t,const std::wstring& fname)
	{
		std::ofstream ofs(fname);
		boost::archive::binary_oarchive oa(ofs);
		oa << t;
	}

	template <class T>
	void load_binary_string(T& t,std::string& str)
	{
		std::istringstream iss(str);
		boost::archive::binary_iarchive ia(iss);
		ia >> t;
	}

	template <class T>
	void load_binary_file(T& t,const std::wstring& fname)
	{
		std::ifstream ifs(fname);
		boost::archive::binary_iarchive ia(ifs);
		ia >> t;
	}

	template <class T>
	void save_xml_file(const T& t,const std::wstring& fname)
	{
		std::wofstream ofs(fname);
		boost::archive::xml_woarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(t);
	}

	template <class T>
	void load_xml_file(T& t,const std::wstring& fname)
	{
		std::wifstream ifs(fname);
		boost::archive::xml_wiarchive ia(ifs);
		ia >> BOOST_SERIALIZATION_NVP(t);
	}
}