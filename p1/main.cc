#include <iostream>
#include <vector>
#include "simple_string.h"
#include "array.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//NOTE THIS IS NOT A COMPLETE LISTING OF TESTS THAT WILL BE RUN ON YOUR CODE
//Just a sample to help get you started and give you an idea of how i'll be testing
//Above each test gives the counts for std::vector and the solution i've written for your array
//As well as checking totals ensure your array doesn't leak memory
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//comment/uncomment these lines to enable tests\
//#define TEST_CLEAR
//#define TEST_POP_FRONT
//#define TEST_POP_BACK
//#define TEST_PUSH_FRONT_WITH_RESERVE
//#define TEST_PUSH_FRONT_VEC
//#define TEST_PUSH_BACK_NEW_VEC
//#define TEST_INITIALIZER_LIST
//#define TEST_ERASE

using std::vector;
//test your code here

int main() {

#ifdef TEST_CLEAR
    //Vector                    Array
    //Default: 0                Default: 0
    //Create: 0                 Create: 0
    //Copy: 0                   Copy: 0
    //Assign: 0                 Assign: 0
    //Destruct: 2               Destruct: 2
    //Move Construct: 0         Move Construct: 0
    //Move Assign: 0            Move Assign: 0

    {
        std::cout << "Vector" << std::endl;
        simple_string a("Goober");
        vector<simple_string> vec;
        vec.push_back(a);
        vec.push_back(a);
        simple_string::initialize_counts();
        vec.clear();
        simple_string::print_counts();

        std::cout << "Array" << std::endl;
        array<simple_string> arr;
        arr.push_back(a);
        arr.push_back(a);
        simple_string::initialize_counts();
        arr.clear();
        simple_string::print_counts();
    }
#endif

#ifdef TEST_POP_FRONT
    //Vector                Array
    //Default: 0            Default: 0
    //Create: 0             Create: 0
    //Copy: 0               Copy: 0
    //Assign: 0             Assign: 0
    //Destruct: 1           Destruct: 1
    //Move Construct: 0     Move Construct: 0
    //Move Assign: 2        Move Assign: 2

    {
        simple_string a("Goober");
        simple_string b("Gabber");
        simple_string c("Gupper");

        std::cout << "Vector" << std::endl;
        vector<simple_string> vec;
        vec.push_back(a);
        vec.push_back(b);
        vec.push_back(c);
        simple_string::initialize_counts();
        //note: std::vec does not have pop_front
        vec.erase(vec.begin());
        simple_string::print_counts();

        std::cout << "Array" << std::endl;
        array<simple_string> arr;
        arr.push_back(a);
        arr.push_back(b);
        arr.push_back(c);
        simple_string::initialize_counts();
        arr.pop_front();
        simple_string::print_counts();
    }

#endif

#ifdef TEST_POP_BACK
    //Vector                Array
    //Default: 0            Default: 0
    //Create: 0             Create: 0
    //Copy: 0               Copy: 0
    //Assign: 0             Assign: 0
    //Destruct: 1           Destruct: 1
    //Move Construct: 0     Move Construct: 0
    //Move Assign: 0        Move Assign: 0
    {
        simple_string a("Goober");


        std::cout << "Vector" << std::endl;
        vector<simple_string> vec;
        vec.push_back(a);
        simple_string::initialize_counts();
        vec.pop_back();
        simple_string::print_counts();


        std::cout << "Array" << std::endl;
        array<simple_string> arr;
        arr.push_back(a);
        simple_string::initialize_counts();
        arr.pop_back();
        simple_string::print_counts();
    }
#endif

#ifdef TEST_PUSH_FRONT_WITH_RESERVE
    //Vector                Array
    //Default: 0            Default: 0
    //Create: 0             Create: 0
    //Copy: 1               Copy: 1
    //Assign: 0             Assign: 0
    //Destruct: 0           Destruct: 0
    //Move Construct: 0     Move Construct: 0
    //Move Assign: 0        Move Assign: 0

    {
        simple_string a("Goober");

        simple_string::initialize_counts();
        std::cout << "Vector" << std::endl;
        vector<simple_string> vec;
        vec.reserve(5);
        vec.insert(vec.begin(), a);
        vec.insert(vec.begin(), a);
        vec.insert(vec.begin(), a);
        vec.insert(vec.begin(), a);
        vec.insert(vec.begin(), a);
        simple_string::print_counts();

        simple_string::initialize_counts();
        std::cout << "Array" << std::endl;
        array<simple_string> arr;
        arr.reserve(5);
        arr.push_front(a);
        arr.push_front(a);
        arr.push_front(a);
        arr.push_front(a);
        arr.push_front(a);
        simple_string::print_counts();
    }
#endif

#ifdef TEST_PUSH_FRONT_VEC
    //Vector                Array
    //Default: 0            Default: 0
    //Create: 0             Create: 0
    //Copy: 1               Copy: 1
    //Assign: 0             Assign: 0
    //Destruct: 2           Destruct: 2
    //Move Construct: 2     Move Construct: 2
    //Move Assign: 0        Move Assign: 0
    {
        simple_string a;
        simple_string b("Foob");
        std::cout << "Vector" << std::endl;

        vector<simple_string> vec;
        std::cout << (int)vec.capacity() << std::endl;
        vec.push_back(a);
        vec.push_back(a);  
        vec.push_back(a);
        //vec.push_back(a);        
        std::cout << (int)vec.capacity() << std::endl;
        simple_string::initialize_counts();
        //note std::vector doesn't have a push_front
        vec.insert(vec.begin(), b);
        std::cout << (int)vec.capacity() << std::endl;        
        simple_string::print_counts();

        std::cout << "Array" << std::endl;
        array<simple_string> arr;
        arr.push_back(a);
        arr.push_back(a);
        arr.push_back(a);
        //arr.push_back(a);
        simple_string::initialize_counts();
        arr.push_front(b);
        simple_string::print_counts();
    }

#endif

#ifdef TEST_PUSH_BACK_NEW_VEC

    //Push back new vec with no reserve
    //
    //Vector                Array
    //Default: 0            Default: 0
    //Create: 0             Create: 0
    //Copy: 1               Copy: 1
    //Assign: 0             Assign: 0
    //Destruct: 0           Destruct: 0
    //Move Construct: 0     Move Construct: 0
    //Move Assign: 0        Move Assign: 0
    {
        simple_string a;

        std::cout << "Vector" << std::endl;
        simple_string::initialize_counts();
        vector<simple_string> vec;
        vec.push_back(a);
        vec.push_back(a);
        vec.push_back(a);
        vec.push_back(a);
        vec.push_back(a);
        simple_string::print_counts();

        std::cout << "Array" << std::endl;
        simple_string::initialize_counts();
        array<simple_string> arr;
        arr.push_back(a);
        arr.push_back(a);
        arr.push_back(a);
        arr.push_back(a);
        arr.push_back(a);
        simple_string::print_counts();
    }
#endif

#ifdef TEST_INITIALIZER_LIST

    //Test initializer list
    //
    //Vector                  Array
    //Default: 0              Default: 0
    //Create: 0               Create: 0
    //Copy: 4                 Copy: 4
    //Assign: 0               Assign: 0
    //Destruct: 2             Destruct: 2
    //Move Construct: 0       Move Construct: 0
    //Move Assign: 0          Move Assign: 0

    {
        simple_string a;
        simple_string b;
        simple_string c;

        std::cout << "Vector" << std::endl;
        simple_string::initialize_counts();
        vector<simple_string> vec({a, b});
        simple_string::print_counts();

        std::cout << "Array" << std::endl;
        simple_string::initialize_counts();
        array<simple_string> arr({a, b});
        simple_string::print_counts();
    }
#endif

#ifdef TEST_ERASE

    //Push back new vec with no reserve
    //
    //Vector                Array
    //Default: 0            Default: 0
    //Create: 0             Create: 0
    //Copy: 1               Copy: 1
    //Assign: 0             Assign: 0
    //Destruct: 0           Destruct: 0
    //Move Construct: 0     Move Construct: 0
    //Move Assign: 0        Move Assign: 0
    {
        simple_string a;

        std::cout << "Vector" << std::endl;
        vector<simple_string> vec;
        vec.push_back(a);
        vec.push_back(a);
        vec.push_back(a);
        vec.push_back(a);
        simple_string::initialize_counts();
        vec.erase(++vec.begin());
        vec.erase(vec.end());
        simple_string::print_counts();

        std::cout << "Array" << std::endl;
        array<simple_string> arr;
        arr.push_back(a);
        arr.push_back(a);
        arr.push_back(a);
        arr.push_back(a);
        simple_string::initialize_counts();
        arr.erase(++arr.begin());
        arr.erase(arr.end());
        simple_string::print_counts();
    }
#endif


    return 0;
}

