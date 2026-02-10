/*! \file    RecordFile.cpp
 *  \brief   Implementation of a "record file" class.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#ifndef RECORDFILE_HPP
#define RECORDFILE_HPP

#include <fstream>

class RecordFile {

  public:
    RecordFile( // Opens file and allocates space for buffer.
        char* file_name, int search_method, int length, char comment, char* delimit);
    ~RecordFile(); // Closes file and frees buffer.

    char** get_line(); // Reads a line and breaks it into fields.
    int get_length();  // Returns the number of fields.
    bool is_ok;        // =true if constructor works.
    bool too_long;     // =false if too many fields in line.

    enum { DEFAULT }; // Search methods.

  private:
    std::ifstream the_file; // Refers to actual file.
    char comment_char;      // Defines comment character in file.
    int line_length;        // Longest allowed line length in file.
    char* buffer;           // Points at the buffer to hold each raw line.
    char* delimiters;       // String of delimiters for fields in the file.
    char* parts[16];        // Points at each field (note fixed size).
    int nmbr_of_parts;      // Number of fields.
};

#endif
