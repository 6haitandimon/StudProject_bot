#pragma once

#include <string>

class User {
    private:
        std::string userFirsName;
        std::string userLastName;
        std::string userId;
        uint32_t direction;
        
    public:
        User(std::string firstName, std::string lastName, std::string userId);
        std::string GetUserId();
        std::string GetFirstName();
        std::string GetLastName();
        std::string GetName();
        void SetUserId(std::string userId);
        void SetUserName(std::string firstName, std::string lastName);
    
};