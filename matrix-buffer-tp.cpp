// The goal of this TP is to implement a Matrix class of double using
//    a 1-dimensional buffer for the underlying storage.

// A reshape operation on the Matrix should return a new matrix sharing the same buffer
//    with possibly different dimensions (it is a very simple numpy-like behavior).

// The public operations that can be done on a Matrix are:
//    - a construction that takes the number of rows and columns and creates the underlying buffer
//    - a function to get the value at a given row and column
//    - a function to set the value at a given row and column
//    - a reshape function that takes new dimensions and returns a new Matrix sharing the same buffer
//    - a print function to display the matrix content rows by rows

// Note that other operations can be added as needed to the Matrix class,
// but don't make public methods that you use for internal purposes only
// (e.g. for example methods giving access to the underlying buffer directly).

// Because a same buffer can be shared between several Matrix instances:
//    - when one of these matrix instances is modified, the changes will be effective
//      for all other instances
//    - when one of these matrix instances arrives at the end of its life cycle,
//      the buffer should not be deleted if other instances are still using it
// => you need to know how many instances are sharing the same buffer at a given time
//    (you must count the number of Matrix sharing the buffer)
//    - for a first version of the Buffer, use a raw pointer
//      and manage the count manually
//    - we will use smart pointers in a more advanced version
// For the underlying buffer:
//   - you can use std::vector<double>
//   - or you can use raw c-type arrays if you prefer to manage memory manually

// Exceptions
//   - you need to handle all exception cases by throwing exceptions
//        use standard exceptions from stdexcept
//   - be carefull when using std::vector v[i] and v.at(i) do not behave the same


// Find below a function (that reads doubles from a file and returns them in an std::vector<double>)
//    that you can use to initialize your buffer if you whish

#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

// note:
//   - the use of the std::string standard library
//   - the use of reference to avoid unnecessary copy
//   - the use of const to avoid modification of the filename
//     (but also to allow passing string literals such as "data.txt")
//   - we return the vector containing the read values by copying it
std::vector<double> read_doubles_from_file(const std::string &filename)
{
    std::vector<double> values;
    // we use an ifstream (input file stream) to read from a file
    std::ifstream file(filename);

    if (!file)
    {
        // if the file could not be opened, we throw an exception
        // note the use of + to concatenate std::string objects
        throw std::runtime_error("Could not open file: " + filename);
    }

    // a variable to store the value
    double value;
    while (file >> value)
    {
        // the operation file >> value:
        //    - reads a double from the file
        //    - stores it in the variable value
        //    - stops when reaching end of file

        // note that we add the read value at the end of the vector
        // (it is the place where an array used to grow)
        values.push_back(value);
    }
    return values;
}

int main()
{

    // first, we create a file named "data.txt" containing some doubles
    const char *filename = "data.txt";

    // note that we use an ofstream (output file stream) and the operator <<
    //   to create and write into the file

    std::ofstream file(filename);
    file << "1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0 5.5 6.0 6.5\n";
    // if you forgot to close the file, the data may not be written correctly in the file
    // either you close it manually or you let the destructor do it automatically
    //   by putting a block around the ofstream variable
    file.close();

    // we pass a string literal (const char []) to the function
    //    it is converted to a reference to a temporary CONST std::string object
    //    try to remove the const to see the compilation error
    std::vector<double> values = read_doubles_from_file(filename);
    std::cout << "the values " << values.size() << std::endl;
    std::cout << values.at(0) << std::endl;
    for (double d : values)
    {
        std::cout << d << ", ";
    }
    std::cout << std::endl;
    return 0;
}