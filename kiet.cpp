#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>

using namespace std;

size_t write_cb(void *p, size_t s, size_t n, void *d) { return s * n; }

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "use: ./fuzzer <url> <wordlist>" << endl;
        cout << "eaxmppel: ./fuzzer http://google.com/FUZZ words.txt" << endl;
        return 1;
    }

    string url = argv[1];
    string listPath = argv[2];

    ifstream file(listPath);
    if (!file) {
        cout << "wordlist not found" << endl;
        return 1;
    }

    vector<string> words;
    string line;
    while (getline(file, line)) if(!line.empty()) words.push_back(line);
    int total = words.size();
    int count = 0;

    cout << "target: " << url << endl;
    cout << "words: " << total << endl;
    cout << "----------------" << endl;

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        for (const string& word : words) {
            count++;
            
            string target = url;
            size_t pos = target.find("FUZZ");
            if (pos != string::npos) target.replace(pos, 4, word);

            curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
            
            long status = 0;
            CURLcode res = curl_easy_perform(curl);
            
            if (res == CURLE_OK) {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
            }

            if (status != 404 && status != 0) {
                cout << "\r" << string(30, ' ') << "\r"; 
                cout << "[" << status << "] " << target << endl;
            }

            cout << "\r" << count << "/" << total << flush;
        }
        curl_easy_cleanup(curl);
    }

    cout << "\ndone" << endl;
    return 0;
}
