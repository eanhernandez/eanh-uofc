clear

echo CASE 2: symlink
echo my stat...
./estat slink
echo
echo real stat...
stat slink
echo
echo CASE 3: hard link
echo my stat...
./estat hlink
echo
echo real stat...
stat hlink


