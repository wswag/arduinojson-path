#ifndef JSONPATH_H
#define JSONPATH_H

#include <ArduinoJson.h>
#include <functional>

typedef std::function<JsonVariant (JsonVariant)> path_propagation_t;

class JsonPath {
    private:
        path_propagation_t _compiled;

        String nextToken(const char* path, int& start, char& tokenType);
    public:
        JsonPath(const char* path);
        JsonVariant execute(JsonVariant src);
        JsonVariant execute(JsonDocument& src);
};

#endif /* JSONPATH_H */
