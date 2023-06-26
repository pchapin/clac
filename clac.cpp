/*! \file    clac.cpp
 *  \brief   Clac main program.
 *  \author  Peter Chapin <chapinp@proton.me> and Peter Nikolaidis
 */

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <memory>

// ClacEntity library.
#include "BinaryEntity.hpp"
#include "FloatEntity.hpp"
#include "IntegerEntity.hpp"
#include "StringEntity.hpp"
#include "convert.hpp"
#include "support.hpp"

// ClacEngine library.
#include "actions.hpp"
#include "get.hpp"
#include "Global.hpp"
#include "words.hpp"

// Scr library.
#include "CommandWindow.hpp"
#include "debug.hpp"
#include "MessageWindow.hpp"
#include "scr.hpp"

#include "ClacCommandWindow.hpp"
#include "DirectoryWindow.hpp"
#include "StackWindow.hpp"

using namespace std;

namespace {

    //! Adjusts the format of __DATE__.
    /*!
     * This function puts a comma after the day of the month and purges leading zeros or spaces
     * from the day of the month.
     *
     * \param standard_date The date in the format given by the __DATE__ macros.
     * \return A pointer to a statically allocated buffer (of size 13) holding the cleaned up
     * date.
     */
    char *adjust_date(const char *standard_date)
    {
        static char  buffer[13];
            char *buffer_pointer;

        // Make a working copy of the date as from the ANSI __DATE__ macro.
        strcpy( buffer, standard_date );

        // Open up space for the comma.
        for( buffer_pointer  = strchr( buffer, '\0' );
            buffer_pointer >= &buffer[6];
            buffer_pointer-- ) {
            *(buffer_pointer+1) = *buffer_pointer;
        }

        // Put the comma in.
        buffer[6] = ',';

        // If this is a date from 1 to 9, close up the extra space.
        if( buffer[4] == '0' || buffer[4] == ' ' ) {
            for( buffer_pointer = &buffer[4]; *buffer_pointer; buffer_pointer++ ) {
                *buffer_pointer = *( buffer_pointer + 1 );
            }
        }

        // Return are result.
        return buffer;
    }


    // These message descriptors define the appearance of the various kinds of message windows.
    scr::MessageWindowDescriptor message_descriptors[] = {
        // For scr::MESSAGE_WINDOW_MESSAGE
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_PROMPT
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_WARNING
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_ERROR
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY },

        // For scr::MESSAGE_WINDOW_INT_ERROR
        { scr::WHITE, scr::SINGLE_LINE, scr::WHITE, NULL, scr::WHITE, scr::MESSAGE_WINDOW_ANY }
    };


    //! Class to perform setup and teardown operations.
    /*!
     * Only one instance of this class should be created. The constructor initializes the
     * underlying screen handling library, and the destructor shuts that library down. The point
     * of this class is to treat the screen as a resource that is managed by the RAI idiom. If
     * an exception is thrown that propagates to main, the destructor will still be called and
     * the screen will be shut down properly.
     */
    class SetUp {
    public:
        SetUp( bool use_debugger );
       ~SetUp( );
    private:
        bool debugging_on;
    };


    SetUp::SetUp( bool use_debugger ) : debugging_on( false )
    {
        // TODO: Reload the calculator state (if there's a saved one to be found).

        scr::initialize( );
        scr::refresh_on_key( true );
        scr::MessageWindow::set_descriptors( message_descriptors );

        // One problem with initializing debugging here is that if an exception is thrown
        // immediately (i.e., the user issues the "quit" command), the destructor of this class
        // doesn't run and the screen is left in a messy state. I don't think this will be an
        // issue in practice. If the debugging user moves to a breakpoint, this constructor will
        // have fully completed and the destructor will do its job.
        // TODO: Fix the problem described above.
        if( use_debugger ) {
            scr::initialize_debugging( DBG_TOP );
            debugging_on = true;
        }
    }


    SetUp::~SetUp( )
    {
        if( debugging_on ) {
            scr::terminate_debugging( );
        }
        scr::terminate( );

        // TODO: Save the calculator state.
        cout << "CLAC Version 0.10a  Compiled: " << adjust_date( __DATE__ ) << '\n'
            << "(C) Copyright 2023 by Peter Chapin and Peter Nikolaidis" << endl;
    }
}

