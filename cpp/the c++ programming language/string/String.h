#pragma once

template<typename C>
class String {
public:
    String();
    explicit String(const C*);
    String operator=(const String&);
    C& operator[](int n) { return ptr[n]; }
    String& operator+=(C c);
private:
    static const int short_max = 15;
    int sz;
    C* ptr;
};


template<typename C>
String<C>::String() {}