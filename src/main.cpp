#include "util.h"
#include "vector.h"
#include "matrix.h"
#include "color.h"
#include "image.h"

int main()
{
    rayTracer::Image test( 800, 600 );
    test.WriteTga("test");
    return EXIT_SUCCESS;
}