//=====================================
//           Message Handling
//=====================================

//! Displays an error message.
/*!
 * This function is the master error message handler for all components of Clac. It is actually
 * declared in a low level header (support.hpp) in the Clac entity library. Any code that uses
 * Clac entities must provide an implementation of this function that is application specific.
 */
void error_message( const char *message, ... )
{
    va_list ap;
    char message_buffer[128 + 1];

    va_start( ap, message );    
    vsnprintf( message_buffer, 128 + 1, message, ap );
    scr::MessageWindow( message_buffer, scr::MESSAGE_WINDOW_ERROR );
}

/*!
 * This function is used to print information messages to the UI. Unlike the error message
 * function, it assumes the caller constructs the entire message. This choice was made on the
 * assumption that informational messages wouldn't normally need to print data values. That
 * assumption may need to be revisted at some point.
 *
 * As with `error_message`, any code that makes use of Clac entities must provide an
 * implementation of this function that is application specific.
 */
void info_message( const string &message )
{
    scr::MessageWindow( message.c_str( ), scr::MESSAGE_WINDOW_MESSAGE );
}


//=================================================
//           Generic Operation Functions
//=================================================

namespace {

    void do_unary( ClacStack &the_stack, Entity *(Entity::*unary_operation)( ) const )
    {
        // Get a pointer to the object on stack level zero.
        Entity *thing = the_stack.get( 0 );

        // If it didn't work, we have an error!
        if( thing == nullptr ) underflow( );
        else {
            // Do the unary operation. If it works, we will get a pointer to a new object.
            Entity *new_thing = ( thing->*unary_operation )( );
            the_stack.put( new_thing );
        }
    }

    void do_binary( ClacStack &the_stack, Entity *(Entity::*binary_operation)( const Entity * ) const )
    {
        Entity *left  = the_stack.get( 1 );
        Entity *right = the_stack.get( 0 );

        if( left == nullptr || right == nullptr ) underflow( );
        else {
            Entity *(Entity::*conversion)( ) const =
                convert_table[left->my_type( )][right->my_type( )];

            if( conversion == nullptr ) {
                error_message( "Required implicit conversion not implemented!" );
                return;
            }

            unique_ptr<Entity> new_left( (left->*conversion)( ) );
            unique_ptr<Entity> new_right( (right->*conversion)( ) );

            Entity *T1 = new_left.get( );
            Entity *T2 = new_right.get( );

            Entity *new_thing = (T1->*binary_operation)( T2 );

            // TODO: Shouldn't there be a method in the stack class that deletes the top element?
            Entity *old_level_zero = the_stack.pop( );
            Entity *old_level_one  = the_stack.pop( );
            delete old_level_zero;
            delete old_level_one;

            the_stack.push( new_thing );
        }
    }

    struct BuiltinBinary {
        const char  *word;
        Entity *(Entity::*binary_operation)( const Entity * ) const;
    };

    struct BuiltinUnary {
        const char  *word;
        Entity *(Entity::*unary_operation)( ) const;
    };

    struct BuiltinAction {
        const char  *word;
        void (*operation)( ClacStack & );
    };

    BuiltinBinary binary_words[] = {
        { "+",      &Entity::plus              },
        { "-",      &Entity::minus             },
        { "*",      &Entity::multiply          },
        { "/",      &Entity::divide            },
        { "==",     &Entity::is_equal          },
        { "!=",     &Entity::is_notequal       },
        { ">",      &Entity::is_greater        },
        { ">=",     &Entity::is_greaterorequal },
        { "<",      &Entity::is_less           },
        { "<=",     &Entity::is_lessorequal    },
        { "mod",    &Entity::modulo            },
        { "^",      &Entity::power             },
        { nullptr,   nullptr                   }
    };

