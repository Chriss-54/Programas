#include "api_handler.h"
#include <string>
#include <iostream>
#include <curl/curl.h>
#include "json.hpp"  // Añadido para manejar JSON

using json = nlohmann::json;

static std::string apiKey = "AIzaSyDr8bVFqyvhkrFD3KIZ2t21NUZChewbx7c";


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string translateWord(const std::string& word) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://translation.googleapis.com/language/translate/v2?key=" + apiKey + "&q=" + word + "&target=es";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }

    // Parsear el JSON para obtener la traducción
    auto jsonResponse = json::parse(readBuffer);
    try {
        std::string translatedText = jsonResponse["data"]["translations"][0]["translatedText"];
        return translatedText;
    } catch (json::exception& e) {
        std::cerr << "Error al parsear la respuesta JSON: " << e.what() << std::endl;
        return "";
    }
}
