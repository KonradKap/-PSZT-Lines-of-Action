#pragma once

#include "Utility.h"

namespace boost {
namespace test_tools {
namespace tt_detail {
    template<>
    struct print_log_value<std::vector<int>> {
        void operator()(std::ostream& ostr, const std::vector<int>& input) {
            print(input, ostr);
        }
    };
}
}
}
