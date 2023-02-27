g++ -c URLEncoder.cpp -I..\include
ar rcs urlencoder.lib *.o
del ..\lib\urlencoder.lib
move urlencoder.lib ..\lib