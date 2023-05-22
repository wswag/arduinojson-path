#include "jsonpath.h"

#define JSON_FIELD_DELIMITER '/'
#define JSON_ARRAY_DELIMITER '#'

JsonVariant JsonPath::execute(JsonVariant src) 
{
    auto v = _compiled(src);
    return v;
}

JsonVariant JsonPath::execute(JsonDocument& src) 
{
    // this is to handle inmplicit member generation correctly (hopefully)
    return execute(src.as<JsonVariant>());
}

JsonPath::JsonPath(const char* path) 
{
    int i = 0;
    int len = strlen(path);

    // starting point
    path_propagation_t f = [](JsonVariant v) -> JsonVariant { return v; };
    while (i != len) {
        char tokenType;
        String token = nextToken(path, i, tokenType);
        int index;
        switch (tokenType) {
            case JSON_FIELD_DELIMITER:
                f = [=](JsonVariant v) -> JsonVariant { return f(v)[token]; };
                break;
            case JSON_ARRAY_DELIMITER:
                index = token.toInt();
                f = [=](JsonVariant v) -> JsonVariant { return f(v)[index]; };
                break;
        }
    }

    _compiled = f;
}

String JsonPath::nextToken(const char* path, int& start, char& tokenType) 
{
    int i = start;
    tokenType = i == 0 
        ? path[0] != JSON_ARRAY_DELIMITER ? JSON_FIELD_DELIMITER : JSON_ARRAY_DELIMITER
        : path[i++];
    while (path[i] != 0 && path[i] != JSON_FIELD_DELIMITER && path[i] != JSON_ARRAY_DELIMITER) {
        i++;
    }
    String token = String(path).substring(start != 0 ? start + 1 : 0, i);
    start = i;
    return token;
}
