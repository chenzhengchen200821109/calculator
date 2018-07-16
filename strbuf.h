#ifndef _strbuf_h
#define _strbuf_h

#include <cstring>
#include <cassert>
#include "Params.h"

//const int maxBufSize = 500; /* global variable included in Params.h */

class StringBuffer
{
    public:
        explicit StringBuffer() : _buf(0), _bufSize(0), _curOffset(0) 
        {
            //_buf = new char [size];
        }
        ~StringBuffer()
        {
            delete [] _buf;
        }
        //bool WillFit(int len) const
        //{
        //    return _curOffset + len + 1 < maxBufSize;
        //}
        int Add(const char* str)
        {
            int len = std::strlen(str);
            int offset = _curOffset;
            if (_curOffset + len + 1 > _bufSize)
                Reallocate(len + 1);
            //std::strcpy(&_buf[_curOffset], str);
            std::strncpy(&_buf[_curOffset], str, len);
            _curOffset += len;
            _buf[_curOffset] = '\0'; // NULL terminator
            ++_curOffset;
            return offset;
            //_curOffset += std::strlen(str) + 1;
        }
        int GetOffset() const
        {
            return _curOffset;
        }
        bool IsEqual(int offStr, const char* str) const
        {
            assert(offStr < _curOffset);
            const char* strStored = &_buf[offStr];
            return std::strcmp(str, strStored) == 0;
        }
        const char* GetString(int offStr) const
        {
            assert(offStr < _curOffset);
            return &_buf[offStr];
        }
    private:
        void Reallocate(int addLen) 
	{
	    int newSize = _bufSize * 2;
	    if (newSize < _curOffset + addLen)
            newSize = _curOffset + addLen;
	    char *newBuf = new char [newSize];
	    for (int i = 0; i < _curOffset; ++i)
            newBuf[i] = _buf[i];
	    delete [] _buf;
	    _buf = newBuf;
	    _bufSize = newSize;
	}
        int _bufSize;
        char* _buf;
        int _curOffset;
};

//void StringBuffer::Reallocate(int addLen)
//{
//    int newSize = _bufSize * 2;
//    if (newSize < _curOffset + addLen)
//        newSize = _curOffset + addLen;
//    char *newBuf = new char [newSize];
//    for (int i = 0; i < _curOffset; ++i)
//        newBuf[i] = _buf[i];
//    delete [] _buf;
//    _buf = newBuf;
//    _bufSize = newSize;
//}

#endif
