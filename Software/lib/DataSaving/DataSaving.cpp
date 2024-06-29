#include "DataSaving.h"

namespace DataSaving
{
    bool Initialize()
    {
        bool suc = LittleFS.begin();
        if(!suc) LittleFS.format();
        return suc;
    }

    
    bool FileExists(const char* path)
    {
        return LittleFS.exists(path);
    }

    bool CreateFile(const char* path)
    {
        if(FileExists(path)) return false;

        LittleFS.open(path, "w").close();

        return true;
    }

    bool DeleteFile(const char* path)
    {
        if(!FileExists(path)) return false;

        return LittleFS.remove(path);
    }

    size_t WriteData(const char* path, const uint8_t* data, const size_t len, bool createFileIfDoesntExist)
    {

        if(!FileExists(path))
        {
            if(!createFileIfDoesntExist || !CreateFile(path)) return -1;
        }

        File file = LittleFS.open(path, "w");
        if(!file)
        {
            return -1;
        }

        size_t res = file.write(data, len);

        file.close();

        return res;

    }

    size_t ReadData(const char* path, uint8_t* data, const size_t len)
    { 
        if(!FileExists(path)) return false;

        File file = LittleFS.open(path, "r");
        if(!file)
        {
            return -1;
        }

        size_t res = file.read(data, len);

        file.close();

        return res;
    }
}