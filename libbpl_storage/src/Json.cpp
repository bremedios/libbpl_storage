//
// Created by Bradley Remedios on 11/15/24.
//
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "bpl/storage/Json.h"

#include "Debug.h"

namespace bpl::storage {
    bool Json::Load(const rapidjson::Value& value, const std::string& name, bool &loadedValue) {
        if (!value.GetObject().HasMember(name.c_str())) {
            return false;
        }

        if (!value.GetObject()[name.c_str()].IsBool()) {
            ERROR_MSG("[bool]: Invalid type for " << name);

            return false;
        }

        loadedValue = value.GetObject()[name.c_str()].GetBool();

        return true;
    } // Load (Bool)

    bool Json::Load(const rapidjson::Value& value, const std::string& name, int &loadedValue) {
        if (!value.GetObject().HasMember(name.c_str())) {
            return false;
        }

        if (!value.GetObject()[name.c_str()].IsInt()) {
            ERROR_MSG("[int]: Invalid type for " << name);

            return false;
        }

        loadedValue = value.GetObject()[name.c_str()].GetInt();

        return true;
    } // Load (Int)

    bool Json::Load(const rapidjson::Value& value, const std::string& name, std::string& loadedValue) {
        if (!value.GetObject().HasMember(name.c_str())) {
            return false;
        }

        if (!value.GetObject()[name.c_str()].IsString()) {
            ERROR_MSG("[std::string&]: Invalid type for " << name);

            return false;
        }

        loadedValue = value.GetObject()[name.c_str()].GetString();

        return true;
    } // Load (String)

    bool Json::Load(const rapidjson::Value& value, const std::string& name, SDL_Color& color) {
        if (!value.GetObject().HasMember(name.c_str())) {
            return false;
        }

        if (!value.GetObject()[name.c_str()].IsArray()) {
            ERROR_MSG("[SDL_Color&]: Invalid format for color (Must be array)");

            return false;
        }

        if (value.GetObject()[name.c_str()].Size() != 4) {
            ERROR_MSG("Color only has " << std::to_string(value.GetObject()[name.c_str()].Size()) << " elements");

            return false;
        }

        color.r = value.GetObject()[name.c_str()][0].GetInt();
        color.g = value.GetObject()[name.c_str()][1].GetInt();
        color.b = value.GetObject()[name.c_str()][2].GetInt();
        color.a = value.GetObject()[name.c_str()][3].GetInt();

        DEBUG_MSG("Loaded Color: " << name << "RGBA(" << std::to_string(color.r) << "," << std::to_string(color.g) << "," << std::to_string(color.b) << "," << std::to_string(color.a) << ")");

        return true;
    } // Load (SDL_Color)

    bool Json::Load(const rapidjson::Value& value, const std::string& name, std::pair<int, int>& pairValue) {
        if (!value.GetObject().HasMember(name.c_str())) {
            return false;
        }

        if (!value.GetObject()[name.c_str()].IsArray()) {
            ERROR_MSG("[std::pair<int,int>: Invalid format for color (Must be array)");

            return false;
        }

        if (value.GetObject()[name.c_str()].Size() != 2) {
            ERROR_MSG("[std::pair<int,int>: Color only has " << std::to_string(value.GetObject()[name.c_str()].Size()) << " elements");

            return false;
        }

        pairValue.first = value.GetObject()[name.c_str()][0].GetInt();
        pairValue.second = value.GetObject()[name.c_str()][1].GetInt();

        return true;
    } // Load (std::pair<int, int>)

    bool Json::Load(const rapidjson::Value& value, const std::string& name, SDL_Rect& rect) {
        if (!value.GetObject().HasMember(name.c_str())) {
            return false;
        }

        if (!value.GetObject()[name.c_str()].IsArray()) {
            ERROR_MSG("[SDL_Rect&]: Not an array type: " << name);

            return false;
        }

        if (value.GetObject()[name.c_str()].Size() != 4) {
            ERROR_MSG("[SDL_Rect&]: Destination only has " << std::to_string(value.GetObject()[name.c_str()].Size()) << " elements");

            return false;
        }

        // ensure everything is an int.
        for (int i = 0; i < 4; ++i) {
            if (!value.GetObject()[name.c_str()][i].IsInt()) {
                return false;
            }
        }

        rect.x = value.GetObject()[name.c_str()][0].GetInt();
        rect.y = value.GetObject()[name.c_str()][1].GetInt();
        rect.w = value.GetObject()[name.c_str()][2].GetInt();
        rect.h = value.GetObject()[name.c_str()][3].GetInt();

        return true;
    } // (SDL_Rect)

    std::shared_ptr<rapidjson::Document> Json::Open(const std::string& filename) {
        auto jsonDoc = std::make_shared<rapidjson::Document>();

        std::ifstream ifs(filename);
        rapidjson::IStreamWrapper isw(ifs);

        jsonDoc->ParseStream(isw);

        if (!jsonDoc->IsObject()) {
            std::cerr << "Error opening file " << filename << std::endl;

            return std::make_shared<rapidjson::Document>(nullptr);
        }

        return jsonDoc;
    } // Open

    std::shared_ptr<rapidjson::Document> Json::Open(const storage::Payload& payload) {
        rapidjson::StringStream ss(payload.getData());

        auto jsonDoc = std::make_shared<rapidjson::Document>();

        jsonDoc->ParseStream(ss);

        if (!jsonDoc->IsObject()) {
            std::cerr << "Error opening json from payload" << std::endl;

            return std::make_shared<rapidjson::Document>(nullptr);
        }

        return jsonDoc;
    } // Open

} // bpl::storage