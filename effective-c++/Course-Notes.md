# Effective C++

Category: Language
Content: Book 📘
Created time: Mar 4, 2021 1:29 AM
Date: Mar 4, 2021 → Mar 14, 2021
Materials: https://github.com/alfmunny/book-notes/tree/master/effective-c%2B%2B
Status: In Progress
Tags: C++
URL: https://book.douban.com/subject/1453373/

- 2020.03.03
    - Chapter 1
        - Item 3
            - overload of const member function and normal member function
            - static_cast
        - Item 4
            - Singleton of C++
            - local static
- 2020.03.05
    - Item 5:  the usage of default constructor and destructor.
        - Rule of Zero: [https://en.cppreference.com/w/cpp/language/rule_of_three](https://en.cppreference.com/w/cpp/language/rule_of_three)
        - How to make a user-defined struct to a trivial type: [https://stackoverflow.com/questions/23007358/are-constructors-specified-with-the-default-keyword-trivial](https://stackoverflow.com/questions/23007358/are-constructors-specified-with-the-default-keyword-trivial)

            ```cpp
            struct Foo
            { 
                Foo() = default;
                Foo(int, int);

                char x;
            };

            #include <type_traits>
            static_assert(std::is_trivially_constructible<Foo>::value, "Works");
            ```

        - What is a trivial type: [https://www.geeksforgeeks.org/trivial-classes-c/](https://www.geeksforgeeks.org/trivial-classes-c/)
        - What are POD types in c++: [https://stackoverflow.com/questions/146452/what-are-pod-types-in-c](https://stackoverflow.com/questions/146452/what-are-pod-types-in-c)

            > POD types have characteristics that non-POD types do not. For example, if you have a global, const, POD-type struct, you can initialize its contents with brace notation, it is put into read-only memory, and no code needs to be generated to initialize it (constructor or otherwise), because it's part of the program image. This is important for embedded folks who often have tight constraints on RAM, ROM, or Flash.

        - How to tell them apart in C++

            ```cpp
            int main() {
              std::cout << std::is_trivial<A>::value << std::endl;
              std::cout << std::is_standard_layout<A>::value << std::endl;
              std::cout << std::is_pod<A>::value << std::endl;
            }
            ```