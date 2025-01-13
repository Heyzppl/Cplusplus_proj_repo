#include <iostream>
#include <string>
#include <fstream>
#include <limits>

//why do we add obj where it is at?
class registration {
    std::string user_name, email, password;
    std::fstream file;
    std::string search_username, search_email, search_password;

public:
    void login();
    void sign_up();
    void forgot();

}obj;

int main(){
    char choice;

    std::cout << "1. Login\n";
    std::cout << "2. Sign Up\n";
    std::cout << "3. Forgot password\n";
    std::cout << "4. Exit\n";
    std::cin >> choice;


    // have to consume the leftover new line so getline wont read an empty line first
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case '1':
            obj.login();
            break;
        case '2':
            obj.sign_up();
            obj.login();
            break;
        case '3':
            obj.forgot();
            break;
        case '4':
            return 0;
        default:
            std::cout << "This selection you chose is invalid\n" << std::endl;

    }
    
}

//create the signup function
void registration::sign_up() {
    std::cout << "Enter the username: ";
    std::getline(std::cin, user_name);

    std::cout << "Enter the email: ";
    std::getline(std::cin, email);

    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    //here is where you create the logindata.txt file to write the above information
    //ask what is app used for? 
    //why do you add the !file
    file.open("logindata.txt", std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open 'logindata.txt' for writing \n";
        return;
    }
    //why do you add *
    file << user_name << "*" << email << "*" << password << "\n";
    file.close();

    std::cout << "You have signed up successfully!\n\n\n";

}

void registration::login() {
    std::cout << "------------------------\n";
    std::cout << "Enter your username: ";
    std::getline(std::cin, search_username);

    std::cout << "\nEnter your password: ";
    std::getline(std::cin, search_password);

    //open the logindata.txt and instead of out use in to read file inpuit
    file.open("logindata.txt", std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: The file wasn't able to open for reading \n";
        return;
    }

    //why add this?
    bool found = false;
    //while loop to read any lines until we cant read no more
    while (true) {
        //this will read username up until *
        if (!std::getline(file, user_name, '*')) break;
        // This will read password up until * 
        if (!std::getline(file, email, '*')) break;
        //will read password up until there is a newline!
        if (!std::getline(file, password)) break;
        int choice = 1;
        if (user_name == search_username) {
            if (password == search_password) {
                std::cout << "\nYour login was successful!\n";
                std::cout << "Username: " << user_name << "\n";
                std::cout << "Email: " << email << "\n";
                std::cout << "Password: " << password << "\n";
                found = true;
                if (choice == 1) {
                    break;
                }else {
                    std::cout << "There is nothing else to do in this console"; 
                }
            }
        }

    }
    file.close();

    if (!found) {
        std::cout << "The username and password are incorrect.\n\n";
    }
}

void registration::forgot(){
    std::cout << "What is your username: ";
    std::getline(std::cin, search_username);

    std::cout << "\nWhat is your password: ";
    std::getline(std::cin, search_password);

    file.open("logindata.txt", std::ios::in);
    //error statement
    if (!file.is_open()) {
        std::cerr << "Error: this file could not open to read data\n";
        return;
    }

    bool found = false;
    
    while (true) {
        if (!std::getline(file, user_name, '*')) break;
        if (!std::getline(file, email, '*')) break;
        if (!std::getline(file, password, '*')) break;

        if (user_name == search_username && email == search_email) {
            std::cout << "Your account has been found! \n";
            std::cout << "Your password is: " << password << "\n";
            found == true;
            break;
        } 
    }
    file.close();

    if (!found) {
        std::cout << "No account found with that username and email \n\n";
    }

}




