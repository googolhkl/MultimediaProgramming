#include"multimediaProgramming.h"

int main()
{
    hkl::RawToBMP rawToBMP;
    rawToBMP.WriteFileInfo();
    rawToBMP.ConvertGray(rawToBMP.getnWidth(), rawToBMP.getnHeight());

    return 0;
}
