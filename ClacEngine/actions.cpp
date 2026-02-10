/*! \file    actions.cpp
 *  \brief   This file contains...
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "BinaryEntity.hpp"
#include "ComplexEntity.hpp"
#include "DisplayState.hpp"
#include "Entity.hpp"
#include "FloatEntity.hpp"
#include "IntegerEntity.hpp"
#include "ListEntity.hpp"
#include "MatrixEntity.hpp"
#include "RationalEntity.hpp"
#include "StringEntity.hpp"
#include <spicacpp/VeryLong.hpp>

#include "Global.hpp"
#include "WordStream.hpp"
#include "actions.hpp"
#include "support.hpp"

using namespace std;
using namespace spica; // TODO: Remove this using directive.

namespace {

    /*!
     * Adjusts the format of __DATE__. Puts a comma after the day of the month and purge leading
     * zeros or spaces from the day of the month.
     *
     * \param ANSI_Date The date in the format given by the __DATE__ macros. \return A pointer
     * to a statically allocated buffer (of size 13) holding the cleaned up date.
     */
    char* AdjDate(const char* ANSI_Date)
    {
        static char buffer[13];
        char* buffer_pointer;

        // Make a working copy of the date as from the ANSI __DATE__ macro.
        strcpy(buffer, ANSI_Date);

        // Open up space for the comma.
        for (buffer_pointer = strchr(buffer, '\0'); buffer_pointer >= &buffer[6];
             buffer_pointer--) {
            *(buffer_pointer + 1) = *buffer_pointer;
        }

        // Put the comma in.
        buffer[6] = ',';

        // If this is a date from 1 to 9, close up the extra space.
        if (buffer[4] == '0' || buffer[4] == ' ') {
            for (buffer_pointer = &buffer[4]; *buffer_pointer; buffer_pointer++) {
                *buffer_pointer = *(buffer_pointer + 1);
            }
        }

        // Return are result.
        return buffer;
    }

    VeryLong pop_int(ClacStack& the_stack)
    {
        VeryLong return_value;

        Entity* temp = the_stack.pop();
        if (temp == nullptr)
            error_message("Too few arguments");
        else {
            IntegerEntity* integer_temp = static_cast<IntegerEntity*>(temp->to_integer());
            if (integer_temp == nullptr) {
                error_message("Integer argument expected");
                the_stack.push(temp);
            }
            else {
                return_value = integer_temp->get_value();
                delete integer_temp;
            }
        }
        return return_value;
    }

} // namespace

void do_bin(ClacStack&)
{
    DisplayState::set_base(DisplayState::BINARY);
}

void do_clear(ClacStack& the_stack)
{
    the_stack.clear();
}

void do_dec(ClacStack&)
{
    DisplayState::set_base(DisplayState::DECIMAL);
}

void do_deg(ClacStack&)
{
    DisplayState::set_angle_mode(DisplayState::DEG);
}

void do_drop(ClacStack& the_stack)
{
    the_stack.drop();
}

void do_dropn(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);

    if (count == 0)
        return;
    for (VeryLong i = 0; i < count; ++i)
        the_stack.drop();
}

void do_dup(ClacStack& the_stack)
{
    Entity* new_copy = the_stack.get(0);
    if (new_copy != nullptr) {
        new_copy = new_copy->duplicate();

        if (new_copy != nullptr)
            the_stack.push(new_copy);
    }
}

void do_dupn(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);

    if (count == 0)
        return;
    for (VeryLong i = 0; i < count; ++i) {
        Entity* new_copy = the_stack.get(count - 1);
        if (new_copy != nullptr) {
            new_copy = new_copy->duplicate();

            if (new_copy != nullptr)
                the_stack.push(new_copy);
        }
    }
}

void do_eng(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);

    if (count == 0)
        return;
    DisplayState::set_decimal_count(count.to_long());
    DisplayState::set_display_mode(DisplayState::ENGINEERING);
}

void do_eval(ClacStack& the_stack)
{
    Entity* temp = the_stack.pop();

    if (temp == nullptr) {
        error_message("Too few arguments");
        return;
    }
    StringEntity* file_name;
    if ((file_name = dynamic_cast<StringEntity*>(temp)) == nullptr) {
        error_message("String expected");
        the_stack.push(temp);
        return;
    }

    FileStream* new_words = new FileStream(file_name->get_value().c_str());
    if (new_words != nullptr) {
        Global::word_source().push(new_words);
    }
}

void do_fix(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);
    DisplayState::set_decimal_count(count.to_long());
    DisplayState::set_display_mode(DisplayState::FIXED);
}

