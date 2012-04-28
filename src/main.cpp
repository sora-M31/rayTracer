#include "util.h"
#include "vector.h"
#include "matrix.h"
#include "color.h"
#include "image.h"
//#include "ray.h"

int main()
{
    using namespace rayTracer;
    Matrix test1 ( 1, 2, 3, 4,
                    4,3,2,1,
                   0,0,1,0,
                   0,0,0,1);
    Vector test2( 4, 5, 6, 7);
    std::cout<<test1*test2<<"\n";
    test1.Inverse().PrintMatrix();
    return EXIT_SUCCESS;
}
