Développer une extension C++ pour Python
----------------------------------------

Cet exemple est un support pour la [présentation](prez.md) au [Meet-up C++ le 2 octobre 2014 à Paris](http://www.meetup.com/User-Group-Cpp-Francophone/events/181945092/). 

Il décrit comment exposer en Python une bibliothèque C++ existante, en l'occurence geo.cpp, pour faire un serveur web qui l'utilise.

La branche *master* expose une fonction selon la documentation officielle de Python : https://docs.python.org/2/extending/extending.html

Cette branche `boost_python <https://github.com/Mappy/un-serveur-metier-en-python-cpp/tree/boost_python>`_ montre comment exposer des fonction et des classes plus simplement avec Boost.Python. Cette branche montre comment exposer ces fonctions via uun serveur Web.

Installation
------------
Dépendances :

* Gcc
* Python

Installation::

    git checkout https://github.com/Mappy/un-serveur-metier-en-python-cpp.git
    sudo python setup.py install


Démarrage
---------
Lancer le serveur web ::

    python geoserver.py

Ouvrir dans un navigateur http://localhost:8888/distance/48.85,2.35/43.30,5.38
