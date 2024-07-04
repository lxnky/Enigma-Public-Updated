#pragma once
#include "../../includes.hpp"
#include "auth.hpp"
#include "json.hpp"
using namespace KeyAuth;

std::string name = _("Enigma");
std::string ownerid = _("GDzvWuQQ86");
std::string secret = _("b63984682223eff4eeadf031ebd050d1c9d8fabc020e0a6955552377279ab13f");
std::string version = _("1.0");
std::string url = _("https://keyauth.win/api/1.2/");


api KeyAuthApp(name, ownerid, secret, version, url);
using json = nlohmann::json;

std::string ReadFromJson(std::string path, std::string section)
{
    if (!std::filesystem::exists(path))
        return _("File Not Found");
    std::ifstream file(path);
    json data = json::parse(file);
    return data[section];
}

bool CheckIfJsonKeyExists(std::string path, std::string section)
{
    if (!std::filesystem::exists(path))
        return _("File Not Found");
    std::ifstream file(path);
    json data = json::parse(file);
    return data.contains(section);
}
bool WriteToJson(std::string path, std::string name, std::string value, bool userpass, std::string name2, std::string value2)
{
    json file;
    if (!userpass)
    {
        file[name] = value;
    }
    else
    {
        file[name] = value;
        file[name2] = value2;
    }

    std::ofstream jsonfile(path, std::ios::out);
    jsonfile << file;
    jsonfile.close();
    if (!std::filesystem::exists(path))
        return false;

    return true;
}

auto get_folder() -> string
{
    char* pbuf = nullptr;
    size_t len = 0;
    if (!_dupenv_s(&pbuf, &len, _("appdata")) && pbuf && strnlen_s(pbuf, MAX_PATH))
    {
        std::string settings_path;
        settings_path.append(pbuf);
        settings_path.append(_("\\Enigma\\"));
        CreateDirectory(settings_path.c_str(), 0);
        free(pbuf);
        return settings_path;
    }
}
auto get_key() -> string {
    return get_folder() + _("\\key.json");
}
auto auth() -> void
{

    //std::cout << _("\n\n Connecting..");
    KeyAuthApp.init();
    if (!KeyAuthApp.data.success)
    {
        std::cout << _("\n Status: ") << KeyAuthApp.data.message;
        Sleep(1500);
        exit(0);
    }

    if (std::filesystem::exists(get_key()))
    {
        if (!CheckIfJsonKeyExists(get_key(), _("username")))
        {
            std::string key = ReadFromJson(get_key(), _("license"));
            KeyAuthApp.license(key);
            if (!KeyAuthApp.data.success)
            {
                std::remove(_("key.json"));
                std::cout << _("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(0);
            }
            std::cout << _("\n\n Successfully Automatically Logged In\n");
        }
        else
        {
            std::string username = ReadFromJson(get_key(), _("username"));
            std::string password = ReadFromJson(get_key(), _("password"));
            KeyAuthApp.login(username, password);
            if (!KeyAuthApp.data.success)
            {
                std::remove(_("key.json"));
                std::cout << _("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(0);
            }
            std::cout << _("\n\n Successfully Automatically Logged In\n");
        }
    }
    else
    {
        std::cout << _("\n\n [1] Login\n [2] Register\n [3] License key only\n\n Choose option: ");

        int option;
        std::string username;
        std::string password;
        std::string key;

        std::cin >> option;
        switch (option)
        {
        case 1:
            std::cout << _("\n\n Enter username: ");
            std::cin >> username;
            std::cout << _("\n Enter password: ");
            std::cin >> password;
            KeyAuthApp.login(username, password);
            break;
        case 2:
            std::cout << _("\n\n Enter username: ");
            std::cin >> username;
            std::cout << _("\n Enter password: ");
            std::cin >> password;
            std::cout << _("\n Enter license: ");
            std::cin >> key;
            KeyAuthApp.regstr(username, password, key);
            break;
        case 3:
            std::cout << _("\n Enter license: ");
            std::cin >> key;
            KeyAuthApp.license(key);
            break;
        default:
            std::cout << _("\n\n Status: Failure: Invalid Selection");
            Sleep(3000);
            exit(0);
        }

        if (!KeyAuthApp.data.success)
        {
            std::cout << _("\n Status: ") << KeyAuthApp.data.message;
            Sleep(1500);
            exit(0);
        }
        if (username.empty() || password.empty())
        {
            WriteToJson(get_key(), _("license"), key, false, _(""), _(""));
            std::cout << _("\n Successfully Created File For Auto Login\n");
        }
        else
        {
            WriteToJson(get_key(), _("username"), username, true, _("password"), password);
            std::cout << _("\n Successfully Created File For Auto Login\n");
        }


    }
    Sleep(2000);



}