// #include <iostream>
// #include "array.h"
// #include "simple_string.h"
// //test your code here

// int main() {
//     // //Initialize string counts
//     // simple_string::initialize_counts();

//     // //Create a default string
//     // simple_string str;
//     // //Create a string with a message
//     // simple_string str2("str2");
//     // //Create a string with a copy of a string
//     // simple_string st3(str2);
//     // //Create a string with the assignment op
//     // simple_string st4 = "assignment op";
//     // simple_string st5;
//     // st5 = st4;
//     // //Print the string counts
//     // simple_string::print_counts();

//     /***********************
//      * Constructor testing
//     ***********************/

//     // //Create a default array
//     // array<simple_string> a;
//     // a.length();

//     // //Create an array from a list and print it
//     // array<simple_string> b({simple_string("lstr1"), simple_string("lstr2"), simple_string("lstr3")});
//     // std::cout << b[0] << std::endl;
//     // std::cout << b[1] << std::endl;
//     // std::cout << b[2] << std::endl;


//     // //Create an array using the copy constructor, change some values from both arrays and print them out (ensure deep copy happened)
//     // array<simple_string> c = b;
//     // b[0] = "b lstr1";
//     // c[0] = "c lstr1";
//     // b[1] = "b lstr2";
//     // c[1] = "c lstr2";
//     // b[2] = "b lstr3";
//     // c[2] = "c lstr3";
//     // std::cout << b[0] << std::endl;
//     // std::cout << c[0] << std::endl;
//     // std::cout << b[1] << std::endl;
//     // std::cout << c[1] << std::endl;
//     // std::cout << b[2] << std::endl;
//     // std::cout << c[2] << std::endl;


