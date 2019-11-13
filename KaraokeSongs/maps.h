#pragma once
#include "Artist.h"
#include "Song.h"
#include "MapManagement.h"
#include <iostream>
#include <map>
using namespace std;
////////PRIMARY Map///////////////////////
///////ENTRIES ARE UNIQUE AND FULL OBJECT MUST BE SAVED TO FILE

	map<string, Artist> artistMap;
	string artistFileTXT = "Artists.txt";
	fstream artistFstream;// (artistFileTXT, ios::in | ios::out);

	map<string, Song> songMap;
	string songFileTXT =  "Songs.txt"; 
	fstream songFstream;// (songFileTXT, ios::in | ios::out);

	//overwrites current contents of the file
	template<typename T>void	primaryMapToFile(map<string, T>& myMap, fstream& myFstream) 
	{
		for (auto& e : myMap) 
		{
			myFstream << e.first << FIELD_DELIMITER << e.second.toFile() << FIELD_DELIMITER << endl;//put key and class output all on a line with field delimiter between key and value
		}
		cout << "\nDone writing map to file.\n";

	};
	template<typename T> void primaryMapFromFile(map<string, T>& myMap, fstream& inputFile)
	{
		GoBeginningOfFile(inputFile);
		while (inputFile)//keep going until end of file
		{
			string line = "";
			getline(inputFile, line, '\n');

			if (line == "")
			{//skip blank line
			}
			else
			{
				vector<string> fields = SeparateLineByDelimiter(line, FIELD_DELIMITER);
				vector<string>::iterator iter = fields.begin();
				string tempKey = *iter;//stores contents of first item in vector as the key
				T tempObject = T();
				iter++;//iterator now points to the first class field that is saved as a string in the vector
				tempObject.fromFile(iter);//pass iterator to class's FromFile() to update the class fields of the object (it will be different for each class)
				bool check = myMap.emplace(make_pair(*iter, tempObject)); //add to map
				cout << "\nAdded " << tempKey << " to map.\n";
			}
			cout << "\nDone reading map from file.\n";
		}
	};
/////////SECONDARY Multimaps////////////////////
/////////save only keys to file, all the map functions like find and emplace only return iterators which are not useful to save. Lookups will be needed to use the contents of these maps
multimap<string, string> songCatalogByArtist;
multimap<string, string> singerHistory; //map<dateAsString, songKey>> 


/////functions for maps
string userInputArtist();
Song userInputSong(string );
bool addSongToCatalogs(string );

/////////functions and user menus specific to individual maps we are using (generic map functions are in MapManagement.h)/////////////////

string userInputArtist() { //temporary, need to complete this 
	//get input from user for fields
	//Artist a = Artist(use user input to create);
	return "dummyKey"; //change to return a.getKey();
};
Song userInputSong(string artistKey) {//temporary, need to complete this 
	string songTitle="";
	cout << "\nSong Title:";
	getline(cin, songTitle);
return Song(songTitle, artistKey);
};

//new songs must be inserted in all relevant maps
bool addSongToCatalogs(Song newSong) {
	if (!addObjectToMap(songMap, newSong))//.second is the bool portion of the pair this function returns (see emplace)
	{cout<<"Already exists in catalog, not added."; return false;}
	string tempArtistKey = newSong.getArtistKey();
	//if (!addObjectToMap(songCatalogByArtist, newSong, tempArtistKey)) //should not fail, not restriction on multimap
	//		{ cout << "Failed to add to song catalog by artist."; return false; }
	return true;
};

