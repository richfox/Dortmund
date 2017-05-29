#pragma once

#include <string>
#include <map>
#include <vector>
#include "basedef.h"

#pragma warning (push)
#pragma warning (disable: 4251)

namespace XFU
{
   //Config file with format:
   //	[section]
   //	key=value
   //	key2=value2
   //	...

   class UTIL_CLASS ConfigFile
   {
   public:
	  //Constructor with the whole path of file.
	  ConfigFile(const std::wstring& filepath);
	  ~ConfigFile();

	  //Test weather the config file exist.
	  bool exist_file() const;

	  //Test weather the specified section exist.
	  bool exist_section(const std::wstring& sectionname) const;

	  //Test weather the specified key in specified section exist.
	  bool exist_key(const std::wstring& sectionname,const std::wstring& key) const;

	  //Retrieves the names of all sections.
	  void get_all_section_names(std::vector<std::wstring>& sectionnames) const;

	  //Retrieves all the key-value-pair for the specified section.
	  void get_key_value_by_section(const std::wstring& sectionname,std::map<std::wstring,std::wstring>& kvs) const;

	  //Retrieves the value in the specified section and specified key.
	  void get_value(const std::wstring& sectionname,const std::wstring& key,std::wstring& value) const;

	  //rename section without changing all the entries within the section
	  void rename_section(const std::wstring& oldname,const std::wstring& newname);

	  //Copies a value into the specified section and specified key.
	  //If the section does not exist, it will be created.
	  //If the key does not exist in the specified section, it will be created.
	  void write_value(const std::wstring& sectionname,const std::wstring& key,const std::wstring& value);

	  //the entire section, including all entries within the section, will be deleted.
	  void delete_section(const std::wstring& sectionname);

	  //the key pointed to in the specified section will be deleted
	  void delete_key(const std::wstring& sectionname,const std::wstring& key);

   private:
	  //locate the memory to hold the config file.
	  //If memory already located, it must be freed frist.
	  void locate_memory();

	  const std::wstring _filepath;
	  wchar_t* _buffer;
	  unsigned int _buffersize;
	  bool _fileexist;
   };
}

#pragma warning (pop)
