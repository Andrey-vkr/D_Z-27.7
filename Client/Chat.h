#pragma once
#include <string.h>
#include <vector>
#include <exception>
#include <memory>



class Chat
{
public:
    std::string chatProcessing();
    void messageProcessing(std::string serverMessage);
    void startMessage();

private:
    bool _sendMessage = false;
    bool _isCurrentUser = false;
    std::string _currentUserName;
    std::string _currentMenu = "";
    std::vector<std::string> _vectorFromMessage;

    void showLoginMenu();
    std::string loginUser();
    std::string registerUser();
    void checkRegister();
    void checkLogin();
    std::string exitChat();

    void showUserMenu();
    std::string getChat();
    std::string addMessage();
    std::string getUsers();
    void showChat();
    void checkAddMessage();
    void showUsers();

    std::vector<std::string> messageToVector(std::string message, std::string delimiter);
};