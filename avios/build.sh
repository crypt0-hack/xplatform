clang malloc.c -c -o malloc
clang crypt.c -c -o crypt
clang reg_log_sys.c -c -o reg_log

clang avios.c malloc crypt reg_log -o avios
rm crypt malloc reg_log
