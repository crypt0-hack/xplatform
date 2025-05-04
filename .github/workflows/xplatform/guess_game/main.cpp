#include <iostream>

void start();
int generate();
void guessing(int secret, int num_try);


int main() {
    start();

    return 0;
}


void start() {
    int secret = generate();
    // std::cout << secret << std::endl;

    std::cout << "I made a number from 0 to 100. Try to guess it" << std::endl;
    guessing(secret, 0);
}
int generate() {
    srand(time(NULL));
    return (rand() % 100) + 1;
}
int get(char c) {
    switch (c) {
        case '0':
            return 0;

        case '1':
            return 1;

        case '2':
            return 2;

        case '3':
            return 3;

        case '4':
            return 4;

        case '5':
            return 5;

        case '6':
            return 6;

        case '7':
            return 7;

        case '8':
            return 8;

        case '9':
            return 9;

        default:
            return -1;
    }
}
bool is_digital(char c) {
    if (c > 47 && c < 58) {
        return true;
    }

    return false;
}
int validate() {
    std::string str;
    std::cin >> str;

    if (str == "quit") {
        std::cout << "Thanks for playing. And goodbye!" << std::endl;
        exit(0);
    }

    int *a = (int *) malloc(str.size());
    for (int i = 0; i < str.size(); i++) {
        if (is_digital(str[i])) {
            a[i] = get(str[i]);
        } else {
            std::cout << "Wrog input! Please try again!" << std::endl;
            return -1;
        }
    }

    int n = 0;
    for (int i = str.size() - 1, j = 1; i >= 0; i--, j *= 10) {
        n += (a[i] * j);
    }

    return n;
}
void guessing(int secret, int num_try) {
    std::cout << "Enter a guess:  ";
    int guess = validate();
    if (guess == -1) {
        guessing(secret, num_try);
    }

    if (guess == secret) {
        char ans;
        std::cout << std::endl << "You win! My conratulations. You still have " << 10 - num_try << " tryies." << std::endl;

        std::cout << "\n Do you want try again?   y - yes/n - no:  ";
        std::cin >> ans;

        if (ans == 'y') {
            std::cout << "\n\n\n\n\n\n";
            start();
        } else {
            std::cout << "\nGoodbye and thanks for playing" << std::endl;
            exit(0);
        }
    } else if (secret > guess) {
        if (num_try < 10) {
            std::cout << "Secret number is more. You have " << 10 - num_try << " tryes. Try again" << std::endl << std::endl;
            guessing(secret, ++num_try);
        }
        
        std::cout << std::endl << "Sorry. You lost! Secret number was " << secret << std::endl;
    } else {
        if (num_try < 10) {
            std::cout << "Secret number is less. You have " << 10 - num_try << " tryes. Try again" << std::endl << std::endl;
            guessing(secret, ++num_try);
        }
        std::cout << std::endl << "Sorry. You lost! Secret number was " << secret << std::endl;
    }
}
