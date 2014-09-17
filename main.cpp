#include <iostream>
#include "haversine.hpp"
using namespace std;
 
int main() {
    cout << "Distance Paris(lat = 48.85, lng = 2.35) -> Marseille (lat = 43.30 , lng = 5.38)" << endl;
    cout << GeoDistance(48.85, 2.35, 43.30, 5.38) << " km " << endl;
}
