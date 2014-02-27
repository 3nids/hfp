cd ../
rmdir c:\hfp /Q /S
mkdir c:\hfp
mkdir c:\hfp\iconengines

copy ..\build-hfp-Desktop-Release\release\hfp.exe c:\hfp\
copy c:\OSGeo4W\bin\QtCore4.dll c:\hfp\
copy c:\OSGeo4W\bin\QtGui4.dll c:\hfp\
copy c:\OSGeo4W\bin\QtXml4.dll c:\hfp\
copy c:\OSGeo4W\bin\QtNetwork4.dll c:\hfp\
copy c:\OSGeo4W\bin\QtSvg4.dll c:\hfp\
copy c:\OSGeo4W\bin\QtWebKit4.dll c:\hfp\

copy c:\OSGeo4W\bin\zlib_osgeo.dll c:\hfp\
copy c:\OSGeo4W\bin\msvcr71.dll c:\hfp\
copy c:\OSGeo4W\bin\phonon4.dll c:\hfp\
copy c:\OSGeo4W\bin\proj.dll c:\hfp\
copy c:\OSGeo4W\bin\geos_c.dll c:\hfp\
copy c:\OSGeo4W\bin\gdal110.dll c:\hfp\
copy c:\OSGeo4W\bin\ogdi_32b1.dll c:\hfp\
copy c:\OSGeo4W\bin\libexpat.dll c:\hfp\
copy c:\OSGeo4W\bin\xerces-c_3_1.dll c:\hfp\
copy c:\OSGeo4W\bin\LIBPQ.dll c:\hfp\
copy c:\OSGeo4W\bin\SSLEAY32.dll c:\hfp\
copy c:\OSGeo4W\bin\LIBEAY32.dll c:\hfp\
copy c:\OSGeo4W\bin\krb5_32.dll c:\hfp\
copy c:\OSGeo4W\bin\comerr32.dll c:\hfp\
copy c:\OSGeo4W\bin\k5sprt32.dll c:\hfp\
copy c:\OSGeo4W\bin\gssapi32.dll c:\hfp\
copy c:\OSGeo4W\bin\hdf_fw.dll c:\hfp\
copy c:\OSGeo4W\bin\mfhdf_fw.dll c:\hfp\
copy c:\OSGeo4W\bin\jpeg_osgeo.dll c:\hfp\
copy c:\OSGeo4W\bin\jpeg12_osgeo.dll c:\hfp\
copy c:\OSGeo4W\bin\netcdf.dll c:\hfp\
copy c:\OSGeo4W\bin\geotiff.dll c:\hfp\
copy c:\OSGeo4W\bin\libtiff.dll c:\hfp\
copy c:\OSGeo4W\bin\sqlite3.dll c:\hfp\
copy c:\OSGeo4W\bin\spatialite4.dll c:\hfp\
copy c:\OSGeo4W\bin\freexl.dll c:\hfp\
copy c:\OSGeo4W\bin\iconv.dll c:\hfp\
copy c:\OSGeo4W\bin\libxml2.dll c:\hfp\
copy c:\OSGeo4W\bin\LIBMYSQL.dll c:\hfp\
copy c:\OSGeo4W\bin\hdf5.dll c:\hfp\
copy c:\OSGeo4W\bin\szip.dll c:\hfp\
copy c:\OSGeo4W\bin\libcurl.dll c:\hfp\
copy c:\OSGeo4W\bin\zlib1.dll c:\hfp\
copy c:\OSGeo4W\bin\openjp2.dll c:\hfp\
copy c:\OSGeo4W\bin\spatialindex1.dll c:\hfp\
copy c:\OSGeo4W\bin\qwt5.dll c:\hfp\

copy c:\OSGeo4W\apps\qt4\plugins\iconengines\qsvgicon4.dll c:\hfp\iconengines\

copy C:\Progra~1\Git\bin\libiconv-2.dll c:\hfp\
copy C:\Progra~1\Git\bin\libintl-8.dll c:\hfp\

copy c:\OSGeo4W\apps\qgis-dev\bin\qgis_Core.dll c:\hfp\
copy c:\OSGeo4W\apps\qgis-dev\bin\qgis_gui.dll c:\hfp\
copy c:\OSGeo4W\apps\qgis-dev\bin\msvcp90.dll c:\hfp\

copy c:\windows\system32\msvcp100.dll c:\hfp\
copy c:\windows\system32\msvcr100.dll c:\hfp\

mkdir c:\hfp\qgis
mkdir c:\hfp\qgis\resources
mkdir c:\hfp\qgis\plugins
copy C:\OSGeo4W\apps\qgis-dev\resources\* c:\hfp\qgis\resources
copy C:\OSGeo4W\apps\qgis-dev\plugins\* c:\hfp\qgis\plugins


cd win32

 
