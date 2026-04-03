echo Hello World
echo "\"Hello\"" # comment
man echo #q
pwd
ls
ls -a
ls -la
mkdir my
cd my
mkdir -p my2/my3/my4
touch 1.txt
cat 1.txt
echo -e "1\n2\n3" > 1.txt
cat 1.txt
echo -e "1\n2\n3" >> 1.txt
cat 1.txt
cat 1.txt | grep 3 # pipe
ls | grep my
ls | grep my > list.txt
cat list*
ls -R
echo $?
rm 333
echo $?
rm 333 > rm.txt
cat rm*
rm 333 > rm.txt 2>&1 &
# 0:stdin 1:stdout 2:stderr

#set -x
#set +x

history
history > h.txt

-----

( for i in {0..99} ; do echo line$i ; done ) > a.txt
cat a.txt | head -n 3
cat a.txt | grep line9 | grep -v 99 | tail -n 3 | grep . -n
ps aux | grep nix
top
htop
