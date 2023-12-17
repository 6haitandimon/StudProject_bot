#include "user.h"

User::User(std::string firstName, std::string lastName, std::string userId){
    this->userFirsName = firstName;
    this->userLastName = lastName;
    this->userId = userId;
}

std::string User::GetUserId(){
    return this->userId;
}

std::string User::GetFirstName(){
    return this->userFirsName;
}

std::string User::GetLastName(){
    return this->userLastName;
}
std::string User::GetName(){
    return GetFirstName() + " " + GetLastName();
}

void User::SetUserId(std::string userId){
    this->userId = userId;
}

void User::SetUserName(std::string firstName, std::string lastName){
    this->userFirsName = firstName;
    this->userLastName = lastName;
}