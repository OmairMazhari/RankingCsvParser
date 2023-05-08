# RankingCsvParser

This program is a file parser that parses the data from two files simultaneously. 
Main Feature: It gets the highest received offer from the available dates from one file and aligns them with that of the other file. 
By editing the arguments in all the makeLine(...) function under the main for loop you can decide how you want the data to be formatted. 
The default format I chose is "['date', rank1, rank2],", I chose this format because I wanted to use this output as arguments in Google line chart javascript code for my website. 
I wrote this program purely for fun and to brush up my C++ a bit as you can tell I could have also created a line graph using Excel, but I do think it can be useful though. 
How to use it for yourself: 1. Get the CSV file for any two programs that you want to compare (same or different year, doesn't matter) 2. Name one as data1.txt and second one as data2.txt. 
3. Place the exe file in the same directory and you should get the output in the form of a file named "output.txt".

