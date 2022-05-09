/** *********************************************************************
 * @file
 *
 * @brief  Prototypes for utilities.cpp
 ***********************************************************************/
#pragma once
#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <iomanip>

using namespace std;

/************************************************************************
 *                         Function Prototypes
 ***********************************************************************/
void cleanUp(ifstream& fin, ofstream& fout, ofstream& foutTwo);
bool openFiles(ifstream& fin, string inputFile);
bool openFilesOutput(ofstream& fout, string outputFile);
bool findWord(string& word);