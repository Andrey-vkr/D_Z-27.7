#include <iostream>
#include <string>
#include <cstring>
#include "Chat.h"
#include "Sha1.h"
#include <string>



std::string Chat::chatProcessing()
{
    std::string outMessage;

    while (!_sendMessage)
    {
        if (!_isCurrentUser)
        {
            if (_currentMenu == "")
            {
                showLoginMenu();
            }
            else if (_currentMenu == "loginUser")
            {
                outMessage = loginUser();
            }
            else if (_currentMenu == "registerUser")
            {
                outMessage = registerUser();
            }
            else if (_currentMenu == "exitChat")
            {
                outMessage = exitChat();
            }
        }
        else
        {
            if (_currentMenu == "")
            {
                showUserMenu();
            }
            else if (_currentMenu == "getChat")
            {
                outMessage = getChat();
            }
            else if (_currentMenu == "addMessage")
            {
                outMessage = addMessage();
            }
            else if (_currentMenu == "getUsers")
            {
                outMessage = getUsers();
            }
        }
    }

    return outMessage;
}

void Chat::messageProcessing(std::string serverMessage)
{
    _vectorFromMessage = messageToVector(serverMessage, ":");

    if (_vectorFromMessage[0] == "loginUser")
    {
        checkLogin();
    }
    else if (_vectorFromMessage[0] == "registerUser")
    {
        checkRegister();
    }
    else if (_vectorFromMessage[0] == "showChat")
    {
        showChat();
    }
    else if (_vectorFromMessage[0] == "addMessage")
    {
        checkAddMessage();
    }
    else if (_vectorFromMessage[0] == "showUsers")
    {
        showUsers();
    }
}

std::vector<std::string> Chat::messageToVector(std::string message, std::string delimiter)
{
    std::vector<std::string> resultVector;

    if (!message.empty())
    {
        size_t start = 0;
        do
        {
            size_t idx = message.find(delimiter, start);
            if (idx == std::string::npos)
            {
                break;
            }

            size_t length = idx - start;
            resultVector.push_back(message.substr(start, length));
            start += (length + delimiter.size());
        } while (true);

        resultVector.push_back(message.substr(start));
    }

    return resultVector;
}

std::string Chat::loginUser()
{
    std::string login, password, outMessage;
    _sendMessage = true;

    std::cout << "login: ";
    std::cin >> login;
    std::cout << "password: ";
    std::cin >> password;

    const char* passwordChar = password.c_str();

    uint* passHex = sha1(passwordChar, strlen(passwordChar));

    outMessage = "loginUser:" + login + ":" + std::to_string(*passHex);

    return outMessage;
}

void Chat::checkLogin()
{
    std::string checkUser;
    checkUser = _vectorFromMessage[1];
    _sendMessage = false;

    if (checkUser == "error")
    {
        _isCurrentUser = false;
        std::cout << "Incorrect password or login" << std::endl;
        showLoginMenu();
    }
    else if (checkUser == "ok")
    {
        _isCurrentUser = true;
        _currentMenu = "";
        _currentUserName = _vectorFromMessage[2];
    }
}

std::string Chat::registerUser()
{
    std::string login, password, name, outMessage;
    _sendMessage = true;

    std::cout << "login: ";
    do
    {
        std::cin >> login;
    } while (login == "all");
    std::cout << "password: ";
    std::cin >> password;
    std::cout << "name: ";
    do
    {
        std::cin >> name;
    } while (login == "all");

    const char* passwordChar = password.c_str();

    uint* passHex = sha1(passwordChar, strlen(passwordChar));

    outMessage = "registerUser:" + login + ":" + std::to_string(*passHex) + ":" + name;

    return outMessage;
}

void Chat::checkRegister()
{
    std::string checkUser, isNameOrLogin;
    checkUser = _vectorFromMessage[1];
    isNameOrLogin = _vectorFromMessage[2];
    _sendMessage = false;

    if (checkUser == "error")
    {
        _isCurrentUser = false;
        if (isNameOrLogin == "login")
        {
            std::cout << "login is busy!" << std::endl;
        }
        else if (isNameOrLogin == "name")
        {
            std::cout << "name is busy!" << std::endl;
        }
        showLoginMenu();
    }
    else if (checkUser == "ok")
    {
        _isCurrentUser = true;
        _currentMenu = "";
        _currentUserName = _vectorFromMessage[2];
    }
}

