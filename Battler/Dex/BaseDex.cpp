#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "../Include/json.hpp"

template <typename T>
class BaseDex {
    protected:
        static std::unordered_map<uint16_t, T> dex;
    public:
        BaseDex() = delete; // Prevent instantiation of the BaseDex class
        static void load(const std::string& path){
            std::ifstream file(path);
            if (!file.is_open()) {
                std::cerr << "CRITICAL: Could not load JSON at " << path << std::endl;
                return;
            }
            nlohmann::json data = nlohmann::json::parse(file);
            for (const auto& entry : data) {
                T obj = T::fromJson(entry);
                dex[obj.id] = obj;
            }
        }
        static const T& get(uint16_t id) {
            auto it = dex.find(id);
            if (it != dex.end()) {
                return it->second;
            }
            return T::makeEmpty(); // Return a default T if the ID is not found
        }
        static bool exists(uint16_t id) {
            return dex.find(id) != dex.end();
        }
};

template <typename T>
std::unordered_map<uint16_t, T> BaseDex<T>::dex;