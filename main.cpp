#include <iostream>
#include "haversine.hpp"
using namespace std;
 
int main() {
	GeoPoint paris = GeoPoint(48.85, 2.35);
	GeoPoint marseille = GeoPoint(43.30, 5.38);
	
    cout << "Distance Paris(lat = 48.85, lng = 2.35) -> Marseille (lat = 43.30 , lng = 5.38)" << endl;
    cout << paris.distance(marseille) << " km " << endl;
    cout << "Longitude de Marseille : " << geocoord2string(5.38) << endl;
}
