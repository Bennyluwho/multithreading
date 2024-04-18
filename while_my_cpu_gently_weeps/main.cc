//Write your code here!
//Compile with g++ -std=c++2a -O3 -fopenmp -pthread THREADmain.cc
#include <iostream>
#include <filesystem>
#include <chrono>
#include <omp.h>
#include <algorithm>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int THREADS = 1;
vector<string> files, foundFiles;
mutex m1,m2;

string get_next_filename() {
        lock_guard<mutex> guard(m1);
        static int idx = 0;
        if (idx < files.size())return files.at(idx++);
	else return "";
}

void write_name(const string &s) {
        lock_guard<mutex> guard(m2);
        foundFiles.push_back(s);
}

void wordSearch(const string keyword) {

        ifstream find;
        string word;
	string file = get_next_filename();

        //Print all the files found
	while (!file.empty()) {
        find.open(file);
        if (find.is_open()) {
            while (find >> word) {
                if (word == keyword) {
                    write_name(file);
                    break;
                }
            }
            find.close();
        }
        file = get_next_filename(); // Get the next file to process
    }
}

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
	if (argc == 2) dir = argv[1];

	cout << "Please enter the keyword to search for:" << endl;
	cin >> keyword;
	cout << "Please enter the directory to search in:" << endl;
	cin >> dir;
	cout << "Please enter the amount of threads:" << endl;
	cin >> THREADS;
//	Enumerate all files off the chosen directory
	auto start = std::chrono::system_clock::now();
	dirParser(dir, files);

	
	vector<thread> threads;
	for (int i = 0; i < THREADS; i++) {
		threads.push_back(thread(wordSearch,keyword));
	}	
	for (int i = 0; i < THREADS; i++) {
		threads.at(i).join();
	}	
	sort(foundFiles.begin(), foundFiles.end());
	for (const string &x : foundFiles)
		cout << x << endl;

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	cerr << "Time Elapsed: " << elapsed.count() << " ms" << '\n';
}
