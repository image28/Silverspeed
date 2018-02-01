cd common
rm -f lib/*.o
sh cross-compile-w32.sh
cd ..
rm -f *.exe
sh cross-compile-demo-w32.sh
