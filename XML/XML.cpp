// XML.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <conio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>


namespace pt = boost::property_tree;

struct FetchConfig
{
	std::wstring _url;
	std::wstring _branch;
	int _build;
	int _32Bit;
	int _64Bit;
	int _debugVal;
	std::vector<std::wstring> _debugFiles;

	void Load(const std::wstring& filename)
	{
		pt::wptree tree;
		std::wifstream ifs(filename);
		pt::read_xml(ifs,tree);

		_url = tree.get<std::wstring>(L"config.image.downloadUrlPrefix");
		_branch = tree.get<std::wstring>(L"config.image.branchID");
		_build = tree.get<int>(L"config.image.build");
		_32Bit = tree.get(L"config.image.fetch32Bit",0);
		_64Bit = tree.get(L"config.image.fetch64Bit",0);
		_debugVal = tree.get(L"config.image.fetchDebug.<xmlattr>.val",0);
		for (const pt::wptree::value_type& v : tree.get_child(L"config.image.fetchDebug"))
		{
			_debugFiles.push_back(v.second.data());
		}
	}

	void Save(const std::wstring& filename)
	{
		pt::wptree tree;
		tree.put(L"config.image.downloadUrlPrefix",_url);
		tree.put(L"config.image.branchID",_branch);
		tree.put(L"config.image.build",_build);
		tree.put(L"config.image.fetch32Bit",_32Bit);
		tree.put(L"config.image.fetch64Bit",_64Bit);
		tree.put(L"config.image.fetchDebug.<xmlattr>.valnew",_debugVal);
		for (const std::wstring& file : _debugFiles)
		{
			tree.add(L"config.image.fetchDebug.fetchDebug",file);
		}

		std::wofstream ofs(filename);
		const auto settings = pt::xml_writer_make_settings<std::wstring>(L'&',3);
		pt::write_xml(ofs,tree,settings);
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
	   //test save load
		FetchConfig fc;
		fc.Load(L"fetchConf.xml");
		fc.Save(L"fetchConf_out.xml");
		std::cout << "Success!" << std::endl;

		//test file to string
		std::wifstream temp(L"fetchConf.xml");
		std::wstringstream buffer;
		buffer << temp.rdbuf();
		temp.close();
		std::wcout << buffer.str() << std::endl;
	}
	catch (const pt::ptree_error& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
    _getch();
	return 0;
}

