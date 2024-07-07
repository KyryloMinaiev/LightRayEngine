#include "JsonLiteralsUtils.h"

namespace JsonLibrary {
    char JsonLiteralsUtils::_literals[static_cast<int>(JsonLiterals::Max)] =
            {
                    k_objectStartLiteral,
                    k_objectEndLiteral,
                    k_stringLiteral,
                    k_arrayStartLiteral,
                    k_arrayEndLiteral,
                    k_fieldStartLiteral,
                    k_commaLiteral,
                    k_dotLiteral,
                    k_spaceLiteral,
                    k_newLineLiteral
            };

    bool JsonLiteralsUtils::IsJsonLiteral(char ch, JsonLiterals jsonLiteral) {
        if (jsonLiteral >= JsonLiterals::Max) {
            return false;
        }

        const char literal = _literals[static_cast<int>(jsonLiteral)];
        return literal == ch;
    }

    char JsonLiteralsUtils::GetLiteral(JsonLiterals jsonLiteral) {
        if (jsonLiteral >= JsonLiterals::Max) {
            return -1;
        }

        return _literals[static_cast<int>(jsonLiteral)];
    }
}
