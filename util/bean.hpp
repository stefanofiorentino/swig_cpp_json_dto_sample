#include <json/json.h>

inline Json::Value fromStringtoJsonValue(std::string const &in)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(in, root);
    if (!parsingSuccessful)
    {
        throw std::runtime_error(reader.getFormattedErrorMessages());
    }
    return root;
}