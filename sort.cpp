#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
class full_name
{
	string name;
	string surname;
	string date;
	size_t memory_size;
	fstream file;
	string out;
	multiset<string> str;
public:
	full_name(string&& current_str);
	friend bool operator<(const full_name& a, const full_name& b)
	{
		if (a.name == "" || b.name == "")
			returne false;
		return a.name < b.name;
	}
	string get_full_str() const;
	void my_sort(string name_main_file, size_t memory_size_, string name_out_file);
	size_t file_size(string name_file);
	};
full_name::full_name(string&& current_str)
{
	if (current_str != "")
	{
		size_t k = 0;
		size_t i = 0;
		while (current_str[i] != ' ')
			++i;
		surname = current_str.substr(k, i - k);
		k = i + 1;
		while (current_str[i] != ' ')
			++i;
		name = current_str.substr(k, i - k);
		date = current_str.substr(i + 1, current_str.length());
	}
	else
	{
		surname = "";
		name = "";
		date = "";
	}
}
string full_name::get_full_str() const
{
	return surname + ' ' + name + ' ' + date;
}

void full_name::my_sort(string name_main_file, size_t memory_size_, string name_out_file)
{
	memory_size = memory_size_ * 1024 * 1024;
	out = name_out_file;
	auto count = memory_size / sizeof(full_name);
	if (!count)
		throw invalid_argument("unlucky");
	ifstream file(name_main_file, ios::app);
	for (int i = 1; i < file_size(name_main_file) / memory_size; ++i)
	{
		ofstream outfile(to_string(i) + ".txt");
		while (str.size < count)
		{
			string buffer;
			if (file.good)
			{
				getline(file, buffer);
			}
			else break;
			str.emplace(move(buffer));
		}
		for (auto i : str)
			outfile << i << endl;
    str.clear();
	}
}
size_t full_name::file_size(string name_file)
{
	long fsize;
	ifstream temp(name_file);
	temp.seekg(0, ios::end);
	fsize = temp.tellg();
	temp.close();
	return fsize;
}
