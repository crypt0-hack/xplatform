#include <iostream>
#include <math.h>
#include <random>

#define uint64_t u_int64_t

uint64_t rand_64() {
     std::random_device rd;
     std::mt19937_64 gen(rd());
     std::uniform_int_distribution<uint64_t> dis;

     return (dis(gen));
}

static uint64_t p, q;

struct private_t {
     uint64_t d;
     uint64_t n;
};
struct public_t {
     uint64_t e;
     uint64_t n;
};

bool is_prime(uint64_t n);
uint64_t prime();

uint64_t gcd(uint64_t m, uint64_t n);
uint64_t ext_gcd(uint64_t m, uint64_t n, int64_t &x, int64_t &y);

uint64_t phi(uint64_t n);
uint64_t e_gen(uint64_t n);
uint64_t modinv(uint64_t e, uint64_t n);
uint64_t mod_pow(uint64_t x, uint64_t y, uint64_t m);


int main() {
     srand(time(NULL));
     do {
          p = prime();
          q = prime();
     } while (p == q);
     
     uint64_t n = p * q;
     uint64_t e = e_gen(n), d = modinv(e, n);

     std::cout << "p: " << p << " q: " << q << std::endl;
     std::cout << "n: " << n << std::endl;
     std::cout << "e: " << e << " d: " << d << std::endl;

     public_t pub = { e, n };
     private_t priv = { d, n };

     uint64_t m = 2;
     uint64_t c = mod_pow(m, pub.e, pub.n);
     std::cout << "crypt: " << c << std::endl;
     uint64_t dc = mod_pow(c, priv.d, priv.n);
     std::cout << "decrypt: " << dc << std::endl;

     return 0;
}


bool is_prime(uint64_t n) {
     if (n <= 1) {
          return false;
     }
     if (n <= 3) {
          return true;
     }

     if (n % 2 == 0) {
          return false;
     }

     for (uint64_t i = 3; i <= sqrt(n); i += 2) {
          if (n % i == 0) {
               return false;
          }
     }

     return true;
}
uint64_t prime() {
     uint64_t n;
     do {
          n = ((uint64_t)rand_64() << 32) | rand_64();
     } while (!is_prime(n));

     return n;
}

uint64_t gcd(uint64_t m, uint64_t n) {
     uint64_t r = m % n;
     return ((r == 0) ? n : gcd(n, r));
}
uint64_t ext_gcd(uint64_t m, uint64_t n, int64_t &x, int64_t &y) {
     if (m == 0) {
          x = 0;
          y = 1;
          return n;
     }

     int64_t x1, y1;
     uint64_t t_gcd = ext_gcd(n % m, m, x1, y1);

     x = y1 - (n / m) * x1;
     y = x1;

     return t_gcd;
}

uint64_t phi(uint64_t n) {
     return ((p - 1) * (q - 1));
}
uint64_t e_gen(uint64_t n) {
     uint64_t e = 65537;
     for (; gcd(e, phi(n)) != 1; e += 2);

     return e;
}
uint64_t modinv(uint64_t e, uint64_t n) {
     int64_t x, y;
     uint64_t t_gcd;
     t_gcd = ext_gcd(e, phi(n), x, y);

     if (t_gcd != 1) {
          std::cout << "modinv err" << std::endl;
          exit(EXIT_FAILURE);
     }

     return ((x % phi(n) + phi(n)) % phi(n));
}
uint64_t mod_pow(uint64_t x, uint64_t y, uint64_t m) {
     uint64_t res = 1;
     x %= m;

     while (y > 0) {
          if (y % 2 == 1) {
               res = (res * x) % m;
          }

          x = (x * x) % m;
          y >>= 1;
     }

     return res;
}
