#pragma once

#include <vector>
#include <yaml-cpp/yaml.h>


namespace Asdf {
class NDArray
{
    public:
        NDArray(void);
        NDArray(int source, std::vector<int> shape);
        int get_source(void) const;
        std::vector<int> get_shape(void) const;


    private:
        int source;
        std::vector<int> shape;

        friend std::ostream&
            operator<<(std::ostream &strm, const NDArray &array);

};
} /* namespace Asdf */

namespace YAML {

template<>
struct convert<Asdf::NDArray>
{
    static Node encode(const Asdf::NDArray &array);
    static bool decode(const Node &node, Asdf::NDArray &array);
};
} /* namespace YAML */