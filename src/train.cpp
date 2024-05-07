// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): countOp(0), first(nullptr) {}

int Train::getOpCount() {
    return countOp;
}

void Train::addCage(bool light) {
    if (first == nullptr) {
        first = new Cage;
        first->light = light;
        first->next = nullptr;
        first->prev = nullptr;
    } else if (first && !first->next) {
        first->next = new Cage;
        first->next->light = light;
        first->next->next = first;
        first->prev = first->next;
        first->next->prev = first;
    } else {
        Cage* temp = first;
        do {
            temp = temp->next;
        } while (temp->next != first);
        temp->next = new Cage;
        temp->next->light = light;
        temp->next->prev = temp;
        temp->next->next = first;
        first->prev = temp->next;
    }
}

int Train::getLength() {
    int len1 = 0, len = 0;
    Cage* temp = first;
    if (!first->light)
        first->light = true;
    while (!temp->next->light) {
        temp = temp->next;
        countOp++;
        len++;
    }
    temp = temp->next;
    countOp++;
    len++;
    temp->light = false;
    len1 = len;
    while (len != 0) {
        temp = temp->prev;
        len--;
        countOp++;
    }
    if (!temp->light)
        return len1;
    else
        return getLength();
}