std::string Chat::exitChat()
{
    _sendMessage = true;
    std::cout << "Exiting the chat" << std::endl;
    return "exit";
}

void Chat::startMessage()
{
    std::cout << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "                       CHAT                        " << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
}

void Chat::showLoginMenu()
{
    char operation;
    std::string outMessage;
    _sendMessage = false;

    std::cout << std::endl;
    std::cout << "Enter the required value:" << std::endl;
    std::cout << "___________________________________________________" << std::endl;
    std::cout << std::endl;
    std::cout << "To enter login      | 1 |" << std::endl;
    std::cout << "To register in chat | 2 |" << std::endl;
    std::cout << "To exit chat        | 3 |" << std::endl;
    std::cout << "___________________________________________________" << std::endl;
    std::cout << "__ ";
    std::cin >> operation;
    std::cout << std::endl;

    switch (operation)
    {
    case '1':
        _currentMenu = "loginUser";
        break;

    case '2':
        _currentMenu = "registerUser";
        break;

    case '3':
        _currentMenu = "exitChat";
        break;

    default:
        std::cout << "1 or 2 or 3" << std::endl;
        _currentMenu = "";
        break;
    }
}

void Chat::showUserMenu()
{
    char operation;
    std::string outMessage;
    _sendMessage = false;

    std::cout << std::endl;
    std::cout << "___________________________________________________" << std::endl;
    std::cout << "Watch chat    | 1 |" << std::endl;
    std::cout << "Add a message | 2 |" << std::endl;
    std::cout << "looke users   | 3 |" << std::endl;
    std::cout << "Exit chat     | 4 |" << std::endl;
    std::cout << "___________________________________________________" << std::endl;
    std::cout << "__ ";
    std::cin >> operation;

    switch (operation)
    {
    case '1':
        _currentMenu = "getChat";
        break;

    case '2':
        _currentMenu = "addMessage";
        break;

    case '3':
        _currentMenu = "getUsers";
        break;

    case '4':
        _isCurrentUser = false;
        _currentMenu = "";
        break;

    default:
        std::cout << "unknown choice " << std::endl;
        _currentMenu = "";
        break;
    }
}

std::string Chat::addMessage()
{
    std::string from, to, text, outMessage;
    _sendMessage = true;
    from = _currentUserName;
    std::cout << "Enter <username> or <all> to send a message" << std::endl;
    std::cin >> to;
    std::cout << "Text: ";
    std::cin.ignore();
    std::getline(std::cin, text);

    outMessage = "addMessage:" + from + ":" + to + ":" + text;

    return outMessage;
}

void Chat::checkAddMessage()
{
    _sendMessage = false;
    std::string checkMessage;
    checkMessage = _vectorFromMessage[1];

    if (checkMessage == "error")
    {
        _currentMenu = "";
        std::cout << "failed to send message to user";
        std::cout << _vectorFromMessage[2] << ">>>" << std::endl;
    }
    else if (checkMessage == "ok")
    {
        _currentMenu = "";
    }
}

std::string Chat::getUsers()
{
    std::string outMessage;
    _sendMessage = true;

    outMessage = "showUsers:" + _currentUserName;

    return outMessage;
}

std::string Chat::getChat()
{
    std::string outMessage;
    _sendMessage = true;

    outMessage = "showChat:" + _currentUserName + ":showChat";

    return outMessage;
}

void Chat::showChat()
{
    std::string from, to;
    _sendMessage = false;
    std::cout << "                 _________________                 " << std::endl;
    std::cout << "                        CHAT                       " << std::endl;
    std::cout << "                 _________________                 " << std::endl;


    if (_vectorFromMessage[1] == "empty")
    {
        std::cout << "empty" << std::endl;
    }
    else
    {
        for (int i = 1; i < _vectorFromMessage.size() - 1; i += 3)
        {
            std::cout << "Message from " << _vectorFromMessage[i];
            std::cout << " to " << _vectorFromMessage[i + 1] << std::endl;
            std::cout << "Message text: " << _vectorFromMessage[i + 2] << std::endl;
        }
    }

    _currentMenu = "";
}

void Chat::showUsers()
{
    _sendMessage = false;
    std::cout << "                 __________________                " << std::endl;
    std::cout << "                     All users                     " << std::endl;
    std::cout << "                 __________________                " << std::endl;


    for (int i = 1; i < _vectorFromMessage.size() - 1; i++)
    {
        std::cout << _vectorFromMessage[i] << std::endl;
    }

    _currentMenu = "";
}