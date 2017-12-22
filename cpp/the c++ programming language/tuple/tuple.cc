#include <iostream>

struct Nil {};

template<typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
struct Tuple : Tuple<T2, T3, T4> {
    T1 x;
    using Base = Tuple<T2, T3, T4>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) : Base(t2, t3, t4), x{t1} {}
};

template<>
struct Tuple<> { Tuple(){} };

template<typename T1>
struct Tuple<T1> : Tuple<> {
    T1 x;
    using Base = Tuple<>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1) : Base{}, x{t1} {}
};

template<typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2> {
    T1 x;
    using Base = Tuple<T2>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1, const T2& t2) : Base(t2), x(t1) {}
};

template<typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3> {
    T1 x;
    using Base = Tuple<T2, T3>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1, const T2& t2, const T3 t3) : Base(t2, t3), x(t1) {}
};


template<typename T1, typename T2, typename T3, typename T4>
void print_elements(std::ostream& os, const Tuple<T1, T2, T3, T4>& t) {
    os << t.x << ",";
    print_elements(os, *t.base());
}

template<typename T1, typename T2, typename T3>
void print_elements(std::ostream& os, const Tuple<T1, T2, T3>& t) {
    os << t.x << ",";
    print_elements(os, *t.base());
}

template<typename T1, typename T2>
void print_elements(std::ostream& os, const Tuple<T1, T2>& t) {
    os << t.x << ",";
    print_elements(os, *t.base());
}

template<typename T1>
void print_elements(std::ostream& os, const Tuple<T1>& t) {
    os << t.x;
}

template<>
void print_elements(std::ostream& os, const Tuple<>& t) {
    os << " ";
}

template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream& os, const Tuple<T1, T2, T3, T4>& t) {
    os << "{";
    print_elements(os, t);
    os << "}";
    return os;
}

template<typename Ret, int N>
struct getNth {
    template<typename T>
    static Ret& get(T& t) {
        return getNth<Ret, N-1>::get(*t.base());
    }

    template<typename T>
    static const Ret& get(const T& t)
    {
        return getNth<Ret, N-1>::get(*t.base());
    }
};

template<typename Ret>
struct getNth<Ret, 0> {
    template<typename T>
    static Ret& get(T& t) {
        return t.x;
    }
    template<typename T>
    static const Ret& get(const T& t) { return t.x; }
};

template<unsigned N, typename... Cases>
struct select;

template<unsigned N, typename T, typename... Cases>
struct select<N, T, Cases...> : select<N-1, Cases...> {
};

template<typename T, typename... Cases>
struct select<0, T, Cases...> {
    using type = T;
};

template<unsigned N, typename... Cases>
using Select = typename select<N, Cases...>::type;

template<int N, typename T1, typename T2, typename T3, typename T4>
Select<N, T1, T2, T3, T4>& get(Tuple<T1, T2, T3, T4>& t) {
    return getNth<Select<N, T1, T2, T3, T4>, N>::get(t);
}


template<int N, typename T1, typename T2, typename T3, typename T4>
const Select<N, T1, T2, T3, T4>& get(const Tuple<T1, T2, T3, T4>& t) {
    return getNth<Select<N, T1, T2, T3, T4>, N>::get(t);
}

template<typename T1, typename T2, typename T3, typename T4>
Tuple<T1, T2, T3, T4> make_tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) {
    return Tuple<T1, T2, T3, T4>{t1, t2, t3, t4};
}

template<typename T1, typename T2, typename T3>
Tuple<T1, T2, T3> make_tuple(const T1& t1, const T2& t2, const T3& t3) {
    return Tuple<T1, T2, T3>{t1, t2, t3};
}
template<typename T1, typename T2>
Tuple<T1, T2> make_tuple(const T1& t1, const T2& t2) {
    return Tuple<T1, T2>{t1, t2};
}
template<typename T1>
Tuple<T1> make_tuple(const T1& t1) {
    return Tuple<T1>{t1};
}

Tuple<> make_tuple() {
    return Tuple<>{};
}
int main()
{
    std::cout << "-----tuple_print-----" << std::endl;
    std::cout << Tuple<double, int, int, int>{1.2, 3, 5, 7} << std::endl;
    std::cout << Tuple<double, int, int>{1.2,3,5} << std::endl;
    std::cout << Tuple<double, int>{1.2, 3} << std::endl;
    std::cout << Tuple<double>{1.2} << std::cout;
    std::cout << Tuple<>{} << std::endl;


    std::cout << "-----tuple_get-----" << std::endl;
    const Tuple<double, int, char, char> x{ 1.1, 42, 'a', 'b' };
    std::cout << "{" << get<0>(x) << "," << get<1>(x) << "," << get<2>(x) << "," << get<3>(x) << "}" << std::endl;
    Tuple<double,int> x1{1.1, 42};
    std::cout << "{" << get<0>(x1) << "," << get<1>(x1) << "}" << std::endl;


    std::cout << "-----make_tuple-----" << std::endl;
    std::cout << make_tuple(1.2, 3, 5, 7) << std::endl;
    std::cout << make_tuple(1.2,3,5) << std::endl;
    std::cout << make_tuple(1.2, 3) << std::endl;
    std::cout << make_tuple(1) << std::endl;
    std::cout << make_tuple() << std::endl;

    return 0;
}
