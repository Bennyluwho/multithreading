//Compile with g++ -std=c++2a filesystem.cc
#include <iostream>
#include <filesystem>
#include <vector>
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

vector<string> filesnames;
mutex m1, m2;

int main(int argc, char **argv) {
	string dir = "../skool";
	if (argc == 2) dir = argv[1];

	vector<string> files;
	//Enumerate all files off the chosen directory
	for (const auto& f : recursive_directory_iterator(dir)) {
		stringstream sts;
		sts << f;
		files.push_back(move(sts.str().substr(1, sts.str().length() - 2)));
	}
	//Print all the files found
	for (const string &file : files) 
		cout << file << endl;
}
