from bottle import route, run, template
from geo import GeoPoint

@route('/distance/<lat1:float>,<lng1:float>/<lat2:float>,<lng2:float>')
def index(lat1, lng1, lat2, lng2):
    dep = GeoPoint(lat1, lng1)
    arr = GeoPoint(lat2, lng2)
    return template("Distance = {{distance}}", distance=dep.distance(arr))

run(host='localhost', port=8888)
