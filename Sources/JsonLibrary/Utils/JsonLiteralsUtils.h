#pragma once

enum class JsonLiterals
{
    ObjectStart = 0,
    ObjectEnd = 1,
    String = 2,
    ArrayStart = 3,
    ArrayEnd = 4,
    FieldStart = 5,
    Comma = 6,
    Dot = 7,
    Space = 8,
    NewLine = 9,

    Max = 10
};

class JsonLiteralsUtils
{
public:
    static bool IsJsonLiteral(char ch, JsonLiterals jsonLiteral);
    static char GetLiteral(JsonLiterals jsonLiteral);

private:
    static constexpr char k_objectStartLiteral = '{';
    static constexpr char k_objectEndLiteral = '}';
    static constexpr char k_stringLiteral = '\"';
    static constexpr char k_arrayStartLiteral = '[';
    static constexpr char k_arrayEndLiteral = ']';
    static constexpr char k_fieldStartLiteral = ':';
    static constexpr char k_commaLiteral = ',';
    static constexpr char k_dotLiteral = '.';
    static constexpr char k_spaceLiteral = ' ';
    static constexpr char k_newLineLiteral = '\n';

    static char _literals[static_cast<int>(JsonLiterals::Max)];
};
