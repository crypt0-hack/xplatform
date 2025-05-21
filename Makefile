avios:
	clang ./crypto/crypt.c -c -o ./crypto/crypt
	clang ./memory/malloc.c -c -o ./memory/malloc
	clang ./secure_sys/reg_log_sys.c -c -o ./secure_sys/secure

	clang avios.c -o avios ./crypto/crypt ./memory/malloc ./secure_sys/secure
	rm ./crypto/crypt ./memory/malloc ./secure_sys/secure