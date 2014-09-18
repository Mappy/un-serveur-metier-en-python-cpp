#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include "geo.hpp"

BOOST_PYTHON_MODULE(geo)
{
    using namespace boost::python;
    def("geocoord2string", geocoord2string);
}
