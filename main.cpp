#include"fileref.h"
#include<iostream>
#include<filesystem>
#include<string>
using namespace std;


void show(char* file);
void set_tags(int argc, char** argv);
bool is_numb(const string& str)
{
	for (auto& ch : str)
		if (!isdigit(ch))
			return false;

	return true;
}
int main(int argc, char** argv)
{
	if (argc == 2)
	{
		if (std::filesystem::exists(std::filesystem::path{argv[1]}))
			show(argv[1]);
		else
			cout << argv[1] << " doesn't exist!";
	}
	else
	{
		set_tags(argc, argv);
	}

	return 0;
}
void show(char* file)
{
	TagLib::FileRef f(file);
	cout << "album:" << f.tag()->album()  << endl
		<< "artist:" << f.tag()->artist() << endl
		<< "title :" << f.tag()->title()  << endl
		<< "genre :" << f.tag()->genre()  << endl
		<< "year  :" << f.tag()->year()   << endl
		<< "track :" << f.tag()->track()  << endl;
}
void set_tags(int argc, char** argv)
{
	if (argc > 8)
	{
		cout << "too many arguments!" << endl;
		exit(-1);
	}
	if (argc < 3)
	{
		cout << "not enough arguments!" << endl;
		exit(-1);
	}
	if (std::filesystem::exists(std::filesystem::path{argv[1]}))
	{
		TagLib::FileRef f(argv[1]);
		for (size_t i = 2; i < argc; i++)
		{
			auto arg = string(argv[i]);
			auto del = arg.find(":");
			if (del == string::npos)
			{
				cout << "incorrect argument:" << arg << endl;
				exit(-1);
			}

			auto left = arg.substr(0, del);
			auto right = arg.substr(del+1);

			if (left == "artist")
				f.tag()->setArtist(right);

			else if (left == "title")
				f.tag()->setTitle(right);

			else if (left == "album")
				f.tag()->setAlbum(right);

			else if (left == "genre")
				f.tag()->setGenre(right);

			else if (left == "year")
			{
				if (is_numb(right))
					f.tag()->setYear(atoi(right.c_str()));
				else
				{
					cout << "can't set year. " << right << " isn't digit value!"<<endl;
				}
			}
			else if (left == "track")
			{
				if (is_numb(right))
					f.tag()->setTrack(atoi(right.c_str()));
				else
				{
					cout << "can't set track. " << right << " isn't digit value!"<<endl;
				}
			}
			else
			{
				cout << "unknown or unsupported tag " << left << endl;
			}
		}

		f.save();
	}
	else
	{
		cout << argv[1] << " doesn't exist!" << endl;
	}
}