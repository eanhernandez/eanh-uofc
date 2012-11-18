clear

echo CASE 1: regular file
echo my stat...
./estat estat.c
echo
echo real stat...
stat estat.c
echo
echo CASE 4: directory
echo my stat...
./estat .
echo
echo real stat...
stat .

