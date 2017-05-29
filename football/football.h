#pragma once

#ifdef FOOTBALL_EXPORTS
#define FOOTBALL_SPEC __declspec(dllexport)
#else
#define FOOTBALL_SPEC __declspec(dllimport)
#endif // FOOTBALL_EXPORTS

#include <string>

#pragma warning (push)
#pragma warning (disable: 4251)

class FOOTBALL_SPEC Formation
{
public:
	Formation(std::wstring name)
		:_name()
	{}

	virtual ~Formation()
	{}

	void set_defence_player(int player);
	void set_midfield_player(int player);
	void set_forward_player(int player);

	int get_defence_player();
	int get_midfield_player();
	int get_forward_player();

private:
	int _defencer;
	int _midfielder;
	int _forward;

	std::wstring _name;
};

#pragma warning (pop)