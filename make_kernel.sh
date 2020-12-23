make olddefconfig
make localmodconfig
make -j`nproc` all
