/*! \file    ClacStack.cpp
 *  \brief   This file contains...
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include "ClacStack.hpp"
#include "support.hpp"

using namespace std;
using namespace spica; // TODO: Remove this using directive.

ClacStack::~ClacStack()
{
    for (Entity* item_pointer : data) {
        delete item_pointer;
    }
}

bool ClacStack::push(Entity* item)
{
    data.push_front(item);
    return true;
}

Entity* ClacStack::pop()
{
    if (data.empty())
        return nullptr;

    Entity* return_value = data.front();
    data.pop_front();
    return return_value;
}

Entity* ClacStack::get(const VeryLong& index)
{
    Entity* return_value = nullptr;

    if (index < data.size()) {
        return_value = data[index.to_long()];
    }
    return return_value;
}

void ClacStack::put(Entity* new_object)
{
    if (data.empty()) {
        data.push_front(new_object);
        return;
    }
    delete data[0];
    data[0] = new_object;
}

void ClacStack::clear()
{
    for (Entity* item_pointer : data) {
        delete item_pointer;
    }
    data.clear();
}

void ClacStack::drop()
{
    Entity* temp = pop();
    if (temp == nullptr)
        error_message("Can't drop from an empty stack");
    delete temp;
}

size_t ClacStack::height()
{
    return data.size();
}

void ClacStack::roll_down(const VeryLong& count)
{
    auto raw_count = static_cast<size_t>(count.to_long());
    if (raw_count == 0)
        raw_count = 1;
    if (raw_count > height())
        error_message("Stack not high enough to roll");
    else {
        Entity* temp = data[0];
        for (size_t i = 0; i < raw_count - 1; i++) {
            data[i] = data[i + 1];
        }
        data[raw_count - 1] = temp;
    }
}

void ClacStack::roll_up(const VeryLong& count)
{
    auto raw_count = static_cast<size_t>(count.to_long());
    if (raw_count == 0)
        raw_count = 1;
    if (raw_count > height())
        error_message("Stack not high enough to roll");
    else {
        Entity* temp = data[raw_count - 1];
        for (size_t i = raw_count - 1; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = temp;
    }
}

void ClacStack::rotate()
{
    if (height() < 3)
        error_message("Stack not high enough to rotate");
    else {
        Entity* temp = data[2];
        data[2] = data[1];
        data[1] = data[0];
        data[0] = temp;
    }
}

void ClacStack::swap()
{
    if (height() < 2)
        error_message("Stack not high enough to swap");
    else {
        Entity* temp = data[1];
        data[1] = data[0];
        data[0] = temp;
    }
}
