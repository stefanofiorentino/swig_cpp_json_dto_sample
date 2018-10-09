#include "util/bean.hpp"

class example
{
    std::string id;
public:
    example() = default;

    explicit example (Json::Value const & root) :
        id(root["id"].asString())
    {}

    explicit example (std::string const & str) :
        example(fromStringtoJsonValue(str))
    {}

    Json::Value toJsonValue() const
    {
        Json::Value jsonValue;
        jsonValue["id"]=id;
        return jsonValue;
    }

    std::string toJsonString() const
    {
        return this->toJsonValue().toStyledString();
    }
};
