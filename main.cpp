#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include <list>

using namespace std;

int main(int argc, char *argv[]) {

    vector<string> tokens;
    set <string> uniqueWords;
    string next_line;

    ifstream readIn(argv[1]);
    string filename = argv[1];

    while (getline(readIn, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token){
            string nopunct = "";
            for(auto &c : token) {
                if (isalpha(c)) {
                    nopunct +=c;
                }
            }
            tokens.push_back(nopunct);
                uniqueWords.insert(nopunct);
        }
    }

    cout << "Number of words "<<tokens.size()<<endl;
    cout << "Number of unique words "<<uniqueWords.size()<<endl;

    ofstream setfile(filename+"_set.txt");
    ofstream vectorfile(filename+"_vector.txt");

    for (set<string>::iterator it=uniqueWords.begin(); it!=uniqueWords.end(); ++it) {
        setfile << ' ' << *it;
    }
    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); ++it) {
        vectorfile << ' ' << *it;
    }

    const int M = 1;

    map<list<string>, vector<string> > wordmap;
    list<string> state;
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
        wordmap[state].push_back(*it);
        state.push_back(*it);
        state.pop_front();
    }

    state.clear();
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
    for (int i = 0; i < 100; i++) {
        if (wordmap[state].size() != 0) {
            int ind = rand() % wordmap[state].size();
            cout << wordmap[state][ind]<<" ";
            state.push_back(wordmap[state][ind]);
        }
        state.pop_front();
    }


    return 0;
}
