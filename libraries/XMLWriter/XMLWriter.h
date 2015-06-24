#ifndef XML_WRITER_H
#define XML_WRITER_H
//
//    FILE: XMLWriter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
//    DATE: 2013-11-06
// PURPOSE: Simple XML writer library
//
// Released to the public domain
//

#include "Arduino.h"
// no pre 1.0 support!

#define XMLWRITER_VERSION "0.1.03"

// for comment()
#define MULTILINE   true

// for tagOpen(), tagEnd()
#define NEWLINE     true
#define NONEWLINE   false
#define NOINDENT    false    // for tagClose()

// for tagEnd()
#define SLASH       true
#define NOSLASH     false

// deepness of XML tree 5..10
// needed for stack of tagStack
#define XMLWRITER_MAXLEVEL 5

// reduce footprint by not using all
// possible datatypes
#define XMLWRITER_EXTENDED
#define XMLWRITER_ESCAPE_SUPPORT

class XMLWriter
{
public:
    XMLWriter(Print* stream);

    void reset();
    
    // standard XML header
    void header();
    
    // if multiline == true it does not indent to allow bigger text blocks
    // <!-- text -->
    void comment(char* text, bool multiLine=false);

    // <tag>
    void tagOpen(char* tag, bool newline=true);
    // <tag name="name">
    void tagOpen(char* tag, char* name, bool newline=true);
    // </tag>
    void tagClose(bool indent=true);

    // <tag
    void tagStart(char* tag);
    // field="value"
    void tagField(char* field, char* value);
    //  />
    void tagEnd(bool newline=true, bool addSlash=true);

    // <tag>value</tag>
    void writeNode(char* tag, char* value);

    // typically 0,2,4; default == 2;
    void setIndentSize(uint8_t size); 

#ifdef XMLWRITER_EXTENDED
    void tagField(char* field, uint8_t  value, uint8_t base=DEC);
    void tagField(char* field, uint16_t value, uint8_t base=DEC);
    void tagField(char* field, uint32_t value, uint8_t base=DEC);
    void tagField(char* field, int8_t   value, uint8_t base=DEC);
    void tagField(char* field, int16_t  value, uint8_t base=DEC);
    void tagField(char* field, int32_t  value, uint8_t base=DEC);
    void tagField(char *field, bool     value);
    void tagField(char* field, double   value, uint8_t decimals=2);

    void writeNode(char* tag, uint8_t   value, uint8_t base=DEC);
    void writeNode(char* tag, uint16_t  value, uint8_t base=DEC);
    void writeNode(char* tag, uint32_t  value, uint8_t base=DEC);
    void writeNode(char* tag, int8_t    value, uint8_t base=DEC);
    void writeNode(char* tag, int16_t   value, uint8_t base=DEC);
    void writeNode(char* tag, int32_t   value, uint8_t base=DEC);
    void writeNode(char* tag, bool      value);
    void writeNode(char* tag, double value, uint8_t decimals=2);
#endif


#ifdef XMLWRITER_ESCAPE_SUPPORT
    // expands the special xml chars
    void escape(char* str);
#endif

private:
    // outputstream
    Print* _stream;
    
    // for indentation
    void spaces();
    uint8_t _indent;
    uint8_t _indentStep;

    // stack - used to remember the current tagname to create 
    // automatic the right close tag.
    uint8_t _idx;
    char tagStack[XMLWRITER_MAXLEVEL][11];
};

#endif
// END OF FILE