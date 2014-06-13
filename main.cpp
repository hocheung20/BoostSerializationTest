#include <fstream>
#include <string>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"

//#define USE_BINARY

#ifdef USE_BINARY
    typedef boost::archive::binary_oarchive out_archive;
    typedef boost::archive::binary_iarchive in_archive;
#else
    typedef boost::archive::text_oarchive out_archive;
    typedef boost::archive::text_iarchive in_archive;
#endif

struct TestStruct
{
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & structInt;
        ar & structUInt;
        ar & structChar;
        ar & structString;
    }

    int structInt;
    unsigned int structUInt;
    char structChar;
    std::string structString;

    bool operator==(const TestStruct& other) const
    {
        return 
        (
            other.structInt == structInt &&
            other.structUInt == structUInt  &&
            other.structChar == structChar &&
            other.structString == structString
        );
    }
};

int main()
{
    TestStruct inputStruct;
    inputStruct.structInt = -1;
    inputStruct.structUInt = 1;
    inputStruct.structChar = 'a';
    inputStruct.structString = "testLol";

    std::string fileName = "test_serialize.txt";
    std::ofstream ofs(fileName);
    {
        out_archive oa(ofs);
        oa << inputStruct;
    }

    TestStruct outputStruct;
    {
        std::ifstream ifs(fileName);
        in_archive ia(ifs);

        ia >> outputStruct;
    }

    std::cout << outputStruct.structInt << std::endl;
    std::cout << outputStruct.structUInt << std::endl;
    std::cout << outputStruct.structChar << std::endl;
    std::cout << outputStruct.structString << std::endl;


    if (!(inputStruct == outputStruct))   
    {
        std::cout << "Fail" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Success" << std::endl;
        return 0;
    }
}

namespace boost {
namespace serialization {



} // namespace serialization
} // namespace boost