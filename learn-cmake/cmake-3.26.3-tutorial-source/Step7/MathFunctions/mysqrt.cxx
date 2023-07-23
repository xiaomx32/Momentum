#include <iostream>

// TODO 4: include cmath
// 由于我们可能会使用 log 和 exp，因此我们需要修改 mysqrt.cxx 以包含 cmath
#include <cmath>
#include "MathFunctions.h"

// a hack square root calculation using simple operations
double mysqrt(double x) {
    if (x <= 0) {
        return 0;
    }

    // TODO 5: If both HAVE_LOG and HAVE_EXP are defined,  use the following:
    //// double result = std::exp(std::log(x) * 0.5);
    //// std::cout << "Computing sqrt of " << x << " to be " << result
    ////        << " using log and exp" << std::endl;
    // else, use the existing logic.

    // Hint: Don't forget the #endif before returning the result!
    // 如果系统上有 log 和 exp，则使用它们计算 mysqrt 函数中的平方根
    // 否则使用自己定义的 log 和 exp
    #if defined(HAVE_LOG) && defined(HAVE_EXP)
        double result = std::exp(std::log(x) * 0.5);
        std::cout << "Computing sqrt of " << x << " to be " << result
                  << " using log and exp" << std::endl;
    #else
        double result = x;

        // do ten iterations
        for (int i = 0; i < 10; ++i) {
            if (result <= 0) {
                result = 0.1;
            }
            double delta = x - (result * result);
            result = result + 0.5 * delta / result;
            std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
        }
    #endif

    return result;
}
