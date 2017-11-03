#pragma once

class string {
public:
    string();
    string(const string& str);
    string(const char* s);
    string(string&& str);

    string& operator=(const string& str);
    string& operator=(const char* s);
    string& operator=(string&& str);

    ~string();

    size_t size() const;
    size_t length() const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    string& append(const string& str);
    string& append(const char* s);

private:

};