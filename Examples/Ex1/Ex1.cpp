// Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<windows.h> //for sleep()
#include "stdafx.h"
#include <string.h>
#include <cstdio>


#include "Economy.hpp" //contains all other headers by inheritance

/*EXEMPLE 1 : Ganja trip to moon
You are a pirate , and must deliver some good indian medicine to miners on moon .
How to use the lib for that ?
Follow the comments ...
*/


int _tmain(int argc, _TCHAR* argv[])
{
//create economy
Economy globalEco;

//create our bases
Base earthbase;
Base moonbase;
//create the factory
Factory earthFactory;

//define cargo type
//Args=std::string name, std::string category, float mass, float volume,float price
CargoType ganja("Ganja","Contraband",10,25,1);

//define a cargoHolder for the base
Cargo earthbaseCargoHolder;
Cargo contrabandcargo;
Cargo ganjacargo;

//add cargo
contrabandcargo.addCargo(ganja,1);
ganjacargo.addCargo(ganja,10);
contrabandcargo.addCargo(ganjacargo);

//set up the ganja industry
//option input,output
ProductionOption earthProdOptGanja(ganjacargo,contrabandcargo);

//add option to factory
earthFactory.addProductionOption(earthProdOptGanja);
earthFactory.setProductionOption(earthProdOptGanja);

//add baseto global economy
globalEco.addBase(earthbase);
globalEco.addBase(moonbase);
//add storecargo
earthbase.addCargo(contrabandcargo);
//link factory
earthbase.addFactory(earthFactory);

bool quit=false;
int distanceToMoon=200;//384400;
while(!quit)
{
//update the market engine
globalEco.tick();
//decoration...
if(distanceToMoon==200)
  {
   printf("\nLocation :Earth \nBase : Pirate\n Factory production :%s\n",earthbase.getCargo().getName().c_str());
   printf("\nXML Boarding code :\n%s\n",earthbase.getCargo().getXML().c_str());
   printf("\nQuantity of cargo = %i",earthbase.getCargo().getCount(ganja));
   printf("\n\n***  Vessel launched to moon *** \n");
  }
  
Sleep(100);// gameplay eh eh
printf(".");// movement of the vessel
distanceToMoon--;

if(distanceToMoon==0)
 {
 //remove cargo from vessel
 printf("\n\n*** Vessel has landed on the Moon Base ***\n");
 printf("\n-Unload of the Vessel started \n");
 //decoration ...
 for(int i=0;i<20;i++)
 {printf(".");Sleep(100);}
 moonbase.addCargo(earthbase.getCargo());
 //empty the vessel
 earthbase.delCargo(earthbase.getCargo());
 printf("\n-Ganja quantity delivered to moon : %i\n",moonbase.getCargo().getCount(ganja));
 //check for vessel room
 printf("-Cargo remaining in Vessel : %i \n",earthbase.getCargo().getCount(ganja));
 quit=true;
 }
}
return 0;
}

