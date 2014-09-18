from distutils.core import setup, Extension

geo_module = Extension('geo',
                    include_dirs = ['/usr/local/include',],
                    library_dirs = ['/usr/local/lib',],
                    sources = ['geomodule.cpp', 'geo.cpp'])

setup (name = 'Geo',
       version = '1.0',
       description = 'A geo package from Mappy',
       author = 'LBS team',
       author_email = 'lbs@mappy.com',
       url = 'http://github.com/mappy',
       long_description = '''
A demo package with geo functions
''',
       ext_modules = [geo_module])
