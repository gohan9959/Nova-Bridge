#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "../Dex/Dex.hpp"
#include "../Include/json.hpp"

template <typename T>
class BaseDex {
    protected:
        inline static std::unordered_map<uint16_t, T> dex;
        BaseDex() = default; // Default constructor
    public:
        static void load(const std::string& path){
            std::ifstream file(path);
            if (!file.is_open()) {
                std::cerr << "CRITICAL: Could not load JSON at " << path << std::endl;
                return;
            }
            nlohmann::json data = nlohmann::json::parse(file);
            dex.reserve(data.size());
            for (const auto& entry : data) {
                T obj = T::fromJson(entry);
                dex.emplace(obj.getId(), obj);
            }
        }
        static const T* get(uint16_t id) {
            auto it = dex.find(id);
            if (it != dex.end()) {
                return &(it->second);
            }
            return nullptr; // No dangling reference!
        }
        static bool exists(uint16_t id) {
            return dex.find(id) != dex.end();
        }
};