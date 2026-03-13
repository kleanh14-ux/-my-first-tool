# -my-first-tool
# fedora Linux:
sudo dnf update && sudo dnf install libcurl4-openssl-dev g++
# Ubuntu/Debian/Kali Linux:
sudo apt update && sudo apt install libcurl4-openssl-dev g++
# macOS:
brew install curl

Compile source code:
g++ fuzzer.cpp -o fuzzer -lcurl

How to run:
./fuzzer <URL/FUZZ> <FILE_WORDLIST>

./fuzzer http://example.com/FUZZ words.txt
=>

target: http://example.com/FUZZ
words: 1000
----------------
[200] http://example.com/admin
[200] http://example.com/login
[301] http://example.com/images
542/1000

Features
Fast & Lightweight: Written in C++ for better performance than traditional shell scripts.

Smart Filtering: Automatically hides 404 Not Found and connection errors to keep the output clean.

Real-time Progress: Shows a live counter (current/total) so you know exactly how far the scan has gone.

CURL Integration: Uses libcurl for reliable and efficient HTTP requests.