//     // // //Create an array using the move constructor, print out the values
//     // // array<simple_string> d = array<simple_string> tmp() ;
//     // // std::cout << d[0] << std::endl;
//     // // std::cout << d[1] << std::endl;
//     // // std::cout << d[2] << std::endl;


//     // //Create an array with reserved size
//     // array<simple_string> e(3);
//     // std::cout << e.length() << std::endl;


//     //Create array with n copies of string
//     // array<simple_string> f(3, simple_string("3 copies"));
//     // std::cout << f[0] << std::endl;
//     // std::cout << f[1] << std::endl;
//     // std::cout << f[2] << std::endl;

//     //Call the destructor (don't do this, bad things happen)
//     //f.~array<simple_string>();

//     // std::cout << g[0] << std::endl;
//     // std::cout << g[1] << std::endl;
//     // std::cout << g[2] << std::endl;


//     /*********************
//      * Function testing *
//     **********************/
//     // //Create an array from a list and print it then test methods on it
//     // array<simple_string> g({simple_string("hi"),
//     //     simple_string("hello"), simple_string("whats up")});

//     // //Test the reserve function
//     // //  g.reserve(500);
//     // //  for (u_int i = 0; i < 500; i++)
//     // //     g[i] = simple_string("reserved");
//     // // for (u_int i = 0; i < 500; i++)
//     // //     std::cout << g[i] << std::endl;


//     // //Create new strings and push it on the end and front of the array
//     // simple_string newStr("new back string");
//     // simple_string newStr2("new front string");
//     // g.push_back(newStr);
//     // g.push_front(newStr2);

//     // //Print out the array
//     // for (u_int i = 0; i < g.length(); i++) 
//     //     std::cout << g[i] << std::endl;

//     // //Test the front and back functions, check the length
//     // std::cout << "using front(): " << g.front() << std::endl;
//     // std::cout << "using back(): " << g.back() << std::endl;

//     // //Pop off the front and back string
//     // g.pop_front();
//     // g.pop_back();
//     // //Print out the array
//     // std::cout << std::endl;
//     // for (u_int i = 0; i < g.length(); i++) 
//     //     std::cout << g[i] << std::endl;

//     // //Test the empty function
//     // if (g.empty()) {
//     //     std::cout << "lies" << std::endl;
//     // } else {
//     //     std::cout << "We have " << g.length() << " objects" << std::endl;
//     // }

//     // //Test the clear function
//     // g.clear();
//     //   if (g.empty()) {
//     //     std::cout << "good deal" << std::endl;
//     // } else {
//     //     std::cout << "lies" << std::endl;
//     // }


//     /*********************
//      * Iterator testers *
//     *********************/

//     array<simple_string> h({simple_string("String 1"),
//         simple_string("String 2"), simple_string("String 3")});

//     //Get an iterator to the front and end and then invoke the copy constructor
//     array_iterator<simple_string> it = h.begin();
//     array_iterator<simple_string> it2 = h.end();
//     //array_iterator<simple_string> it3(it);

//     // std::cout << *it << std::endl;
//     // std::cout << *it2 << std::endl;
//     // std::cout << *it3 << std::endl;

//     //Test the increment ops
//     // it++;
//     // ++it3;
//     // std::cout << *it << std::endl;
//     // std::cout << *it2 << std::endl;

//     //Test the equal, not equal ops
//     // if (it == it3) {
//     //     std::cout << "yayyy, its working" << std::endl;
//     // } else {
//     //     std::cout << "booo, its not working" << std::endl;
//     // }

//     // it++;
//     // if (it != it3) {
//     //     std::cout << "yayyy, its working" << std::endl;
//     // } else {
//     //     std::cout << "boooo, its not working" << std::endl;
//     // }

//     //Test the insert and erase functions
//     simple_string insert("insert string");
//     //h.insert(insert, it);
//     //h.insert(insert, ++it);
//     h.insert(insert, it2);
//     for (u_int i = 0; i < h.length(); i++) 
//         std::cout << h[i] << std::endl;

//     array_iterator<simple_string> it3 = h.begin();
//     h.erase(h.end());
//     //h.erase(++it3);
//     for (u_int i = 0; i < h.length(); i++)
//         std::cout << h[i] << std::endl;


//     return 0;
// }