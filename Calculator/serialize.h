#ifndef _SERIALIZE_H
#define _SERIALIZE_H

#include <fstream>

using std::ios_base;

const long TruePattern = 0xfab1fab2;
const long FalsePattern = 0xbad1bad2;

class DeSerializer
{
    public:
        DeSerializer(std::string const& nameFile) : _stream(nameFile.c_str(), ios_base::in | ios_base::binary)
        {
            if (!_stream.is_open())
                throw "couldn't open file";
        }
        long GetLong()
        {
            if (_stream.eof())
                throw "unexpected end of file";
            long l;
            _stream.read(reinterpret_cast<char *>(&l), sizeof(long));
            if (_stream.bad())
                throw "file read failed";
            return l;
        }
        double GetDouble()
        {
            double d;
            if (_stream.eof())
                throw "unexpected end of file";
            _stream.read(reinterpret_cast<char *>(&d), sizeof(double));
            if (_stream.bad())
                throw "file read failed";
            return d;
        }
        std::string GetString()
        {
            long len = GetLong();
            std::string str;
            str.resize(len);
            _stream.read(&str[0], len);
            if (_stream.bad())
                throw "file read failed";
            return str;
        }
        bool GetBool()
        {
            long b = GetLong();
            if (_stream.bad())
                throw "file read failed";
            if (b == TruePattern)
                return true;
            else if (b == FalsePattern)
                return false;
            else
                throw "data corruption";
            return false;
        }
    private:
        std::ifstream _stream;
};

class Serializer
{
    public:
        Serializer(std::string const& nameFile) : _stream(nameFile.c_str(), ios_base::out | ios_base::binary)
        {
            if (!_stream.is_open())
                throw "couldn't open file";
        }
        void PutLong(long x)
        {
            _stream.write(reinterpret_cast<char *>(&x), sizeof(long));
            if (_stream.bad())
                throw "file write failed";
        }
        void PutDouble(double x)
        {
            _stream.write(reinterpret_cast<char *>(&x), sizeof(double));
            if (_stream.bad())
                throw "file write failed";
        }
        void PutString(std::string const& str)
        {
            std::size_t len = str.length();
            PutLong(len);
            _stream.write(str.data(), len);
            if (_stream.bad())
                throw "file write failed";
        }
        void PutBool(bool x)
        {
            long l = (x ? TruePattern : FalsePattern);
            PutLong(l);
            if (_stream.bad())
                throw "file write failed";
        }
    private:
        std::ofstream _stream;
};

#endif
