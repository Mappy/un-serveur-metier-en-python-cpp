#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include "geo.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(geo)
{
    def("geocoord2string", geocoord2string);
    class_<GeoPoint>("GeoPoint", init<double, double>())
        .def("distance", &GeoPoint::distance)
    ;
}
