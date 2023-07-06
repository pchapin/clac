/*! \file    ClacStack.cpp
 *  \brief   This file contains...
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "ClacStack.hpp"
#include "support.hpp"

using namespace std;

ClacStack::ClacStack( )
{
    for( size_t i = 0; i < STACK_SIZE; i++ ) {
        data[i] = nullptr;
    }
}


ClacStack::~ClacStack( )
{
    for( size_t i = 0; i < STACK_SIZE; i++ ) {
        delete data[i];
    }
}


bool ClacStack::push( Entity *item )
{
    delete data[STACK_SIZE-1];
    for( size_t i = STACK_SIZE-1; i > 0; i-- ) {
        data[i] = data[i-1];
    }
    data[0] = item;
    return true;
}


Entity *ClacStack::pop( )
{
    Entity *return_value = data[0];

    for( size_t i = 0; i < STACK_SIZE-1; i++ ) {
        data[i] = data[i+1];
    }
    data[STACK_SIZE-1] = nullptr;
    return return_value;
}


Entity *ClacStack::get( const VeryLong &index )
{
    Entity *return_value = nullptr;

    if( index < STACK_SIZE ) {
        return_value = data[index.to_long( )];
    }
    return return_value;
}


void ClacStack::put( Entity *new_object )
{
    delete data[0];
    data[0] = new_object;
}


void ClacStack::clear( )      // Drop everything from the stack.
{
    size_t i;
    for( i = 0; i <= STACK_SIZE && data[i] != nullptr; i++ ) {
        delete data[i];
        data[i] = nullptr;
    }
}


void ClacStack::drop( )       // Discard level 1 of the stack.
{
    Entity *temp = pop( );    // pop item off of the stack.
    if( temp == nullptr )
        error_message( "Can't drop from an empty stack" );
    delete temp;
}


size_t ClacStack::height( )  // Depth of the stack.
{
    size_t C = 0;
    for( size_t i = 0; i < STACK_SIZE-1; i++ ) {
        if( data[i] != nullptr )
            C++;
    }
    return C;
}


void ClacStack::roll_down( const VeryLong &count )
{
    size_t raw_count = static_cast<size_t>( count.to_long( ) );
    if( raw_count == 0 ) raw_count = 1;
    if( raw_count > height( ) )
        error_message( "Stack not high enough to roll" );
    else {
        Entity *temp  = data[0];
        for( size_t i = 0; i < raw_count - 1; i++ ) {
            data[i] = data[i + 1];
        }
        data[raw_count - 1] = temp;
    }
}


void ClacStack::roll_up( const VeryLong &count )
{
    size_t raw_count = static_cast<size_t>( count.to_long( ) );
    if( raw_count == 0 ) raw_count = 1;
    if( raw_count > height( ) )
        error_message( "Stack not high enough to roll" );
    else {
        Entity *temp  = data[raw_count - 1];
        for( size_t i = raw_count - 1; i > 0; i-- ) {
            data[i] = data[i - 1];
        }
        data[0] = temp;
    }
}


void ClacStack::rotate( )
{
    if( data[0] != nullptr && data[1] != nullptr && data[2] != nullptr ) {
        Entity *temp = data[2];
        data[2] = data[1];
        data[1] = data[0];
        data[0] = temp;
    }
    else {
        error_message( "Too few arguments" );
    }
}


void ClacStack::swap( )
{
    if( data[0] != nullptr && data[1] != nullptr ) {
        Entity *temp = data[0];
        data[0] = data[1];
        data[1] = temp;
    }
    else {
        error_message( "Too few arguments" );
    }
}
