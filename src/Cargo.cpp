#include <cassert>
#include <sstream>
//#include <vector>
#include "Cargo.hpp"

Cargo::Cargo() : cargo(std::map<CargoType, unsigned int>()) {}

Cargo::~Cargo()
{
}


void Cargo::addCargo(const CargoType& type, unsigned int quantity) {
  assert(quantity != 0);
  Cargo::iterator current = this->cargo.find(type);
  if (current != this->end()) {
    quantity += current->second;
  }
  this->cargo[type] = quantity;
}

void Cargo::addCargo(const Cargo& newCargo) {
  if(newCargo.cargo.empty()){return;}
  Cargo::const_iterator newStock;
  for (newStock = newCargo.begin(); newStock != newCargo.end(); ++newStock)
   {
    this->addCargo(newStock->first, newStock->second);
  }
}

bool Cargo::delCargo(const Cargo& newCargo) {
  if (this == &newCargo) {
    this->cargo.clear();
    return true;
  }
  if(newCargo.cargo.empty()){
    return true;
  }

  if (this->contains(newCargo) == false) {
    return false;
  }

  for (Cargo::const_iterator newStock = newCargo.begin(); newStock != newCargo.end(); ++newStock) {
    this->cargo[newStock->first] -= newStock->second;
    if (this->cargo[newStock->first] == 0) {
      this->cargo.erase(newStock->first);
    }
  }
  return true;
}


unsigned int Cargo::getCount(const CargoType& type) const {
  unsigned int result = 0;
  std::map<CargoType, unsigned int>::const_iterator thing =  this->cargo.find(type);
  if (thing != this->cargo.end()){
    result = thing->second;
  }
  return result;
}

bool Cargo::contains(const Cargo& newCargo) const {
  
  if (newCargo.cargo.empty()) {
    return true;
  }
  if (this->cargo.empty()) {
    return false;
  }
  
  Cargo::const_iterator newStock;
  for (newStock = newCargo.begin(); newStock != newCargo.end(); ++newStock) {
    if (this->cargo.find(newStock->first) == this->cargo.end()) {
      return false;
    }

     
#if __cplusplus > 199711L
 if (this->cargo.at(newStock->first) < newStock->second) {return false;}
#else
 if (this->cargo.find(newStock->first)->second< newStock->second) {return false;}
#endif   
   
  }
  return true;
}

bool Cargo::operator==(const Cargo &that) const {
  return this->cargo == that.cargo;
}

/** String representation of this Cargo
  * @by ezee */
std::string Cargo::getName() const 
{
    
    for(Cargo::const_iterator i = this->cargo.begin();
		i != this->cargo.end(); ++i)
		{return i->first.getName();}
	
	
	}
std::string Cargo::getXML() const {
	std::stringstream xmlstream;
	xmlstream<<"<Cargo>";

	for(Cargo::const_iterator i = this->cargo.begin();
		i != this->cargo.end(); ++i){
		xmlstream<<"<pair>"<<i->first.getXML()<<"<value>"<<i->second<<"</value></pair>";
	}
	xmlstream<<"</Cargo>";
	return xmlstream.str();
}

Cargo::const_iterator Cargo::begin() const { return this->cargo.begin(); }

Cargo::iterator Cargo::begin() { return this->cargo.begin(); }

Cargo::const_iterator Cargo::end() const { return this->cargo.end(); }

Cargo::iterator Cargo::end() { return this->cargo.end(); }
