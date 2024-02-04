#pragma once

#ifndef VECTOR_UTILITY
#define VECTOR_UTILITY

namespace vecUtil {
    void arrPush(int **&, int &, int &, const int *);
    void arrPop(int &);
    void arrUnshift(int **&, int &, int &, const int *);

    void arrResize(int **&, int &, int &);

    void moveArrElRightBy1(int **, int &);
    
    void arrUninitialize(int **, const int);
}

#endif