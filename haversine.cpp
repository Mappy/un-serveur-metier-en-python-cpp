#define _USE_MATH_DEFINES
#include <cmath>

double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

double GeoDistance( double nLat1, double nLon1, double nLat2, double nLon2 )
{
    double nRadius = 6371; // Earth's radius in Kilometers
 
    double nDLat = deg2rad(nLat2 - nLat1);
    double nDLon = deg2rad(nLon2 - nLon1);
 
    nLat1 =  deg2rad(nLat1);
    nLat2 =  deg2rad(nLat2);
 
    double nA = pow ( sin(nDLat/2), 2 ) + cos(nLat1) * cos(nLat2) * pow ( sin(nDLon/2), 2 );
 
    double nC = 2 * atan2( sqrt(nA), sqrt( 1 - nA ));
    double nD = nRadius * nC;
 
    return nD; // Return our calculated distance
}
