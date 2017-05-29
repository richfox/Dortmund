#include "stdafx.h"
#include "ConfigFile.h"

using namespace std;
using namespace XFU;


ConfigFile::ConfigFile(const std::wstring& filepath)
	:_filepath(filepath),
	_buffer(nullptr),
	_buffersize(0)
{
	wifstream is(_filepath.c_str());
	_fileexist = is.is_open();

	if (!_fileexist)
	{
		return;
	}
	else
	{
		locate_memory();
	}
}

ConfigFile::~ConfigFile()
{
	if (_buffer != nullptr)
	{
		free(_buffer);
	}
}

void ConfigFile::locate_memory()
{
	if (_buffer != nullptr)
	{
		free(_buffer);
	}

	wifstream is(_filepath.c_str());
	is.seekg(0,ios::end);
	_buffersize = static_cast<unsigned int>(is.tellg()) + 16;
	_buffer = static_cast<wchar_t*> (malloc(_buffersize*sizeof(wchar_t)));
}

bool ConfigFile::exist_file() const
{
	return _fileexist;
}

bool ConfigFile::exist_section(const std::wstring& sectionname) const
{
	bool res = false;

	GetPrivateProfileSectionNamesW(_buffer,_buffersize,_filepath.c_str());

	int count = 0;
	CString name;

	while (AfxExtractSubString(name,_buffer,count,L'\0'))
	{
		if (name.IsEmpty())
		{
			break;
		}

		if (_wcsicmp(name.Trim().GetBuffer(),sectionname.c_str()) == 0)
		{
			res = true;
			break;
		}

		count++;
	}

	return res;
}

bool ConfigFile::exist_key(const std::wstring& sectionname,const std::wstring& key) const
{
	bool res = false;

	GetPrivateProfileSectionW(sectionname.c_str(),_buffer,_buffersize,_filepath.c_str());

	int count = 0;
	CString rowtext, rowkey;

	while (AfxExtractSubString(rowtext,_buffer,count,L'\0'))
	{
		if (rowtext.IsEmpty())
		{
			break;
		}

		if (AfxExtractSubString(rowkey,rowtext,0,L'='))
		{
			if (_wcsicmp(rowkey.Trim().GetBuffer(),key.c_str()) == 0)
			{
				res = true;
				break;
			}
		}

		count++;
	}

	return res;
}

void ConfigFile::get_all_section_names(std::vector<std::wstring>& sectionnames) const
{
	sectionnames.clear();

	GetPrivateProfileSectionNamesW(_buffer,_buffersize,_filepath.c_str());

	int count = 0;
	CString name;

	while (AfxExtractSubString(name,_buffer,count,L'\0'))
	{
		if (name.IsEmpty())
		{
			break;
		}

		sectionnames.push_back(name.Trim().GetBuffer());

		count++;
	}
}

void ConfigFile::get_key_value_by_section(const std::wstring& sectionname,map<wstring,wstring>& kvs) const
{
	kvs.clear();

	GetPrivateProfileSectionW(sectionname.c_str(),_buffer,_buffersize,_filepath.c_str());

	int count = 0;
	CString rowtext, rowkey, rowvalue;

	while (AfxExtractSubString(rowtext,_buffer,count,L'\0'))
	{
		if (rowtext.IsEmpty())
		{
			break;
		}

		if (AfxExtractSubString(rowkey,rowtext,0,L'='))
		{
			rowvalue = rowtext.Right(rowtext.GetLength()-rowtext.Find(L'=')-1);
			kvs[rowkey.Trim().GetBuffer()] = rowvalue.Trim().GetBuffer();
		}

		count++;
	}
}

void ConfigFile::get_value(const std::wstring& sectionname,const std::wstring& key,std::wstring& value) const
{
	value = L"";

	GetPrivateProfileSectionW(sectionname.c_str(),_buffer,_buffersize,_filepath.c_str());

	int count = 0;
	CString rowtext, rowkey;

	while (AfxExtractSubString(rowtext,_buffer,count,L'\0'))
	{
		if (rowtext.IsEmpty())
		{
			break;
		}

		if (AfxExtractSubString(rowkey,rowtext,0,L'='))
		{
			if (_wcsicmp(rowkey.Trim().GetBuffer(),key.c_str()) == 0)
			{
				value = rowtext.Right(rowtext.GetLength()-rowtext.Find(L'=')-1).Trim().GetBuffer();
				break;
			}
		}

		count++;
	}
}

void ConfigFile::rename_section(const std::wstring& oldname,const std::wstring& newname)
{
	map<wstring,wstring> kvs;
	get_key_value_by_section(oldname,kvs);
	delete_section(oldname);

	for_each(kvs.begin(),kvs.end(),[&](const map<wstring,wstring>::value_type& kv)
	{
		WritePrivateProfileStringW(newname.c_str(),kv.first.c_str(),kv.second.c_str(),_filepath.c_str());
	});

	locate_memory();
}

void ConfigFile::write_value(const std::wstring& sectionname,const std::wstring& key,const std::wstring& value)
{
	WritePrivateProfileStringW(sectionname.c_str(),key.c_str(),value.c_str(),_filepath.c_str());

	locate_memory();
}

void ConfigFile::delete_section(const std::wstring& sectionname)
{
	WritePrivateProfileStringW(sectionname.c_str(),nullptr,nullptr,_filepath.c_str());
}

void ConfigFile::delete_key(const std::wstring& sectionname,const std::wstring& key)
{
	WritePrivateProfileStringW(sectionname.c_str(),key.c_str(),nullptr,_filepath.c_str());
}