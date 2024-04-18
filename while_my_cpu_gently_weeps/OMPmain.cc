//Write your code here!
//Compile with g++ -std=c++2a filesystem.cc
#include <iostream>
#include <filesystem>
#include <chrono>
#include <omp.h>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

void dirParser(string dir, vector<string> &x) {
	try {
                for (const auto& f : recursive_directory_iterator(dir)) {
                        stringstream sts;
                        sts << f;
                        x.push_back(move(sts.str().substr(1, sts.str().length() - 2)));
                }
        } catch (...){
                cout << "Could not open that directory\n";
                exit(1);
        }
}
int main(int argc, char **argv) {
	string keyword, temp, dir;
	vector<string> files, foundFiles;
	if (argc == 2) dir = argv[1];

	cout << "Please enter the keyword to search for:" << endl;
	cin >> keyword;
	cout << "Please enter the directory to search in:" << endl;
	cin >> dir;
	//Enumerate all files off the chosen directory
	auto start = std::chrono::system_clock::now();
	dirParser(dir, files);

	#pragma omp parallel
	{
	
	ifstream find;
	string word;
	vector<string> localFoundFiles;	

	//Print all the files found
	#pragma omp for
	for (const string &file : files) {
		find.open(file);
		while(find >> word) {
			if (word == keyword) {
				foundFiles.push_back(file);
				break;
			}
		}
		find.close();
	}
	
	#pragma omp critical
    	foundFiles.insert(foundFiles.end(), localFoundFiles.begin(), localFoundFiles.end());
		
	}
	sort(foundFiles.begin(), foundFiles.end());
	for (const string &x : foundFiles)
		cout << x << endl;

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	cerr << "Time Elapsed: " << elapsed.count() << " ms" << '\n';
}
