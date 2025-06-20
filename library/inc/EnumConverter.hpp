#ifndef _WX_ENUM_CONVERTER_HPP
#define _WX_ENUM_CONVERTER_HPP

#include <map>
#include <stdexcept>

namespace wx
{
    template <typename EnumT, typename StringT>
    class EnumConverter
    {
    public:
        using EnumType = EnumT;
        using StringType = StringT;

        // Преобразование enum в строку

        static StringType ToString(EnumType value)
        {
            const auto &map = GetToStringMap();

            if (auto it = map.find(value); it != map.end())
            {
                return it->second;
            }

            throw std::invalid_argument("Invalid enum value");
        }

        // Преобразование строки в enum

        static EnumType FromString(const StringType &str)
        {
            const auto &map = GetFromStringMap();

            auto capitalizedString = str; // str.Capitalize();

            if (auto it = map.find(capitalizedString); it != map.end())
            {
                return it->second;
            }

            throw std::invalid_argument("Invalid enum string: " + str);
        }

    protected:
        static const std::map<EnumType, StringType> &GetToStringMap();
        static const std::map<StringType, EnumType> &GetFromStringMap();
    };
}

#endif // _WX_ENUM_CONVERTER_HPP