void do_grad(ClacStack&)
{
    DisplayState::set_angle_mode(DisplayState::GRAD);
}

void do_hex(ClacStack&)
{
    DisplayState::set_base(DisplayState::HEX);
}

void do_info(ClacStack&)
{
    info_message(string("CLAC Version 0.00a  Compiled: ") + AdjDate(__DATE__) + '\n' +
                 "(C) Copyright 2023 by Peter Chapin and Peter Nikolaidis");
}

void do_oct(ClacStack&)
{
    DisplayState::set_base(DisplayState::OCTAL);
}

void do_polar(ClacStack&)
{
    DisplayState::set_complex_mode(DisplayState::POLAR);
}

void do_purge(ClacStack& the_stack)
{
    Entity* temp = the_stack.pop();

    if (temp == nullptr) {
        error_message("Too few arguments");
        return;
    }
    StringEntity* variable_name;
    if ((variable_name = dynamic_cast<StringEntity*>(temp)) == nullptr) {
        error_message("String expected");
        the_stack.push(temp);
        return;
    }
    // Gets the root Directory_Entity.
    // global::get_root( ).delete( variable_name->get_value( ).c_str( ) );
    delete variable_name;
}

void do_rad(ClacStack&)
{
    DisplayState::set_angle_mode(DisplayState::RAD);
}

void do_rec(ClacStack&)
{
    DisplayState::set_complex_mode(DisplayState::RECTANGULAR);
}

static unsigned long read_header(ifstream& in_file)
{
    // TODO: Fix this to use IOStreams properly.
#ifdef NEVER
    unsigned long lulv; // lulv = local unsigned long variable

    if (fread(&lulv, sizeof(lulv), 1, in_file) != 1)
        return static_cast<unsigned long>(-1);
    else
        return lulv;
#endif
    return 0;
}

static bool read_signature(ifstream& in_file)
{
    // TODO: Fix this to use IOStreams properly.
#ifdef NEVER
    char array[10 + 1];
    if (fscanf(in_file, "%10c", array) == EOF)
        return false;
    array[10] = '\0';
    if (strcmp(array, "CLAC FILE\x1A") != 0)
        return false;
    return true;
#endif
    return false;
}

void do_read(ClacStack& the_stack)
{
    Entity* temp = the_stack.pop();
    ifstream in_file;

    if (temp == nullptr) {
        error_message("Too few arguments");
        return;
    }
    StringEntity* file_name;
    if ((file_name = dynamic_cast<StringEntity*>(temp)) == nullptr) {
        error_message("String expected");
        the_stack.push(temp);
        return;
    }
    in_file.open(file_name->get_value().c_str());
    if (!in_file) {
        error_message("Cannot open %s for reading", file_name->get_value().c_str());
        delete file_name;
        return;
    }
    if ((read_signature(in_file) == false) ||
        (read_header(in_file) == static_cast<unsigned long>(-1))) {
        error_message("Bad file format");
        delete file_name;
        return;
    }
    char type = -1;
    in_file.read(&type, 1);

    Entity* new_object = nullptr;
    switch (type) {
    case BINARY:
        new_object = new BinaryEntity;
        break;
    case COMPLEX:
        new_object = new ComplexEntity(std::complex<double>(0.0));
        break;
    case FLOAT:
        new_object = new FloatEntity(0.0);
        break;
    case INTEGER:
        new_object = new IntegerEntity(0UL);
        break;
    case LIST:
        new_object = new ListEntity;
        break;
    case MATRIX:
        new_object = new MatrixEntity;
        break;
    case RATIONAL:
        new_object = new RationalEntity(Rational<VeryLong>());
        break;
    case STRING:
        new_object = new StringEntity;
        break;
    default:
        error_message("Unknown object type in file");
        break;
    }
    if (new_object == nullptr) {
        delete file_name;
        in_file.close();
        return;
    }
    // TODO: This is completely broken. The semantics of read must have changed at some point.
    // if( new_object->read( in_file ) == false ) {
    //     error_message( "Unable to read object" );
    //     delete new_object;
    // }
    delete file_name;
    in_file.close();
    the_stack.push(new_object);
    return;
}

void do_roll_up(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);
    the_stack.roll_up(count);
}

void do_roll_down(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);
    the_stack.roll_down(count);
}

void do_rot(ClacStack& the_stack)
{
    the_stack.rotate();
}

