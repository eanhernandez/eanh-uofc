clear
set -v
# BAD INPUT, self overwrite:
./filecopy t1.txt t1.txt


# BAD INPUT, input file doesn't exist:
./filecopy NOFILE.txt t1.txt


# GOOD INPUT:
rm -f t2.txt
./filecopy t1.txt t2.txt
cat t2.txt

