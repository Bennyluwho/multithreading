//Write your code here!
//Compile with g++ -std=c++2a filesystem.cc
#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main(int argc, char **argv) {
	string keyword, temp, dir, word;
	vector<string> files, foundFiles;
	ifstream find;
	if (argc == 2) dir = argv[1];

	cout << "Please enter the keyword to search for:" << endl;
	cin >> keyword;
	cout << "Please enter the directory to search in:" << endl;
	cin >> dir;
	//Enumerate all files off the chosen directory
	auto start = std::chrono::system_clock::now();
	try {
		for (const auto& f : recursive_directory_iterator(dir)) {
			stringstream sts;
			sts << f;

			//temp = sts.str();
			//temp.pop_back();
			//temp.erase(0,1);

			//files.push_back(temp);
			files.push_back(move(sts.str().substr(1, sts.str().length() - 2)));
		}
	} catch (...){
		cout << "Could not open that directory\n";
		return 0; 
	}


	//Print all the files found
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

	sort(foundFiles.begin(), foundFiles.end());
	for (const string &x : foundFiles)
		cout << x << endl;

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	cerr << "Time Elapsed: " << elapsed.count() << " ms" << '\n';
}
