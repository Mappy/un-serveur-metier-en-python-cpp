class GeoPoint
{
public:
    GeoPoint(double lat, double lng);
    double distance(const GeoPoint &other);
private:
    double lat;
    double lng;
};