    BuiltinUnary unary_words[] = {
        { "abs",    &Entity::abs               },
        { "acos",   &Entity::acos              },
        { "alog",   &Entity::exp10             },
        { "asin",   &Entity::asin              },
        { "atan",   &Entity::atan              },
        { "conj",   &Entity::complex_conjugate },
        { "cos",    &Entity::cos               },
        { "exp",    &Entity::exp               },
        { "frac",   &Entity::fractional_part   },
        { "im",     &Entity::imaginary_part    },
        { "inv",    &Entity::inv               },
        { "ln",     &Entity::ln                },
        { "log",    &Entity::log               },
        { "neg",    &Entity::neg               },
        { "re",     &Entity::real_part         },
        { "sgn",    &Entity::sign              },
        { "sin",    &Entity::sin               },
        { "sq",     &Entity::sq                },
        { "sqrt",   &Entity::sqrt              },
        { "tan",    &Entity::tan               },
        
        { ">BIN",   &Entity::to_binary         },
        { ">CPX",   &Entity::to_complex        },
        { ">FLT",   &Entity::to_float          },
        { ">INT",   &Entity::to_integer        },
        { ">LST",   &Entity::to_list           },
        { ">MAT",   &Entity::to_matrix         },
        { ">RAT",   &Entity::to_rational       },
        { ">STR",   &Entity::to_string         },
        { nullptr,   nullptr                   }
    };

    BuiltinAction action_words[] = {
        // Normal actions.
        { "bin",    do_bin      },
        { "clear",  do_clear    },
        { "dec",    do_dec      },
        { "deg",    do_deg      },
        { "drop",   do_drop     },
        { "dropn",  do_dropn    },
        { "dup",    do_dup      },
        { "dupn",   do_dupn     },
        { "eng",    do_eng      },
        { "eval",   do_eval     },
        { "fix",    do_fix      },
        { "grad",   do_grad     },
        { "hex",    do_hex      },
        { "info",   do_info     },
        { "oct",    do_oct      },
        { "polar",  do_polar    },
        { "purge",  do_purge    },
        { "rad",    do_rad      },
        { "read",   do_read     },
        { "rec",    do_rec      },
        { "roll" ,  do_roll_up  },
        { "rolld",  do_roll_down},
        { "rot",    do_rot      },
        { "run",    do_run      },
        { "sci",    do_sci      },
        { "sto",    do_store    },
        { "stws",   do_stws     },
        { "swap",   do_swap     },
        //{ "sys",    do_sys      },
        { "write",  do_write    },

        // Unary actions.
        { "sl",     do_shift_left   },
        { "sr",     do_shift_right  },
        //{ "asr",    do_ashift_right },

        // Off. The other versions of "off" just produce a message telling the user to use the
        // 'quit' command.
        //
        { "exit",   do_off },
        { "off",    do_off },
        { "quit",   do_off },
        
        { nullptr,  nullptr }
    };

