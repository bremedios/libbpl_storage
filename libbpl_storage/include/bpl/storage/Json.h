//
// Created by Bradley Remedios on 11/15/24.
//

#ifndef BPL_STORAGE_JSON_H
#define BPL_STORAGE_JSON_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "rapidjson/document.h"

#include "Payload.h"

namespace bpl::storage {
    class Json {
    public:
        static bool Load(const rapidjson::Value& value, const std::string& name, bool &loadedValue);
        static bool Load(const rapidjson::Value& value, const std::string& name, int &loadedValue);
        static bool Load(const rapidjson::Value& value, const std::string& name, std::string& loadedValue);
        static bool Load(const rapidjson::Value& value, const std::string& name, SDL_Color& color);
        static bool Load(const rapidjson::Value& value, const std::string& name, SDL_Rect& rect);
        static bool Load(const rapidjson::Value& value, const std::string& name, std::pair<int, int>& pairValue);

        static std::shared_ptr<rapidjson::Document> Open(const std::string& name);
        static std::shared_ptr<rapidjson::Document> Open(const storage::Payload& payload);
    };
} // bpl::storage

#endif // BPL_STORAGE_JSON_H
