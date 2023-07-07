/*
 * Copyright (c) 2023, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "EDF/String.hpp"

#include <iostream>

static void examples() {
    // tag::init_str_literal_char[]
    const char strLiteralChar[] = "const char*";
    // end::init_str_literal_char[]
    // tag::init_p_literal_char[]
    const char* pLiteralChar = strLiteralChar;
    // end::init_p_literal_char[]

    // tag::init_str_literal_uint8_t[]
    const uint8_t strLiteralUint8_t[] = "const uint8_t*";
    // end::init_str_literal_uint8_t[]
    // tag::init_p_literal_uint8_t[]
    const uint8_t* pLiteralUint8_t = strLiteralUint8_t;
    // end::init_p_literal_uint8_t[]

    // tag::init_literal_int8_t[]
    int8_t valueInt8_t = 0xA5;
    // end::init_literal_int8_t[]
    // tag::init_literal_int16_t[]
    int16_t valueInt16_t = 0xA5A5;
    // end::init_literal_int16_t[]
    // tag::init_literal_int32_t[]
    int32_t valueInt32_t = 0xA5A5A5A5;
    // end::init_literal_int32_t[]
    // tag::init_literal_int64_t[]
    int64_t valueInt64_t = 0xA5A5A5A5A5A5A5A5;
    // end::init_literal_int64_t[]
    // tag::init_literal_uint8_t[]
    uint8_t valueUint8_t = 0xA5;
    // end::init_literal_uint8_t[]
    // tag::init_literal_uint16_t[]
    uint16_t valueUint16_t = 0xA5A5;
    // end::init_literal_uint16_t[]
    // tag::init_literal_uint32_t[]
    uint32_t valueUint32_t = 0xA5A5A5A5;
    // end::init_literal_uint32_t[]
    // tag::init_literal_uint64_t[]
    uint64_t valueUint64_t = 0xA5A5A5A5A5A5A5A5;
    // end::init_literal_uint64_t[]
    // tag::init_literal_char[]
    char ch = 'h';
    // end::init_literal_char[]
    // tag::init_literal_different_sized_string[]
    EDF::String<8> differentSizedString = "Hello";
    // end::init_literal_different_sized_string[]

    // tag::init_default[]
    EDF::String<128> stringDefault;
    // end::init_default[]

    // tag::init[]
    EDF::String<128> string = "Hello, world!";;
    // end::init[]

    // tag::init_const_char_star[]
    EDF::String<32> stringConstCharStar = "const char*";
    EDF::String<32> stringConstCharStar2( "const char*" );
    // end::init_const_char_star[]
    // tag::init_const_uint8_t_star[]
    EDF::String<32> stringConstUint8_tStar = pLiteralUint8_t;
    EDF::String<32> stringConstUint8_tStar2( pLiteralUint8_t );
    // end::init_const_uint8_t_star[]
    // tag::init_const_char_star_n[]
    EDF::String<32> stringConstCharStarN( pLiteralChar, std::strlen( strLiteralChar ) );
    // end::init_const_char_star_n[]
    // tag::init_const_uint8_t_star_n[]
    EDF::String<32> stringConstUint8_tStarN( pLiteralUint8_t, std::strlen( reinterpret_cast<const char*>( strLiteralUint8_t ) ) );
    // end::init_const_uint8_t_star_n[]

    // tag::init_const_char_ref[]
    EDF::String<32> stringConstCharStarRef( strLiteralChar );
    // end::init_const_char_ref[]
    // tag::init_const_uint8_t_ref[]
    EDF::String<32> stringConstUint8_tStarRef( strLiteralUint8_t );
    // end::init_const_uint8_t_ref[]

    // tag::init_char[]
    EDF::String<32> stringChar = 'C';
    EDF::String<32> stringChar2( 'C' );
    // end::init_char[]

    // tag::init_int8_t[]
    EDF::String<32> stringInt8_t( valueInt8_t );
    EDF::String<32> stringInt8_tHex( valueInt8_t, 16 );
    // end::init_int8_t[]

    // tag::init_int16_t[]
    EDF::String<32> stringInt16_t( valueInt16_t );
    EDF::String<32> stringInt16_tHex( valueInt16_t, 16 );
    // end::init_int16_t[]

    // tag::init_int32_t[]
    EDF::String<32> stringInt32_t( valueInt32_t );
    EDF::String<32> stringInt32_tHex( valueInt32_t, 16 );
    // end::init_int32_t[]

    // tag::init_int64_t[]
    EDF::String<32> stringInt64_t( valueInt64_t );
    EDF::String<32> stringInt64_tHex( valueInt64_t, 16 );
    // end::init_int64_t[]

    // tag::init_uint8_t[]
    EDF::String<32> stringUint8_t( valueUint8_t );
    EDF::String<32> stringUint8_tHex( valueUint8_t, 16 );
    // end::init_uint8_t[]

    // tag::init_uint16_t[]
    EDF::String<32> stringUint16_t( valueUint16_t );
    EDF::String<32> stringUint16_tHex( valueUint16_t, 16 );
    // end::init_uint16_t[]

    // tag::init_uint32_t[]
    EDF::String<32> stringUint32_t( valueUint32_t );
    EDF::String<32> stringUint32_tHex( valueUint32_t, 16 );
    // end::init_uint32_t[]

    // tag::init_uint64_t[]
    EDF::String<32> stringUint64_t( valueUint64_t );
    EDF::String<32> stringUint64_tHex( valueUint64_t, 16 );
    // end::init_uint64_t[]

    // tag::init_string[]
    EDF::String<32> stringEDFString = differentSizedString;
    EDF::String<32> stringEDFString2( differentSizedString );
    // end::init_string[]

    // tag::is_question_empty[]
    if( !string.isEmpty() ) {
        /* ... */
    }
    // end::is_question_empty[]

    // tag::is_question_full[]
    if( !string.isFull() ) {
        /* ... */
    }
    // end::is_question_full[]

    // tag::capacity_length[]
    auto nCharactersInString = string.length();
    // end::capacity_length[]
    // tag::capacity_max_length[]
    constexpr auto maxNumberOfCharacters = string.maxLength();
    // end::capacity_max_length[]

    // tag::element_access_standard[]
    string[0_uz] = 'h';
    // end::element_access_standard[]

    // tag::element_access_at[]
    string.at( 0_uz ) = 'h';
    // end::element_access_at[]

    // tag::element_access_as_c_string[]
    const char* cString = string.asCString();
    // end::element_access_as_c_string[]

    // tag::element_access_as_byte_data[]
    const uint8_t* byteData = string.asByteData();
    // end::element_access_as_byte_data[]

    // tag::conversion_to_int8_t[]
    int8_t valueInt8_tBase10 = stringInt8_t.toInt8_t();
    int8_t valueInt8_tBase16 = stringInt8_tHex.toInt8_t( 16 );
    // end::conversion_to_int8_t[]

    // tag::conversion_to_int16_t[]
    int16_t valueInt16_tBase10 = stringInt16_t.toInt16_t();
    int16_t valueInt16_tBase16 = stringInt16_tHex.toInt16_t( 16 );
    // end::conversion_to_int16_t[]

    // tag::conversion_to_int32_t[]
    int32_t valueInt32_tBase10 = stringInt32_t.toInt32_t();
    int32_t valueInt32_tBase16 = stringInt32_tHex.toInt32_t( 16 );
    // end::conversion_to_int32_t[]

    // tag::conversion_to_int64_t[]
    int64_t valueInt64_tBase10 = stringInt64_t.toInt64_t();
    int64_t valueInt64_tBase16 = stringInt64_tHex.toInt64_t( 16 );
    // end::conversion_to_int64_t[]

    // tag::conversion_to_uint8_t[]
    uint8_t valueUint8_tBase10 = stringUint8_t.toUint8_t();
    uint8_t valueUint8_tBase16 = stringUint8_tHex.toUint8_t( 16 );
    // end::conversion_to_uint8_t[]

    // tag::conversion_to_uint16_t[]
    uint16_t valueUint16_tBase10 = stringUint16_t.toUint16_t();
    uint16_t valueUint16_tBase16 = stringUint16_tHex.toUint16_t( 16 );
    // end::conversion_to_uint16_t[]

    // tag::conversion_to_uint32_t[]
    uint32_t valueUint32_tBase10 = stringUint32_t.toUint32_t();
    uint32_t valueUint32_tBase16 = stringUint32_tHex.toUint32_t( 16 );
    // end::conversion_to_uint32_t[]

    // tag::conversion_to_uint64_t[]
    uint64_t valueUint64_tBase10 = stringUint64_t.toUint64_t();
    uint64_t valueUint64_tBase16 = stringUint64_tHex.toUint64_t( 16 );
    // end::conversion_to_uint64_t[]

    // tag::operation_append[]
    string.append( "Hello, world!" );
    string.append( 1234 );
    string.append( "0x" ).append( 0x5678, 16 );
    // end::operation_append[]
    string = "Hello, world!";

    // tag::operation_get_appended[]
    string.getAppended( "Hello, world!" );
    string.getAppended( 1234 );
    string.getAppended( "0x" ).append( 0x5678, 16 );
    // end::operation_get_appended[]
    string.clear();

    // tag::operation_insert[]
    string.insert( 0_uz, "Hello, world!");
    string.insert( 6_uz, 4 );
    string.insert( 7, 0x2, 16 );
    string.insert( string.end() - 1, "s and solar system" );
    string.insert( 6, ' ' );
    // end::operation_insert[]
    string = "Hello, world!";

    // tag::operation_get_inserted[]
    string.getInserted( 6_uz, 4 );
    string.getInserted( 7, 0x2, 16 );
    string.getInserted( string.end() - 1, "s and solar system" );
    string.getInserted( 6, ' ' );
    // end::operation_get_inserted[]
    string = "Hello, world!";

    // tag::operation_erase[]
    string.erase( 5 );
    // end::operation_erase[]

    string = "Hello, world!";
    // tag::operation_get_erased[]
    string.getErased( 5 );
    // end::operation_get_erased[]

    string = "Hello, world!";
    // tag::operation_erase_range[]
    string.erase( 5, 12 );
    // end::operation_erase_range[]

    string = "Hello, world!";
    // tag::operation_get_erased_range[]
    string.getErased( 5, 12 );
    // end::operation_get_erased_range[]

    // tag::operation_copy_to[]
    char destinationBuffer[128];
    string.copyTo( destinationBuffer, 128 );
    // end::operation_copy_to[]

    // tag::operation_copy_to_array[]
    uint8_t destination[128];
    string.copyTo( destination );
    // end::operation_copy_to_array[]

    string = "Hello, world!";
    // tag::operation_find[]
    string.find( ',' );
    string.find( "world");
    // end::operation_find[]

    // tag::operation_find_n[]
    string.find( ",", 1_uz );
    string.find( "world", std::strlen("world") );
    // end::operation_find_n[]

    // tag::operation_find_pos[]
    string.find( string.begin() + 3, ',' );
    string.find( string.begin() + 3, "world" );
    // end::operation_find_pos[]

    // tag::operation_find_pos_n[]
    string.find( ",", 1_uz );
    string.find( "world", std::strlen("world") );
    // end::operation_find_pos_n[]

    // tag::operation_rfind[]
    string.rfind( ',' );
    string.rfind( "world");
    // end::operation_rfind[]

    // tag::operation_rfind_n[]
    string.rfind( ",", 1_uz );
    string.rfind( "world", std::strlen("world") );
    // end::operation_rfind_n[]

    // tag::operation_rfind_pos[]
    string.rfind( string.rbegin() + 3, ',' );
    string.rfind( string.rbegin() + 3, "world" );
    // end::operation_rfind_pos[]

    // tag::operation_rfind_pos_n[]
    string.rfind( ",", 1_uz );
    string.rfind( "world", std::strlen("world") );
    // end::operation_rfind_pos_n[]

    // tag::operation_contains[]
    if( string.contains( "Hello" ) ) {
        /* .. */
    }
    // end::operation_contains[]

    // tag::operation_contains_n[]
    if( string.contains( "Hello", std::strlen("Hello") ) ) {
        /* .. */
    }
    // end::operation_contains_n[]

    // tag::operation_equals[]
    if( string.equals( "Hello, world!" ) ) {
        /* ... */
    }
    // end::operation_equals[]

    // tag::operation_equals_n[]
    if( string.equals( "Hello", std::strlen("Hello") ) ) {
        /* ... */
    }
    // end::operation_equals_n[]

    // tag::operation_strip[]
    string.strip();
    string.strip( '\n' );
    string.strip( " ,\t\n" );
    string.strip( EDF::String<4>("lo") );
    // end::operation_strip[]

    // tag::operation_strip_n[]
    string.strip( " \x1B", std::strlen("\x1B") );
    // end::operation_strip_n[]

    // tag::operation_get_stripped[]
    string.getStripped();
    string.getStripped( '\n' );
    string.getStripped( " ,\t\n" );
    string.getStripped( EDF::String<4>("lo") );
    // end::operation_get_stripped[]

    // tag::operation_get_stripped_n[]
    string.getStripped( " \x1B", std::strlen("\x1B") );
    // end::operation_get_stripped_n[]

    // tag::operation_trim[]
    string = "\t\x1B Hello, world! \r\n ";
    string.trim( '\t' ); // "\x1B Hello, world! \r\n "
    string.trim( " \r\n" ); // "\t\x1B Hello, world!"
    string.trim(); // "Hello, world!"
    // end::operation_trim[]

    // tag::operation_trim_n[]
    string = "\t\x1B Hello, world! \r\n ";
    string.trim( "\r \n\x1B", std::strlen("\r \n\x1B") ); // "\t\x1B Hello, world!"
    // end::operation_trim_n[]

    // tag::operation_get_trim[]
    string = "\t\x1B Hello, world! \r\n ";
    string.getTrimmed( '\t' ); // "\x1B Hello, world! \r\n "
    string.getTrimmed( "\r\n" ); // "\t\x1B Hello, world! \r\n "
    string.getTrimmed(); // "Hello, world!"
    // end::operation_get_trim[]

    // tag::operation_get_trim_n[]
    string = "\t\x1B Hello, world! \r\n ";
    string.getTrimmed( "\r \n\x1B", std::strlen("\r \n\x1B") ); // "\t\x1B Hello, world!"
    // end::operation_get_trim_n[]

    // tag::operation_trim_left[]
    string = "\t\x1B Hello, world! \r\n ";
    string.trimLeft( '\t' ); // "\x1B Hello, world! \r\n "
    string.trimLeft( "\r\n" ); // "\t\x1B Hello, world! \r\n "
    string.trimLeft(); // "Hello, world! \r\n "
    // end::operation_trim_left[]

    // tag::operation_trim_left_n[]
    string = "\t\x1B Hello, world! \r\n ";
    string.trimLeft( "\r \n\x1B", std::strlen("\r \n\x1B") ); // "\t\x1B Hello, world! \r\n "
    // end::operation_trim_left_n[]

    // tag::operation_get_trimmed_left[]
    string = "\t\x1B Hello, world! \r\n ";
    string.getTrimmedLeft( '\t' ); // "\x1B Hello, world! \r\n "
    string.getTrimmedLeft( "\r\n" ); // "\t\x1B Hello, world! \r\n "
    string.getTrimmedLeft(); // "Hello, world! \r\n "
    // end::operation_get_trimmed_left[]

    // tag::operation_get_trimmed_left_n[]
    string = "\t\x1B Hello, world! \r\n ";
    string.getTrimmedLeft( "\r \n\x1B", std::strlen("\r \n\x1B") ); // "\t\x1B Hello, world! \r\n "
    // end::operation_get_trimmed_left_n[]

    // tag::operation_trim_right[]
    string = "\t\x1B Hello, world! \r\n ";
    string.trimRight( '\t' ); // "\t\x1B Hello, world! \r\n "
    string.trimRight( "\r\n" ); // "\t\x1B Hello, world! \r\n "
    string.trimRight(); // "\t\x1B Hello, world!"
    // end::operation_trim_right[]

    // tag::operation_trim_right_n[]
    string = "\t\x1B Hello, world! \r\n ";
    string.trimRight( "\r \n\x1B", std::strlen("\r \n\x1B") ); // "\t\x1B Hello, world!"
    // end::operation_trim_right_n[]

    // tag::operation_get_trimmed_right[]
    string = "\t\x1B Hello, world! \r\n ";
    string.getTrimmedRight( '\t' ); // "\t\x1B Hello, world! \r\n "
    string.getTrimmedRight( "\r\n" ); // "\t\x1B Hello, world! \r\n "
    string.getTrimmedRight(); // "\t\x1B Hello, world!"
    // end::operation_get_trimmed_right[]

    // tag::operation_get_trimmed_right_n[]
    string = "\t\x1B Hello, world! \r\n ";
    string.getTrimmedRight( "\r \n\x1B", std::strlen("\r \n\x1B") ); // "\t\x1B Hello, world!"
    // end::operation_get_trimmed_right_n[]
    string = "Hello, world!";
    // tag::operation_reverse[]
    string.reverse(); // "!dlrow ,olleH"
    // end::operation_reverse[]

    // tag::operation_get_reversed[]
    string.getReversed(); // "!dlrow ,olleH"

    string = "Madam in Eden, Im Adam.";
    auto normalized = string.getToLower().strip( " ,." );
    bool isPalindrome = normalized.equals( normalized.getReversed() );
    // end::operation_get_reversed[]
    std::cout << "isPalindrome: " << isPalindrome << std::endl;

    string = "Hello, world!";
    // tag::operation_to_lower[]
    string.toLower(); // "hello, world!";
    // end::operation_to_lower[]
    // tag::operation_get_to_lower[]
    string.getToLower(); // "hello, world!";
    // end::operation_get_to_lower[]

    // tag::operation_to_upper[]
    string.toUpper(); // "HELLO, WORLD!";
    // end::operation_to_upper[]
    // tag::operation_get_to_upper[]
    string.getToUpper(); // "HELLO, WORLD!";
    // end::operation_get_to_upper[]

    string = "Hello, world!\r\nHow's it \r\ngoing?";
    // tag::operation_replace[]
    string.replace( 'e', 'a' );
    string.replace( "\r\n", '\n' );
    string.replace( "'s", std::strlen("'s"), 's' );

    string.replace( ',', "" );
    string.replace( "Hows", "How is" );
    string.replace( "How", std::strlen("How"), "Who" );

    string.replace( 't', "magining", std::strlen("magining") );
    string.replace( "imagining \n", "planning on ", std::strlen("planning on ") );
    string.replace( "going", std::strlen("going"), "saying goodbye", std::strlen("saying goodbye") );
    // end::operation_replace[]

    string = "Hello, world!\r\nHow's it \r\ngoing?";
    // tag::operation_get_replace[]
    string.getReplaced( 'e', 'a' );
    string.getReplaced( "\r\n", '\n' );
    string.getReplaced( "'s", std::strlen("'s"), 's' );

    string.getReplaced( ',', "" );
    string.getReplaced( "Hows", "How is" );
    string.getReplaced( "How", std::strlen("How"), "Who" );

    string.getReplaced( 't', "magining", std::strlen("magining") );
    string.getReplaced( "imagining \n", "planning on ", std::strlen("planning on ") );
    string.getReplaced( "going", std::strlen("going"), "saying goodbye", std::strlen("saying goodbye") );
    // end::operation_get_replace[]

    string = "Hello, world!";
    // tag::operation_substring[]
    string.subString( string.begin(), string.begin() + 5 );
    // end::operation_substring[]
    string = "Hello, world!";
    // tag::operation_get_substring[]
    string.getSubString( string.begin(), string.begin() + 5 );

    string.getSubString( string.find(", ") + std::strlen(", "), string.find( '!' ) );
    // end::operation_get_substring[]

    string = "Hello, world!";
    // tag::operation_plus_equals1[]
    string += " c string";
    string += pLiteralUint8_t;
    string += strLiteralChar;
    string += strLiteralUint8_t;
    string += ch;
    string += 'c';
    string += valueInt8_t; // assumes base 10, use append() for a different base
    string += valueInt16_t; // assumes base 10, use append() for a different base
    string += valueInt32_t; // assumes base 10, use append() for a different base
    string += valueInt64_t; // assumes base 10, use append() for a different base
    string += valueUint8_t; // assumes base 10, use append() for a different base
    string += valueUint16_t; // assumes base 10, use append() for a different base
    string += valueUint32_t; // assumes base 10, use append() for a different base
    // tag::operation_plus_equals1[]
    string.clear(); // for this example, string is running out of space, just clear it
    // end::operation_plus_equals2[]
    string += valueUint64_t; // assumes base 10, use append() for a different base
    string += differentSizedString;
    // end::operation_plus_equals2[]
    string = "Hello, world!";

    // tag::init_result[]
    EDF::String<128> result;
    // end::init_result[]

    // tag::operation_plus_rhs[]
    result = string + " c string";
    result = string + pLiteralUint8_t;
    result = string + strLiteralChar;
    result = string + strLiteralUint8_t;
    result = string + ch;
    result = string + 'c';
    result = string + valueInt8_t; // assumes base 10, use append() for a different base
    result = string + valueInt16_t; // assumes base 10, use append() for a different base
    result = string + valueInt32_t; // assumes base 10, use append() for a different base
    result = string + valueInt64_t; // assumes base 10, use append() for a different base
    result = string + valueUint8_t; // assumes base 10, use append() for a different base
    result = string + valueUint16_t; // assumes base 10, use append() for a different base
    result = string + valueUint32_t; // assumes base 10, use append() for a different base
    result = string + valueUint64_t; // assumes base 10, use append() for a different base
    result = string + differentSizedString;
    // end::operation_plus_rhs[]

    // tag::operation_plus_lhs[]
    result = " c string" + string;
    result = pLiteralUint8_t + string;
    result = strLiteralChar + string;
    result = strLiteralUint8_t + string;
    result = ch + string;
    result = 'c' + string;
    result = valueInt8_t + string; // assumes base 10, use append() for a different base
    result = valueInt16_t + string; // assumes base 10, use append() for a different base
    result = valueInt32_t + string; // assumes base 10, use append() for a different base
    result = valueInt64_t + string; // assumes base 10, use append() for a different base
    result = valueUint8_t + string; // assumes base 10, use append() for a different base
    result = valueUint16_t + string; // assumes base 10, use append() for a different base
    result = valueUint32_t + string; // assumes base 10, use append() for a different base
    result = valueUint64_t + string; // assumes base 10, use append() for a different base
    result = differentSizedString + string;
    // end::operation_plus_lhs[]

    std::cout << result.asCString() << std::endl;
}

