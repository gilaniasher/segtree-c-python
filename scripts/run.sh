# sudo apt install python3-dev
gcc $(python3-config --includes) segtree.c -o segtree
./segtree
