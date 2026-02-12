/*! \file    RecordFile.cpp
 *  \brief   Implementation of a "record file" class.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 *
 * This file contains the implementation of class RecordFile. Objects from this class support
 * easy reading of text files which are organized as several lines where each line contains a
 * record consisting of several fields. The record files supported can have a variable number of
 * fields per line and can contain comments.
 */

#include "RecordFile.hpp"
#include <cstring>

using namespace std;

namespace {

    bool split_string(char* buffer,               // String to be split.
                      char* delimiters,           // String of delimiter characters.
                      char* strings[],            // Array to be filled with pntrs to substrings.
                      int max_nmbr_of_strings,    // Maximum number of substrings allowed.
                      int* actual_nmbr_of_strings // Actual number of substrings found.
    )
    {
        char* buffer_pointer;    // Temporary pointer into buffer.
        bool in_string = false;  // =false when *buf_ptr not pointing at str.
        bool return_code = true; // Returns false if too many substrings.

        // Initialize result and check for out of bounds input.
        *actual_nmbr_of_strings = 0;
        if (max_nmbr_of_strings < 0)
            return_code = false;
        else {

            // Sweep down string until null byte reached.
            buffer_pointer = buffer;
            while (*buffer_pointer != '\0') {

                // Try to process the current character only if no error so far.
                if (return_code == true) {

                    // If delimiter found while scanning an argument...
                    if ((strchr(delimiters, *buffer_pointer) != nullptr) && in_string) {
                        *buffer_pointer = '\0';
                        in_string = false;
                    }

                    // If non-delimiter found while scanning "white" space...
                    else if ((strchr(delimiters, *buffer_pointer) == nullptr) && !in_string) {

                        // Install only if space. If no space left set error flag.
                        if (*actual_nmbr_of_strings < max_nmbr_of_strings) {
                            strings[*actual_nmbr_of_strings] = buffer_pointer;
                            (*actual_nmbr_of_strings)++;
                            in_string = true;
                        }
                        else
                            return_code = false;
                    }
                }
                buffer_pointer++;
            }
        }

        return return_code;
    }

} // namespace

namespace clac::ui {
    /*----------------------------------------------------------------------------
    The constructor opens the file and allocates memory for a working buffer. The search method
    specified tells the object where the record file might be found. Currently, only DEFAULT is
    supported; record files must be in the default directory.

    The comment character is the character used to mark the beginning of an end-of-line style
    comment in the record file. All text after the first occurrence of this character is ignored. It
    can be '\0' if there are to be no comments in the record file.
    ----------------------------------------------------------------------------*/

    RecordFile::RecordFile(char* file_name,        // File name. Can contain paths, etc.
                           int /* search_method*/, // Where to find file. Must be DEFAULT (for now).
                           int length,             // Maximum length of line in record file.
                           char comment,           // Character which starts end-of-line comments.
                           char* delimit // String of characters which serve to delimit fields.
    )
    {
        // Initialize important members.
        buffer = nullptr;
        nmbr_of_parts = 0;

        // Open the file and allocate space.
        the_file.open(file_name);
        if (!the_file) {
            is_ok = false;
        }
        else if ((buffer = new char[length + 2]) == nullptr) {
            is_ok = false;
        }
        else {
            // Save desired specs.
            delimiters = delimit;
            comment_char = comment;
            line_length = length;
            is_ok = true;
        }
    }

    /*----------------------------------------------------------------------------
    The destructor closes the file and frees the buffer.
    ----------------------------------------------------------------------------*/

    RecordFile::~RecordFile()
    {
        delete buffer;
    }

    /*----------------------------------------------------------------------------
    The following function returns an array of character pointers. Each pointer in the array points
    to a field from the next line of the record file. To determine the number of fields, see the next
    function. Comments in the record file and trailing white space (regardless of the delimiter
    characters) are already stripped. The function returns nullptr if there is nothing else in the
    file.
    ----------------------------------------------------------------------------*/

    char** RecordFile::get_line()
    {
        if (!is_ok)
            return nullptr;

        char** return_value = nullptr;
        char* end_pntr;

        // Try to read a line from the file.
        if (the_file.getline(buffer, line_length + 1)) {

            // Kill comments.
            if ((end_pntr = strchr(buffer, comment_char)) != nullptr)
                *end_pntr = '\0';

            // Remove the trailing white space.
            for (end_pntr = buffer; *end_pntr; end_pntr++) /* Null */
                ;
            for (--end_pntr; end_pntr >= buffer && (*end_pntr == ' ' || *end_pntr == '\t');
                 --end_pntr) /* Null */
                     ;
            *++end_pntr = '\0';

            // Split the string into fields.
            too_long = split_string(buffer, delimiters, parts, 16, &nmbr_of_parts);
            return_value = parts;
        }

        // Return pointer to fields or nullptr.
        return return_value;
    }

    /*----------------------------------------------------------------------------
    The following function returns the number of fields in the last line read from the file.
    ----------------------------------------------------------------------------*/

    int RecordFile::get_length()
    {
        if (!is_ok)
            return 0;
        return nmbr_of_parts;
    }
}
