#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>

using namespace std;

// This program is a file parser that parses the data from two files simultaneously.

// Main Feature: It gets the highest received offer from the available dates from one file  and aligns them with that of the other file.

// By editing the arguments in all the makeLine(...) function under the main for loop you can decide how you want the data to be formatted
// The default format i choose is "['date', rank1, rank2],", I chose this format because i wanted to use this output as arguments in google 
// line chart javascript code for my website.

// I wrote this program purely for fun and to brush up my c++ a bit as you can tell I could have also created a line graph using excel, but
// I do think it can be useful though.

// How to use it for yourself : 
// 1. Get the csv file for any two programmes that you want to compare ( same or different year, doesn't matter)
// 2. Name one as data1.txt and second one as data2.txt.
// 3. Place the exe file in the same directory and you should get the output in the form of a file named  "output.txt".





vector<string> months {"", "January",  "February", "March",  "April",

                      "May",     "June",     "July",     "August", "September",
                      "October", "November", "December"};



int CharToInt(const char &value) { return value - 48; }
// Was gunna use this method intially but then remmeberd the stoi() function



// This function retrives the data from the file
string FileData(ifstream& data)
{
    string line("");
    string FileData("");
    while(data.good())
    {
        data >> line;
        for(int x = 0; x < line.size(); x++)
                if(line[x] == ',') 
                    line[x] = ' ';
        FileData.append(line);
        FileData.append("\n");
    }
    return FileData;
}

// This function parses the date from numerical form to months and day form
string ParseDate(const string &date) {
  string parsedData;
  const string strMonth = (date.substr(5, 2));
  const string strDay = (date.substr(8, 2));
  parsedData.append(months[stoi(strMonth)]);
  parsedData.append(" ");
  parsedData.append(to_string(stoi(strDay)));
  return parsedData;
}

// This function splits a string based on the delimiter character
vector<string> ToWords(const string& line,    char delim = ' ')
{ 
	vector<string> words;
	int temp = 0;

   for(int x = 0; x < line.size(); x++)
   	{ 
   		if(line[x] == delim)
   		{

   			if(temp == 0 )words.push_back(line.substr(temp, x-temp));
   			else words.push_back(line.substr(temp+1, x-temp-1));
   			temp = x;
   		}
   		else if(x+1 == line.size())
   		{
   			words.push_back(line.substr(temp+1, x-temp+1));
   		}

   	}

   	return words;
}

// This function groups the date and the ranking(s) recieved on that date
// The 0th element is the date and all the extra elements are the rankings on that date, it returns a vector of vector of string
vector<vector<string>> group(const vector<string>& value) 
{ 	
	
	vector<vector<string>> ret_value;

	int f_index = 0;
	bool copyExists = false;
	for(int x = 0; x < value.size(); x++)
		{ 
			int copyIndex = 0;
			copyExists = false;
			vector<string> words = ToWords(value[x], ' ');

			for(int y = 0; y < ret_value.size(); y++) 
			{
					if(ret_value[y][0] == words[2])
					{
						copyIndex = y;
					 	copyExists = true;
					}
			}
				
			if(!copyExists)
			{
				ret_value.push_back(vector<string> {words[2], words[1]});
			}
			else
			{
			    ret_value[copyIndex].push_back(words[1]);
			}
		}
		return ret_value;
}

// This function simply appends all the strings provided in the vector to make a new string
string makeLine(const vector<string>& value){

	string ret_value;
	for(int x = 0; x < value.size(); x++)
		{ 
			ret_value.append(value[x]);
		}
	return ret_value;
}

// Returns the greater value
int greaterSize(int val1, int val2)
{

	if(val1 > val2) return val1;
	return val2;
}

int main() {


ifstream data1 ("data1.txt");
ifstream data2 ("data2.txt");

// The data is retrived from file first, then each line is identified on the basis of newline charactar, then the group funciton groups the dates and rankings
vector<vector<string>> vec1 = group(ToWords(FileData(data1),'\n'));
vector<vector<string>> vec2 = group(ToWords(FileData(data2),'\n'));

// Starting Date
int day = 15;

// Starting Month
int monthIndex = 4;

// Starting Rankings
int value1 = 350;
int value2 = 375;

// Index1 and Index2 are the separate counters of each vector. We cant use Index as the counter for both as vec1.size != vev2.size != days specified
int index1 = 0;
int index2 = 0;

// Vector containing the result of all the operations
vector<string> data;


// Index is the count of how many days up untill we want to make the comparision
for(int index = 0; index < 125; index++)
{ 
    string date("");
	// This is not a good way to implement the month counter as not all months are 31 days, good developers should take care of these minor things ( i am not a good developer)
	if(day > 31){
		day = 1;
		monthIndex++;
	}
	// Get the 0th element from the vector of vector, and parse it, as the 0th element will always be a date string
	date =  makeLine({months[monthIndex], " ", to_string(day)});


	// If index 1 and index 2 are not out of bound then check if they both have an entry on the current date
	if(index2+1 < vec2.size() && index1+1 < vec1.size() &&(date == ParseDate(vec1[index1][0]) && date == ParseDate(vec2[index2][0])))
	{

			//  x = 1 because, 0th element is always the date
			for(int x = 1; x < greaterSize(vec1[index1].size(), vec2[index2].size()); x++)
			{
				// If vec1 ran out of ranks, fill only vec2
				if(x+1 > vec1[index1].size())
					value2 = stoi(vec2[index2][x]);

				// If vec2 ran out of ranks, fill only vec1
				else if( x+1 > vec2[index2].size())
					value1 = stoi(vec1[index1][x]);

				// If both of them currently have ranks then fill them together
				else
				{
					value1 = stoi(vec1[index1][x]);
					value2 = stoi(vec2[index2][x]);
				}
			}
			// At the end of the loop value1 and value2 will be the highest rank on the date because of the way data is arranged in raw file (accending)

			//Format the string and add it to the vector
			data.push_back(makeLine({"[\'",date,"\',",to_string(value1), ", ", to_string(value2),"],"}));

			// Update the two index counters, so next date which has an entry will be checked
			index1++;
			index2++;

	}
	// Make sure if the index is in bound then check if the date is same 

	else if(index1 < vec1.size() && date == ParseDate(vec1[index1][0]))
	{
		for(int x = 1; x < vec1[index1].size(); x++)
				value1 = stoi(vec1[index1][x]);

			data.push_back(makeLine({"[\'",date,"\',",to_string(value1), ", ", to_string(value2),"],"}));
			index1++;
	}
	else if(index2 < vec2.size() && date == ParseDate(vec2[index2][0]))
	{
		for(int x = 1; x < vec2[index2].size(); x++)
				value2 = stoi(vec2[index2][x]);

			data.push_back(makeLine({"[\'",date,"\',",to_string(value1), ", ", to_string(value2),"],"}));
			index2++;
	}
	else
	{ 
		
			data.push_back(makeLine({"[\'",date,"\',",to_string(value1), ", ", to_string(value2),"],"}));
	}


// Logic code end
	day++;


}
// Write the data in the vector to the file
ofstream output("output.txt");
for(auto line : data)
{
	output << line << endl;
}

//Close all the files.
output.close();
data1.close();
data2.close();
	

return 0;

}