    bool process_binary( ClacStack &the_stack, const string &word_buffer )
    {
        // Scan the list of builtin binary words.
        BuiltinBinary *bin_op = binary_words;
        while( bin_op->word != nullptr ) {
            if( bin_op->word == word_buffer ) break;
            bin_op++;
        }

        // If we found it, do the operation.
        if( bin_op->word != nullptr ) {
            do_binary( the_stack, bin_op->binary_operation );
            return true;
        }
        return false;
    }

    
    bool process_unary( ClacStack &the_stack, const string &word_buffer )
    {
        // Scan the list of built in unary words.
        BuiltinUnary *unary_op = unary_words;
        while( unary_op->word != nullptr ) {
            if( unary_op->word == word_buffer ) break;
            unary_op++;
        }

        // If we found it, do the operation.
        if( unary_op->word != nullptr ) {
            do_unary( the_stack, unary_op->unary_operation );
            return true;
        }
        return false;
    }

    
    bool process_action( ClacStack &the_stack, const string &word_buffer )
    {
        // Scan the list of builtin action words.
        BuiltinAction *action_op = action_words;
        while( action_op->word != nullptr ) {
            if( action_op->word == word_buffer ) break;
            action_op++;
        }

        // If we found it, do the operation.
        if( action_op->word != nullptr ) {
            action_op->operation( the_stack );
            return true;
        }
        return false;
    }

}


//! Process the words on the master stream, executing them one at a time.
/*!
 * This function continues working until the master stream is completely empty. Note that some
 * words cause new WordStream objects to be pushed onto the master stream. This function
 * continues until all of those streams are exhausted as well.
 *
 * \return true if the program should continue; false if the "quit" word was encountered.
 */
bool process_words( )
{
    while( 1 ) {
        try {
            string new_word( Global::word_source( ).next_word( ) );

            // The master stream is exhausted.
            if( new_word.length( ) == 0 ) return true;

            // See if we got the null word. [Can this ever happen?]
            if( new_word[0] == '\0' ) {
                do_dup( Global::the_stack( ) );
                continue;
            }

            // Should we quit?
            if( new_word == "quit" ) return false;

            // See if it is a built in word.
            if( process_binary( Global::the_stack( ), new_word) ) continue;
            if( process_unary ( Global::the_stack( ), new_word) ) continue;
            if( process_action( Global::the_stack( ), new_word) ) continue;

            StringStream stream( new_word );
            Entity *new_object = get_entity( stream );
            if( new_object != nullptr )
                Global::the_stack( ).push( new_object );
        }
        catch( const char *the_message ) {
            error_message( "Exception: %s", the_message );
        }
        catch( const exception &e ) {
            error_message( "Exception: %s", e.what( ) );
        }
    }
}

//==================================
//           Main Program
//==================================

int Main( int argc, char **argv )
{
    // The value of 'use_debugger' selects if the runtime debugging environment is active.
    bool use_debugger = false;

    // Command line analysis. Note that the windowing system is not yet running.
    // TODO: Improve and generalize the handling of the command line.
    for( int i = 1; i < argc; ++i ) {
        if( strcmp( argv[i], "-d" ) == 0 ) use_debugger = true;
    }

    // Initialize the program and start the windowing system.
    SetUp the_program( use_debugger );
    const int screen_rows = scr::number_of_rows( );
    const int screen_cols = scr::number_of_columns( );
    const int half_width  = screen_cols / 2;

    // Create the window manager.
    scr::Manager window_manager;

    // Create the windows in their initial positions and register them with the window manager.
    StackWindow stack_view(
        window_manager,  2,  2, half_width - 2, screen_rows - 5 );

    DirectoryWindow directory_view(
        window_manager,  2, half_width + 2, half_width - 2, screen_rows - 5 );

    ClacCommandWindow command_view(
        &window_manager, screen_rows - 1,  2, screen_cols - 2,  1 );

    // Initialize windows (the directory window is currently not implemented).
    stack_view.associate( &Global::the_stack( ) );
    command_view.set_prompt( "=> " );

    window_manager.input_loop( );

    // Clac always "succeeds" unless there is an unhandled exception (see below).
    return EXIT_SUCCESS;
}

//===================================
//           The real main
//===================================

int main( int argc, char **argv )
{
    // Set the default exit status in case an unhandled exception propagates through main.
    int return_value = EXIT_FAILURE;

    try {
        return_value = Main( argc, argv );
    }
    catch (...) {
        cerr << "\nPanic! Unhandled exception propagated through main()" << endl;
    }
    return return_value;
}
