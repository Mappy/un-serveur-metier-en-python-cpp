Utiliser des routines C++ en Python
===
Présentation au Meet-up C++ le 2 octobre 2014 à Paris : http://www.meetup.com/User-Group-Cpp-Francophone/events/181945092/

Par [Alexandre Bonnasseau](https://github.com/lexman) de [Mappy](https://mappy.com)

Cadre
===
Base de code C++ fiable et testée

On souhaite prototyper rapidement (besoin mouvant)

Temps d'execution rapide pour des fonctions critiques

L'existant
===
Base de code 

geo.cpp

````
#define _USE_MATH_DEFINES
#include <cmath>
#include "geo.hpp"
#include <sstream>

string geocoord2string(double angle) {
	if ( (angle > 180) || (angle < -180) )
		throw invalid_argument("Invalid argument : angle must be beetween -180° and 180°");
	int deg = int(floor(angle));
	double rest = angle - deg;
	int minute = int(floor( rest * 60));
	rest = rest * 60 - minute;
	int second = int(floor( rest * 60));
	ostringstream result;
	result << deg << "° " << minute << "' " << second <<"''";
	return result.str();
}

double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

GeoPoint::GeoPoint(double lat, double lng) : lat(lat), lng(lng)
{}

double GeoPoint::distance(const GeoPoint &other) {
    // Haversine distance : http://en.wikipedia.org/wiki/Haversine_formula
    double nDLat = deg2rad(other.lat - this->lat);
    double nDLon = deg2rad(other.lng - this->lng);
    double thisLatRad =  deg2rad(this->lat);
    double otherLatRad =  deg2rad(other.lat); 
    double nA = pow ( sin(nDLat/2), 2 ) + cos(thisLatRad) * cos(otherLatRad) * pow ( sin(nDLon/2), 2 ); 
    double nC = 2 * atan2( sqrt(nA), sqrt( 1 - nA ));
    double nD = EARTH_RADIUS * nC; 
    return nD; 
}
````


Ecriture d'une fonction C++ compatible Python
===
D'après : https://docs.python.org/2/extending/extending.html

On écrit une fonction compréhensible par Python :


````
#include "Python.h"
#include "geo.hpp"

static PyObject * geocoord2string_py(PyObject *self, PyObject *args)
{
    double angle = 0;

    if (!PyArg_ParseTuple(args, "d", &angle))
        return NULL;
        
    string res = geocoord2string(angle);
    return Py_BuildValue("s", res.c_str());
}
````

Exposer la fonction dans le module geo
===

````
// La liste des fonctions qu'on expose en Python
static PyMethodDef geoMethods[] = {
    {"geocoord2string",  geocoord2string_py, METH_VARARGS,
     "Conver a latitude or a longitude as an angle in a string in the form : d° m' s''."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

// La fonction initnomdumodule est appelée par l'interpreteur Python 
// à l'import du module
PyMODINIT_FUNC initgeo(void)
{
    (void) Py_InitModule("geo", geoMethods);
}
````


Packager une extension Python
===


````
  from distutils.core import setup, Extension

  geo_module = Extension('geo',
                    include_dirs = ['/usr/local/include',],
                    library_dirs = ['/usr/local/lib',],
                    extra_compile_args=['-std=c++11'],
                    sources = ['geomodule.cpp', 'geo.cpp'])

  setup (name = 'Geo',
       version = '1.0',
       description = 'A geo package from Mappy',
       ext_modules = [geo_module])
````
Installer avec ``python setup.py install`` ou ``python setup.py bdist``



Avec Boost.Python
=== 

````
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
````


Avec Boost.Python on peut
=== 
* Exposer des fonctions C++ en Python
* Définir des classes
* Choisir quelles méthodes exposer en Python pour une classe C++

Focus : Gestion de la mémoire
===
Un code C++ qui conserve une référence sur un objet Python doit appeler la macro ``Py_INCREF()`` pour s'assurer que l'objet ne sera pas détruit
Il faut appeler ``Py_DECREF()`` pour libérer l'objet


Focus : Gestion des erreurs
===

````
import geo
print geo.geocoord2string(181)
````

Sans Boost.Python :

````
terminate called after throwing an instance of 'std::invalid_argument'
  what():  Invalid argument : angle must be beetween -180° and 180°
````
  
Avec Boost.Python :
````
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ValueError: Invalid argument : angle must be beetween -180° and 180°
````
Boost.Python permet également d'affiner al getion des erreurs en associant des erreurs spécifiques Python à des exceptions C++

Un serveur de distance géographiques
===

````
from bottle import route, run, template
from geo import GeoPoint

@route('/distance/<lat1:float>,<lng1:float>/<lat2:float>,<lng2:float>')
def index(lat1, lng1, lat2, lng2):  
    dep = GeoPoint(lat1, lng1)
    arr = GeoPoint(lat2, lng2)
    return template("Distance = {{distance}}", distance=dep.distance(arr))

run(host='localhost', port=8888)
````

A tester avec :
``http://localhost:8888/distance/48.85,2.35/43.30,5.38``


Autre approche : Producteur / Consommateur
===
Si le code C++ concentre les routines critiques en temps d'exécution :

Le code python peut appeler des méthodes C++ à distance

Par exemple via un bus RabbitMQ ou bien des appels ZMQ

Au final, le code Python délègue l'éxécution des sections critiques à des workers C++


 

Les difficultés en Python quand on vient du C++
===

Typage dynamique
===
* En C++ le typage statique offre une première validation du code
* En Python, on ne détecte les erreurs de type qu'à l'exécution !
* => il faut executer le code pour le tester
* => les tests unitaires sont indispensables !


Threads
===
Le [Global Interpreter Lock(GIL)](https://docs.python.org/2/glossary.html#term-global-interpreter-lock) assure que les traitements concurents ne se marchent pas dessus

Les modules thread / threading 
* encapsulent les primitives système de thread
* fournissent des primitives de synchronisation : verrous, sémaphores, etc.

... Mais à aucun moment deux instructions peuvent être executées en même temps à cause du GIL !

Mieux vaut utiliser multiprocessing



Mémoire partagée
===
Le module mmap (Memory-mapped file) permet de partager de la mémoire entre plusieurs process

On peut accéder à cette mémoire comme un fichier en lecture / écriture 

On accède à cette mémoire comme un tableau de char

Mais on ne peut pas utiliser de types complexes


Conclusion : Où va Mappy ?
===

Continuer à développer l'outillage et les sections de code non critiques en Python
Bientôt refaire le serveur d'itinéraire en Python / C++ :
	- graphe des voies en Europe : 20 Go
	- 50 requetes / secondes
	- répondre en 300 ms
	