int main() {
    EDF::String<128> test( 1234 );
    test += 567890;
    std::cout << "1:" << test.asCString() << '\n';
    test.insert( 4, " Inserted Value" );
    std::cout << (4 + (EDF::String<10>(" Okay") + test)).strip().asCString() << '\n';

    std::cout << "2:" << test.asCString() << '\n';
    test.insert( 0_uz, " \n Test \n" );
    std::cout << "3:" << test.asCString() << '\n';
    std::cout << "4:" << test.getStripped( "ea" ).asCString() << '\n';

    EDF::String<64> smallerTest = "  ! !Hello, world!  !   ";
    smallerTest.trim( " !" );
    std::cout << "5:>" << smallerTest.asCString() << "<" << '\n';

    std::cout << "6:" << smallerTest.contains("Hello") << '\n';

    std::cout << "7:" << smallerTest.getReversed().asCString() << '\n';

    std::cout << "8:" << smallerTest.equals( "Hello, world" ) << '\n';

    std::cout << "9:" << smallerTest.getToUpper().asCString() << '\n';

    std::cout << "10:" << smallerTest.getToLower().asCString() << '\n';

    std::cout << "11:"
              << smallerTest
                    .getAppended( " world something" )
                    .getReplaced( "world", "solar system!" )
                    .asCString()
              << '\n';

    auto comma = smallerTest.find( smallerTest.begin(), ',' );
    auto firstWord = smallerTest.find( comma + 2, ' ' );
    std::cout << "12:"
              << smallerTest.getSubString( comma + 2, firstWord ).asCString()
              << '\n';

    std::cout << "13:" << smallerTest.asCString() << '\n';

    EDF::String<32> stringNumber = 1'000'000;
    int counter = 0;
    for( EDF::String<32>::ReverseIterator it = stringNumber.rbegin(); it != stringNumber.rend(); ++it ) {
        if( ++counter == 3 ) {
            // it will point to the "right" of the element, similar to end() being +1 to the "right"
            stringNumber.insert( (it+1).base(), ',' );
            counter = 0;
        }
    }

    std::cout << "14:" << stringNumber.asCString() << '\n';

    examples();

    return 0;
}