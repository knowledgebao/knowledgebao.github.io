#pragma once

#if defined(_WIN32)

#  define CDECL     __cdecl 
#  define WINAPI    __stdcall
#  define FASTCALL  __fastcall

#  if defined(example_EXPORTS)
#    define MEG_API __declspec(dllexport)
#  else
#    define MEG_API __declspec(dllimport)
#  endif // defined(example_EXPORTS)

#else

#  define CDECL     __attribute__((__cdecl__)) 
#  define WINAPI    
#  define FASTCALL  

#  if example_EXPORTS
#    define MEG_API __attribute__((visibility("default")))
#  else
#    define MEG_API
#  endif
#endif

MEG_API int add_v1(int a, int b, int c);

extern "C" {
MEG_API int CDECL add_v2(int a, int b, int c);
MEG_API int WINAPI add_v3(int a, int b, int c);
MEG_API int FASTCALL add_v4(int a, int b, int c);
}

extern "C" MEG_API int add_v5(int a, int b, int c);

class MEG_API AddOp {
public:
    int add_v6(int a, int b, int c);
    int CDECL add_v7(int a, int b, int c);
};

MEG_API int add_v8(int a, int b);
MEG_API int add_v8(int a, int b, int c);
MEG_API int add_v8(int a, int b, int c, int d);

extern "C" {
MEG_API int add_v9(int a, int b, int* OUT);
MEG_API int sprint(char *buffer, char a, int b, const char* c);
}