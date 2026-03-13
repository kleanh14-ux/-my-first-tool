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