void do_run(ClacStack& the_stack)
{
    Entity* temp = the_stack.pop();

    if (temp == nullptr) {
        error_message("Too few arguments");
        return;
    }
    StringEntity* file_name;
    if ((file_name = dynamic_cast<StringEntity*>(temp)) == nullptr) {
        error_message("String expected");
        the_stack.push(temp);
        return;
    }

#ifdef NEVER
    FWordStream* new_words = new FWordStream((char*)*file_name);
    if (new_words != nullptr) {
        global::word_source().push(new_words);
    }
#endif
}

void do_sci(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);
    DisplayState::set_decimal_count(count.to_long());
    DisplayState::set_display_mode(DisplayState::SCIENTIFIC);
}

void do_store(ClacStack& the_stack)
{
    Entity* temp = the_stack.pop();

    if (temp == nullptr) {
        error_message("Too few arguments");
        return;
    }
    StringEntity* variable_name;
    if ((variable_name = dynamic_cast<StringEntity*>(temp)) == nullptr) {
        error_message("String expected");
        the_stack.push(temp);
        return;
    }
    Entity* object = the_stack.pop();
    if (object == nullptr) {
        error_message("Too few arguments");
        delete variable_name;
        return;
    }
#ifdef NEVER
    if (!global::get_root().insert(*variable_name, object)) {
        error_message("Unable to save object in current directory");
        the_stack.push(object);
    }
#endif
    delete variable_name;
    return;
}

void do_stws(ClacStack& the_stack)
{
    VeryLong count = pop_int(the_stack);

    if (count < 1) {
        error_message("Word size must be at least one bit");
    }
    else if (count > 32) {
        error_message("Word size must be no more than 32 bits");
    }
    else {
        Global::set_bit_count(count);
    }
}

void do_swap(ClacStack& the_stack)
{
    the_stack.swap();
}

#ifdef NEVER
// Probably this function should be in the UI component.
void do_sys(ClacStack& the_stack)
{
    Entity* command = the_stack.get(0);
    if (command == nullptr) {
        underflow();
    }
    else if (command->my_type() != STRING) {
        error_message("System command requires string argument");
    }
    else {
        StringEntity* command_string = (StringEntity*)command;

        // Make sure everything is hidden.
        //         global::stack_view( ).hide( );
        //         global::flag_view( ).hide( );
        //         global::dir_view( ).hide( );
        ScrClear(1, 1, 80, 25, SCR_WHITE);
        ScrSetCursorPos(1, 1);

        // Do the command.
        system(command_string->get_value().c_str());
        cout << '\n' << '\n' << "***** Strike any key to return to CLAC *****";
        ScrKey();

        // Restore screen.
        //         global::stack_view ().show( );
        //         global::flag_view( ).show( );
        //         global::dir_view( ).show( );

        // Get rid of the dos command.
        do_drop(the_stack);
    }
}
#endif

static void write_signature(ofstream& Out_File)
{
    // TODO: Change this to use IOStreams properly.
#ifdef NEVER
    fprintf(out_file, "CLAC FILE\x1A");
#endif
}

static void write_header(ofstream& out_file, Entity* object)
{
    // TODO: Change this to use IOStreams properly.
#ifdef NEVER
    unsigned long length = object->file_size();
    fwrite(&length, sizeof(length), 1, out_file);
#endif
}

void do_write(ClacStack& the_stack)
{
    Entity* temp = the_stack.pop();
    ofstream out_file;

    if (temp == nullptr) {
        error_message("Too few arguments");
        return;
    }
    StringEntity* file_name;
    if ((file_name = dynamic_cast<StringEntity*>(temp)) == nullptr) {
        error_message("String expected");
        the_stack.push(temp);
        return;
    }
    Entity* object = the_stack.get(0);
    if (object == nullptr) {
        error_message("Too few arguments");
        delete file_name;
        return;
    }
    out_file.open(file_name->get_value().c_str());
    if (!out_file) {
        error_message("Cannot open %s for output", file_name->get_value().c_str());
        delete file_name;
        return;
    }
    write_signature(out_file);
    write_header(out_file, object);
    object->write(out_file);
    if (!out_file) {
        error_message("Error occurred during object write");
        out_file.close();
        remove(file_name->get_value().c_str());
        delete file_name;
        return;
    }
    out_file.close();
    delete file_name;
    return;
}

void do_shift_left(ClacStack&)
{
    return;
}

void do_shift_right(ClacStack&)
{
    return;
}

void do_ashift_right(ClacStack&)
{
    return;
}

void do_off(ClacStack&)
{
    error_message("Use 'quit' to terminate Clac");
}
