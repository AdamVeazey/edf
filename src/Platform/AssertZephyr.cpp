#include "EDF/Assert.hpp"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <cstdarg>

namespace EDF {
namespace impl {

void assertion_failed(const char* format, ...) {
    std::va_list args;
    va_start(args, format);
    vprintk(format, args);
    va_end(args);
}

[[noreturn]] void assertion_abort() {
    k_panic();
}

} /* impl */
} /* EDF */