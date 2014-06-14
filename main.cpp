#include <fstream>
#include <sstream>
#include <string>

#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"

#define USE_BINARY_ARCHIVES
#define USE_FSTREAM
#define USE_BINARY_STREAMS

#ifdef USE_BINARY_ARCHIVES
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

#ifdef USE_FSTREAM
    const std::string filename = "test_serialize.txt";
#ifdef USE_BINARY_STREAMS
    std::ofstream os(filename, std::ios_base::out | std::ios_base::in | std::ios_base::binary );
#else
    std::ofstream os(filename);
#endif // USE_BINARY_STREAMS
#else
#ifdef USE_BINARY_STREAMS
    std::stringstream os(std::ios_base::out | std::ios_base::in | std::ios_base::binary );
#else
    std::stringstream os;
#endif  // USE_BINARY_STREAMS
#endif  // USE_FSTREAM
    {
        out_archive oa(os);
        oa << inputStruct;
    }

    TestStruct outputStruct;
    {
#ifdef USE_FSTREAM
#ifdef USE_BINARY_STREAMS
        std::ifstream is(filename, std::ios_base::in | std::ios_base::binary );
#else
        std::ifstream is(filename);
#endif // USE_BINARY_STREAMS
#else
#ifdef USE_BINARY_STREAMS
        std::stringstream is(std::ios_base::in | std::ios_base::out | std::ios_base::binary );
#else
        std::stringstream is;
#endif  // USE_BINARY_STREAMS
        is.str(os.str());
#endif  // USE_FSTREAM
        in_archive ia(is);

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
