#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

bool check_num(std::string cn, std::string pin);
bool check(std::string un, std::string pwd);
bool is_digit(char c);

std::string intro();

void start();
void welcome();
void withdraw(std::string cn);
void replenish(std::string cn);
void check(std::string cn);
void update(int index, int n);
void update(std::string cn, std::string pin);
void work(std::string cn, std::string pin);
void login(std::string cn, std::string pin);
void add();
void bye();
int cin();

int get(char c);
int get(int *i, std::string cn);
int get(std::string cn);
