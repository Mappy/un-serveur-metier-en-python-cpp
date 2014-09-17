#define _USE_MATH_DEFINES
#include <cmath>
#include "haversine.hpp"


double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

GeoPoint::GeoPoint(double lat, double lng) : lat(lat), lng(lng)
{}

double GeoPoint::distance(const GeoPoint &other) {
    double nRadius = 6371; // Earth's radius in Kilometers
 
    double nDLat = deg2rad(other.lat - this->lat);
    double nDLon = deg2rad(other.lng - this->lng);
 
    double thisLatRad =  deg2rad(this->lat);
    double otherLatRad =  deg2rad(other.lat);
 
    double nA = pow ( sin(nDLat/2), 2 ) + cos(thisLatRad) * cos(otherLatRad) * pow ( sin(nDLon/2), 2 );
 
    double nC = 2 * atan2( sqrt(nA), sqrt( 1 - nA ));
    double nD = nRadius * nC;
 
    return nD; // Return our calculated distance
}
