#include <functional>
#include <cstddef>
#include <tuple>
#include <iostream>
#include <utility>

// index_sequence implementation (not available in C++11):
template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

// helper function to inject parameter into signature of function at given position
template <std::size_t N, typename Arg, typename R, typename... Args, std::size_t... Before, std::size_t... After, typename Tuple = std::tuple<Args...>>
auto inject_param(index_sequence<Before...>, index_sequence<After...>)
    -> std::function<R(typename std::tuple_element<Before, Tuple>::type..., Arg, typename std::tuple_element<N + After, Tuple>::type...)>;

// generates lambda function that ignores parameter at given position
template <std::size_t N, typename Arg, typename R, typename... Args, std::size_t... Before, std::size_t... After, typename Tuple = std::tuple<Args...>>
auto add_ignored_arg(std::function<R(Args...)> f, index_sequence<Before...>, index_sequence<After...>)
    -> decltype(inject_param<N, Arg, R, Args...>(index_sequence<Before...>{}, index_sequence<After...>{}))
{
    return [f] (typename std::tuple_element<Before, Tuple>::type... before
                , Arg /*arg*/
                , typename std::tuple_element<N + After, Tuple>::type... after)
                {
                    return f(before..., after...);
                };
}

// overload for std::function wrapped functions:
template <std::size_t N, typename Arg, typename R, typename... Args, typename Tuple = std::tuple<Args...>>
auto add_ignored_arg(std::function<R(Args...)> f)
    -> decltype(inject_param<N, Arg, R, Args...>(make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N>{}))
{
    return add_ignored_arg<N, Arg>(f, make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N>{});
}

// overload for raw function pointers:
template <std::size_t N, typename Arg, typename R, typename... Args, typename Tuple = std::tuple<Args...>>
auto add_ignored_arg(R(*f)(Args...))
    -> decltype(inject_param<N, Arg, R, Args...>(make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N>{}))
{
    return add_ignored_arg<N, Arg>(std::function<R(Args...)>(f), make_index_sequence<N>{}, make_index_sequence<sizeof...(Args) - N>{});
}

struct B {};

void foo(int i, char c, double d)
{
    std::cout << "foo! " << i << " " << c << " " << d << std::endl;
}

void doSomething(std::function<void(int, char, B, double)> callback)
{
    callback(123, 'A', B{}, 3.14f);
}

void myDoSomething(std::function<void(int, char, double)> callback0)
{
    doSomething(add_ignored_arg<2, B>(callback0));
}

int main()
{
    myDoSomething(&foo);
    
    // works even without std::function wrapper:
    doSomething(add_ignored_arg<2, B>(&foo));
}
