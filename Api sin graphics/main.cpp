#include "SplayTree.h"
#include <iostream>
#include <string>
#include <limits>
#include <curl/curl.h>
#include <json/json.h> // Necesitarás la biblioteca JsonCpp

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string translateWithAPI(const std::string& word, const std::string& from, const std::string& to) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://api.mymemory.translated.net/get?q=" + word + "&langpair=" + from + "|" + to;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "Error de traducción";
        }

        // Parsear la respuesta JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(readBuffer, root);
        if (!parsingSuccessful) {
            std::cerr << "Failed to parse JSON" << std::endl;
            return "Error al procesar la respuesta";
        }

        return root["responseData"]["translatedText"].asString();
    }

    return "Error de traducción";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    SplayTree dictionary;
    
    int choice;
    std::string englishWord, spanishWord;

    do {
        std::cout << "\n--- Diccionario Inglés-Español con API ---\n";
        std::cout << "1. Agregar nueva palabra al diccionario local\n";
        std::cout << "2. Buscar traducción (local y API)\n";
        std::cout << "3. Eliminar palabra del diccionario local\n";
        std::cout << "4. Mostrar todo el diccionario local\n";
        std::cout << "5. Salir\n";
        std::cout << "Elige una opción: ";
        std::cin >> choice;
        clearInputBuffer();

        switch(choice) {
            case 1:
                std::cout << "Ingresa la palabra en inglés: ";
                std::getline(std::cin, englishWord);
                std::cout << "Ingresa la traducción en español: ";
                std::getline(std::cin, spanishWord);
                dictionary.insert(englishWord, spanishWord);
                std::cout << "Palabra agregada exitosamente al diccionario local.\n";
                break;
            case 2:
                std::cout << "Ingresa la palabra en inglés que quieres traducir: ";
                std::getline(std::cin, englishWord);
                spanishWord = dictionary.search(englishWord);
                if (spanishWord != "Not found") {
                    std::cout << "Traducción (local): " << spanishWord << "\n";
                } else {
                    std::cout << "Palabra no encontrada en el diccionario local. Buscando con API...\n";
                    spanishWord = translateWithAPI(englishWord, "en", "es");
                    std::cout << "Traducción (API): " << spanishWord << "\n";
                }
                break;
            case 3:
                std::cout << "Ingresa la palabra en inglés que quieres eliminar del diccionario local: ";
                std::getline(std::cin, englishWord);
                dictionary.remove(englishWord);
                std::cout << "Palabra eliminada del diccionario local (si existía).\n";
                break;
            case 4:
                std::cout << "\nDiccionario local completo:\n";
                dictionary.printDictionary();
                break;
            case 5:
                std::cout << "Gracias por usar el diccionario. ¡Hasta luego!\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor, intenta de nuevo.\n";
        }
    } while (choice != 5);

    return 0;
}