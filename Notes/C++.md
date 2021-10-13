  - [C++](#sec-1)
    - [Install gcc-5 and g++5 in Ubuntu 20](#sec-1-1)
    - [Declare virtual destructors in polymorphic base classes](#sec-1-2)
    - [coc-ccls not working](#sec-1-3)
    - [Run single test with ctest](#sec-1-4)
    - [Virtual Table Explained](#sec-1-5)
    - ["this" and const member function](#sec-1-6)
    - ["using" declaration for constructor inheritance](#sec-1-7)
    - [Add Boost to project in cmake](#sec-1-8)
    - [CMake install prefix](#sec-1-9)
    - [tempalte and typename](#sec-1-10)

# C++<a id="sec-1"></a>


## Install gcc-5 and g++5 in Ubuntu 20     :linux:setup:<a id="sec-1-1"></a>

1.  Add following source to `/etc/apt/sources.list`. [Source](https://askubuntu.com/questions/1236552/how-can-i-downgrade-gcc-to-version-6-on-20-04)
    
        deb http://dk.archive.ubuntu.com/ubuntu/ bionic main universe
2.  Update and install
    
    ```shell
    sudo apt update
    sudo apt install g++-5
    ```

3.  Configure Alternatives
    
    ```shell
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.3 10
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 20
    
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.3 10
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.4 20
    
    sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc 30
    sudo update-alternatives --set cc /usr/bin/gcc
    
    sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 30
    sudo update-alternatives --set c++ /usr/bin/g++
    ```
    
    Then select the version
    
    ```shell
    sudo update-alternatives --config gcc
    sudo update-alternatives --config g++
    ```

References:

-   [Source 1](https://askubuntu.com/questions/1236552/how-can-i-downgrade-gcc-to-version-6-on-20-04)

-[ Source 2](https://askubuntu.com/questions/26498/how-to-choose-the-default-gcc-and-g-version/26518#26518)

## Declare virtual destructors in polymorphic base classes<a id="sec-1-2"></a>

Why not always declare virtual destructors?

Virtual table and virtual pointer cost space.

Takeaway:

1.  polymorphic base classes should always declare a virtual destructor. If the base class already has a virtual member function, it should also declare a virtual destructor.
2.  Do not declare virtual destructor if it is not a polymorphic base classes.

## coc-ccls not working     :setup:vim:linux:<a id="sec-1-3"></a>

`./lib not found`

```shell
cd ~/.config/coc/extensions/node_modules/coc-ccls
ln -s node_modules/ws/lib lib
```

[Reference](https://github.com/neoclide/coc.nvim/issues/2088)

## Run single test with ctest<a id="sec-1-4"></a>

Use regular expression

```shell
ctest -R '^test_'
```

[Reference](https://stackoverflow.com/questions/54160415/running-only-one-single-test-with-cmake-make)

## Virtual Table Explained<a id="sec-1-5"></a>

References:

-   <https://www.cnblogs.com/zhxmdefj/p/11594459.html>
-   <https://jacktang816.github.io/post/virtualfunction/>

## "this" and const member function<a id="sec-1-6"></a>

Reference:

-   <https://www.cnblogs.com/zhxmdefj/p/11572570.html>

## "using" declaration for constructor inheritance<a id="sec-1-7"></a>

Using-declaration introduces a member of a base class into the derived class definition, such as to expose a protected member of base as public member of derived.

It maybe helpful in unit test, when you want to test the protected methods, or get private member through protected methods.

```C++
#include <iostream>
struct B {
    virtual void f(int) { std::cout << "B::f\n"; }
    void g(char)        { std::cout << "B::g\n"; }
    void h(int)         { std::cout << "B::h\n"; }
 protected:
    int m; // B::m is protected
    typedef int value_type;
};

struct D : B {
    using B::m; // D::m is public
    using B::value_type; // D::value_type is public

    using B::f;
    void f(int) { std::cout << "D::f\n"; } // D::f(int) overrides B::f(int)
    using B::g;
    void g(int) { std::cout << "D::g\n"; } // both g(int) and g(char) are visible
                                           // as members of D
    using B::h;
    void h(int) { std::cout << "D::h\n"; } // D::h(int) hides B::h(int)
};

int main()
{
    D d;
    B& b = d;

//    b.m = 2; // error, B::m is protected
    d.m = 1; // protected B::m is accessible as public D::m
    b.f(1); // calls derived f()
    d.f(1); // calls derived f()
    d.g(1); // calls derived g(int)
    d.g('a'); // calls base g(char)
    b.h(1); // calls base h()
    d.h(1); // calls derived h()
}
```

Reference:

-   <https://en.cppreference.com/w/cpp/language/using_declaration>

## Add Boost to project in cmake<a id="sec-1-8"></a>

```

set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.76.0)
find_package(Boost)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${BOOST_ROOT})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()
```

## CMake install prefix<a id="sec-1-9"></a>

```
cmake -D CMAKE_INSTALL_PREFIX:PATH=/home/user/opt/ -Bbuild -S.
```

[Reference](https://askubuntu.com/questions/2167/how-to-build-application-without-sudo-privileges)

## tempalte and typename<a id="sec-1-10"></a>

[Reference](https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates)
