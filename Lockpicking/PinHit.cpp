#include "PinHit.h"

PinHit::PinHit() {
    //unneeded as PinHit vector push_backs all newly added pin combinations, so left blank
}

PinHit::PinHit(int key, int value) : m_pin(key), m_hits(value){
    //sets key to m_pin and value to m_hits
}

void PinHit::SetKey(int pin) {//sets the pin
    m_pin = pin;
}

int PinHit::GetKey() const { //returns the pin combination
    return m_pin;
}

int PinHit::GetValue() const { //returns frequency
    return m_hits;
}

void PinHit::IncrementHits() { //increments frequency
    m_hits++;
}

int PinHit::CompareTo(const PinHit& other) const {
    if (this->m_hits == other.m_hits) //used to check if frequency is larger or smaller than one it's comparing to, returning value depending on if smaller, larger, or equal
        return 0;
    else if(this->m_hits > other.m_hits)
        return 1;
    else
    {
        return -1;
    }
    
}

bool PinHit::operator==(const PinHit& other) { //comparing if two pin combinations are equal
    return (this->m_pin == other.m_pin);
}
