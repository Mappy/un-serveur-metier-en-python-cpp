#include <string>
using namespace std;

const float EARTH_RADIUS = 6371;

class GeoPoint
{
public:
    GeoPoint(double lat, double lng);
    double distance(const GeoPoint &other);
private:
    double lat;
    double lng;
};

string geocoord2string(double angle);
