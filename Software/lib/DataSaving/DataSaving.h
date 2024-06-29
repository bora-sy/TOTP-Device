#include "FS.h"
#include <LittleFS.h>

namespace DataSaving
{
    bool Initialize();

    
    bool FileExists(const char* path);

    bool CreateFile(const char* path);

    bool DeleteFile(const char* path);
    size_t WriteData(const char* path, const uint8_t* data, const size_t len, bool createFileIfDoesntExist = true);

    size_t ReadData(const char* path, uint8_t* data, const size_t len);
}