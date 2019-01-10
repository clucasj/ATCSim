/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include <list>
#include <fstream>

namespace atcsim{

    // PUNTOS DE ESPERA
    // Para x>8500, y>0
    Position pos_wait_izq_1(15000.0, 15000.0, 3500.0);
    Position pos_wait_izq_2(15000.0, 9000.0, 3500.0);
    Position pos_wait_izq_3(15000.0, 2500.0, 3500.0);
    Position pos_wait_izq_4(10500.0, 2500.0, 3500.0);
    Position pos_wait_izq_5(9000.0, 8750.0, 3500.0);
    Position pos_wait_izq_6(10500.0, 15000.0, 3500.0);
    Position pos_wait_izq_7(15000.0, 15000.0, 3000.0);
    Position pos_wait_izq_8(15000.0, 9000.0, 2400.0);
    Position pos_wait_izq_9(15000.0, 2500.0, 2400.0);
    Position pos_wait_izq_10(10500.0, 2500.0, 2400.0);
    Position pos_wait_izq_11(9000.0, 8750.0, 2400.0);
    Position pos_wait_izq_12(10500.0, 15000.0, 2400.0);
    Position pos_wait_izq_13(15000.0, 15000.0, 2000.0);
    Position pos_wait_izq_14(15000.0, 9000.0, 1300.0);
    Position pos_wait_izq_15(15000.0, 2500.0, 1300.0);
    Position pos_wait_izq_16(10500.0, 2500.0, 1300.0);
    Position pos_wait_izq_17(9000.0, 8750.0, 1300.0);
    Position pos_wait_izq_18(10500.0, 15000.0, 1300.0);
    Position pos_wait_izq_19(15000.0, 15000.0, 1300.0);
    Position pos_subida_izq_1(15000.0, 9000.0, 2400.0);
    Position pos_subida_izq_2(15000.0, 2500.0, 3500.0);

    // Para x<8500, y>0
    Position pos_wait_izq_20(7000.0, 15000.0, 3500.0);
    Position pos_wait_izq_21(7000.0, 7000.0, 3500.0);
    Position pos_wait_izq_22(2000.0, 7000.0, 3500.0);
    Position pos_wait_izq_23(2000.0, 15000.0, 3500.0);
    Position pos_wait_izq_24(7000.0, 15000.0, 3000.0);
    Position pos_wait_izq_25(7000.0, 7000.0, 2400.0);
    Position pos_wait_izq_26(2000.0, 7000.0, 2400.0);
    Position pos_wait_izq_27(2000.0, 15000.0, 2400.0);
    Position pos_wait_izq_28(7000.0, 15000.0, 2000.0);
    Position pos_wait_izq_29(7000.0, 7000.0, 1300.0);
    Position pos_wait_izq_30(2000.0, 7000.0, 1300.0);
    Position pos_wait_izq_31(2000.0, 15000.0, 1300.0);
    Position pos_wait_izq_32(7000.0, 15000.0, 1300.0);
    Position pos_subida_izq_3(7000.0, 11000.0, 2400.0);
    Position pos_subida_izq_4(7000.0, 7000.0, 3500.0);

    // Para x>8500, y<0
    Position pos_wait_dcha_1(15000.0, -15000.0, 3500.0);
    Position pos_wait_dcha_2(15000.0, -9000.0, 3500.0);
    Position pos_wait_dcha_3(15000.0, -2500.0, 3500.0);
    Position pos_wait_dcha_4(10500.0, -2500.0, 3500.0);
    Position pos_wait_dcha_5(9000.0, -8750.0, 3500.0);
    Position pos_wait_dcha_6(10500.0, -15000.0, 3500.0);
    Position pos_wait_dcha_7(15000.0, -15000.0, 3000.0);
    Position pos_wait_dcha_8(15000.0, -9000.0, 2400.0);
    Position pos_wait_dcha_9(15000.0, -2500.0, 2400.0);
    Position pos_wait_dcha_10(10500.0, -2500.0, 2400.0);
    Position pos_wait_dcha_11(9000.0, -8750.0, 2400.0);
    Position pos_wait_dcha_12(10500.0, -15000.0, 2400.0);
    Position pos_wait_dcha_13(15000.0, -15000.0, 2000.0);
    Position pos_wait_dcha_14(15000.0, -9000.0, 1300.0);
    Position pos_wait_dcha_15(15000.0, -2500.0, 1300.0);
    Position pos_wait_dcha_16(10500.0, -2500.0, 1300.0);
    Position pos_wait_dcha_17(9000.0, -8750.0, 1300.0);
    Position pos_wait_dcha_18(10500.0, -15000.0, 1300.0);
    Position pos_wait_dcha_19(15000.0, -15000.0, 1300.0);
    Position pos_subida_dcha_1(15000.0, -9000.0, 2400.0);
    Position pos_subida_dcha_2(15000.0, -2500.0, 3500.0);

    // Para x<8500, y<0
    Position pos_wait_dcha_20(7000.0, -15000.0, 3500.0);
    Position pos_wait_dcha_21(7000.0, -7000.0, 3500.0);
    Position pos_wait_dcha_22(2000.0, -7000.0, 3500.0);
    Position pos_wait_dcha_23(2000.0, -15000.0, 3500.0);
    Position pos_wait_dcha_24(7000.0, -15000.0, 3000.0);
    Position pos_wait_dcha_25(7000.0, -7000.0, 2400.0);
    Position pos_wait_dcha_26(2000.0, -7000.0, 2400.0);
    Position pos_wait_dcha_27(2000.0, -15000.0, 2400.0);
    Position pos_wait_dcha_28(7000.0, -15000.0, 2000.0);
    Position pos_wait_dcha_29(7000.0, -7000.0, 1300.0);
    Position pos_wait_dcha_30(2000.0, -7000.0, 1300.0);
    Position pos_wait_dcha_31(2000.0, -15000.0, 1300.0);
    Position pos_wait_dcha_32(7000.0, -15000.0, 1300.0);
    Position pos_subida_dcha_3(7000.0, -11000.0, 2400.0);
    Position pos_subida_dcha_4(7000.0, -7000.0, 3500.0);


    // PUNTOS DE ATERRIZAJE
    Position pos_aterrizaje_1(3500.0, 0.0, 100.0);
    Position pos_aterrizaje_2(1500.0, 0.0, 50);
    Position pos_aterrizaje_3(200.0, 0.0, 25.0);
    Position pos_aterrizaje_4(-750.0, 0.0, 25.0);

    Position pos_aterrizaje_izq_1(2100.0, 2500.0, 100.0);
    Position pos_aterrizaje_izq_2(1950.0, 2000.0, 100.0);
    Position pos_aterrizaje_izq_3(1800.0, 1250.0, 80.0);
    Position pos_aterrizaje_izq_4(1725.0, 1000.0, 75.0);
    Position pos_aterrizaje_izq_5(1650.0, 750.0, 75.0);
    Position pos_aterrizaje_izq_6(1575.0, 500.0, 75.0);
    Position pos_aterrizaje_izq_7(1500.0, 250.0, 75.0);
    Position pos_aterrizaje_izq_8(1000.0, 0.0, 50.0);
    Position pos_aterrizaje_izq_9(200.0, 0.0, 25.0);
    Position pos_aterrizaje_izq_10(-750.0, 0.0, 25.0);

    Position pos_aterrizaje_dcha_1(2100.0, -2500.0, 100.0);
    Position pos_aterrizaje_dcha_2(1950.0, -2000.0, 100.0);
    Position pos_aterrizaje_dcha_3(1800.0, -1250.0, 80.0);
    Position pos_aterrizaje_dcha_4(1725.0, -1000.0, 75.0);
    Position pos_aterrizaje_dcha_5(1650.0, -750.0, 75.0);
    Position pos_aterrizaje_dcha_6(1575.0, -500.0, 75.0);
    Position pos_aterrizaje_dcha_7(1500.0, -250.0, 75.0);
    Position pos_aterrizaje_dcha_8(1000.0, 0.0, 50.0);
    Position pos_aterrizaje_dcha_9(200.0, 0.0, 25.0);
    Position pos_aterrizaje_dcha_10(-750.0, 0.0, 25.0);


    // RUTAS DE ESPERA
    // Para x>8500, y>0
    Route r1_w_izq, r2_w_izq, r3_w_izq, r4_w_izq, r5_w_izq, r6_w_izq, r7_w_izq, r8_w_izq, r9_w_izq, r10_w_izq,
    r11_w_izq, r12_w_izq, r13_w_izq, r14_w_izq, r15_w_izq, r16_w_izq, r17_w_izq, r18_w_izq, r19_w_izq, r1_subida_izq, r2_subida_izq;

    // Para x<8500, y>0
    Route r20_w_izq, r21_w_izq, r22_w_izq, r23_w_izq, r24_w_izq, r25_w_izq, r26_w_izq, r27_w_izq, r28_w_izq,
    r29_w_izq, r30_w_izq, r31_w_izq, r32_w_izq, r3_subida_izq, r4_subida_izq;

    // Para x>8500, y<0
    Route r1_w_dcha, r2_w_dcha, r3_w_dcha, r4_w_dcha, r5_w_dcha, r6_w_dcha, r7_w_dcha, r8_w_dcha, r9_w_dcha, r10_w_dcha,
    r11_w_dcha, r12_w_dcha, r13_w_dcha, r14_w_dcha, r15_w_dcha, r16_w_dcha, r17_w_dcha, r18_w_dcha, r19_w_dcha, r1_subida_dcha, r2_subida_dcha;

    // Para x<8500, y<0
    Route r20_w_dcha, r21_w_dcha, r22_w_dcha, r23_w_dcha, r24_w_dcha, r25_w_dcha, r26_w_dcha, r27_w_dcha, r28_w_dcha,
    r29_w_dcha, r30_w_dcha, r31_w_dcha, r32_w_dcha, r3_subida_dcha, r4_subida_dcha;

    // RUTAS DE ATERRIZAJE
    Route ra1, ra2, ra3, ra4;

    Route r1_a_izq, r2_a_izq, r3_a_izq, r4_a_izq, r5_a_izq, r6_a_izq, r7_a_izq, r8_a_izq, r9_a_izq, r10_a_izq;

    Route r1_a_dcha, r2_a_dcha, r3_a_dcha, r4_a_dcha, r5_a_dcha, r6_a_dcha, r7_a_dcha, r8_a_dcha, r9_a_dcha, r10_a_dcha;


AirController::AirController() {
	// TODO Auto-generated constructor stub
}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}


std::list<Flight*>::iterator ruta_noroeste_1(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r1_w_izq);
      (*it)->getRoute()->push_back(r2_w_izq);
      (*it)->getRoute()->push_back(r3_w_izq);
      (*it)->getRoute()->push_back(r4_w_izq);
      (*it)->getRoute()->push_back(r5_w_izq);
      (*it)->getRoute()->push_back(r6_w_izq);
      (*it)->getRoute()->push_back(r7_w_izq);
      (*it)->getRoute()->push_back(r8_w_izq);
      (*it)->getRoute()->push_back(r9_w_izq);
      (*it)->getRoute()->push_back(r10_w_izq);
      (*it)->getRoute()->push_back(r11_w_izq);
      (*it)->getRoute()->push_back(r12_w_izq);
      (*it)->getRoute()->push_back(r13_w_izq);
      (*it)->getRoute()->push_back(r14_w_izq);
      (*it)->getRoute()->push_back(r15_w_izq);
      (*it)->getRoute()->push_back(r16_w_izq);
      (*it)->getRoute()->push_back(r17_w_izq);
      (*it)->getRoute()->push_back(r18_w_izq);
      (*it)->getRoute()->push_back(r19_w_izq);

      (*it)->getRoute()->push_back(r1_subida_izq);
      (*it)->getRoute()->push_back(r2_subida_izq);
      (*it)->getRoute()->push_back(r4_w_izq);
      (*it)->getRoute()->push_back(r5_w_izq);
      (*it)->getRoute()->push_back(r6_w_izq);
      (*it)->getRoute()->push_back(r7_w_izq);
      (*it)->getRoute()->push_back(r8_w_izq);
      (*it)->getRoute()->push_back(r9_w_izq);
      (*it)->getRoute()->push_back(r10_w_izq);
      (*it)->getRoute()->push_back(r11_w_izq);
      (*it)->getRoute()->push_back(r12_w_izq);
      (*it)->getRoute()->push_back(r13_w_izq);
      (*it)->getRoute()->push_back(r14_w_izq);
      (*it)->getRoute()->push_back(r15_w_izq);
      (*it)->getRoute()->push_back(r16_w_izq);
      (*it)->getRoute()->push_back(r17_w_izq);
      (*it)->getRoute()->push_back(r18_w_izq);
      (*it)->getRoute()->push_back(r19_w_izq);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_noroeste_2(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r2_w_izq);
      (*it)->getRoute()->push_back(r3_w_izq);
      (*it)->getRoute()->push_back(r4_w_izq);
      (*it)->getRoute()->push_back(r5_w_izq);
      (*it)->getRoute()->push_back(r6_w_izq);
      (*it)->getRoute()->push_back(r7_w_izq);
      (*it)->getRoute()->push_back(r8_w_izq);
      (*it)->getRoute()->push_back(r9_w_izq);
      (*it)->getRoute()->push_back(r10_w_izq);
      (*it)->getRoute()->push_back(r11_w_izq);
      (*it)->getRoute()->push_back(r12_w_izq);
      (*it)->getRoute()->push_back(r13_w_izq);
      (*it)->getRoute()->push_back(r14_w_izq);
      (*it)->getRoute()->push_back(r15_w_izq);
      (*it)->getRoute()->push_back(r16_w_izq);
      (*it)->getRoute()->push_back(r17_w_izq);
      (*it)->getRoute()->push_back(r18_w_izq);
      (*it)->getRoute()->push_back(r19_w_izq);

      (*it)->getRoute()->push_back(r1_subida_izq);
      (*it)->getRoute()->push_back(r2_subida_izq);
      (*it)->getRoute()->push_back(r4_w_izq);
      (*it)->getRoute()->push_back(r5_w_izq);
      (*it)->getRoute()->push_back(r6_w_izq);
      (*it)->getRoute()->push_back(r7_w_izq);
      (*it)->getRoute()->push_back(r8_w_izq);
      (*it)->getRoute()->push_back(r9_w_izq);
      (*it)->getRoute()->push_back(r10_w_izq);
      (*it)->getRoute()->push_back(r11_w_izq);
      (*it)->getRoute()->push_back(r12_w_izq);
      (*it)->getRoute()->push_back(r13_w_izq);
      (*it)->getRoute()->push_back(r14_w_izq);
      (*it)->getRoute()->push_back(r15_w_izq);
      (*it)->getRoute()->push_back(r16_w_izq);
      (*it)->getRoute()->push_back(r17_w_izq);
      (*it)->getRoute()->push_back(r18_w_izq);
      (*it)->getRoute()->push_back(r19_w_izq);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_noroeste_3(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r3_w_izq);
      (*it)->getRoute()->push_back(r4_w_izq);
      (*it)->getRoute()->push_back(r5_w_izq);
      (*it)->getRoute()->push_back(r6_w_izq);
      (*it)->getRoute()->push_back(r7_w_izq);
      (*it)->getRoute()->push_back(r8_w_izq);
      (*it)->getRoute()->push_back(r9_w_izq);
      (*it)->getRoute()->push_back(r10_w_izq);
      (*it)->getRoute()->push_back(r11_w_izq);
      (*it)->getRoute()->push_back(r12_w_izq);
      (*it)->getRoute()->push_back(r13_w_izq);
      (*it)->getRoute()->push_back(r14_w_izq);
      (*it)->getRoute()->push_back(r15_w_izq);
      (*it)->getRoute()->push_back(r16_w_izq);
      (*it)->getRoute()->push_back(r17_w_izq);
      (*it)->getRoute()->push_back(r18_w_izq);
      (*it)->getRoute()->push_back(r19_w_izq);

      (*it)->getRoute()->push_back(r1_subida_izq);
      (*it)->getRoute()->push_back(r2_subida_izq);
      (*it)->getRoute()->push_back(r4_w_izq);
      (*it)->getRoute()->push_back(r5_w_izq);
      (*it)->getRoute()->push_back(r6_w_izq);
      (*it)->getRoute()->push_back(r7_w_izq);
      (*it)->getRoute()->push_back(r8_w_izq);
      (*it)->getRoute()->push_back(r9_w_izq);
      (*it)->getRoute()->push_back(r10_w_izq);
      (*it)->getRoute()->push_back(r11_w_izq);
      (*it)->getRoute()->push_back(r12_w_izq);
      (*it)->getRoute()->push_back(r13_w_izq);
      (*it)->getRoute()->push_back(r14_w_izq);
      (*it)->getRoute()->push_back(r15_w_izq);
      (*it)->getRoute()->push_back(r16_w_izq);
      (*it)->getRoute()->push_back(r17_w_izq);
      (*it)->getRoute()->push_back(r18_w_izq);
      (*it)->getRoute()->push_back(r19_w_izq);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_suroeste(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r20_w_izq);
      (*it)->getRoute()->push_back(r21_w_izq);
      (*it)->getRoute()->push_back(r22_w_izq);
      (*it)->getRoute()->push_back(r23_w_izq);
      (*it)->getRoute()->push_back(r24_w_izq);
      (*it)->getRoute()->push_back(r25_w_izq);
      (*it)->getRoute()->push_back(r26_w_izq);
      (*it)->getRoute()->push_back(r27_w_izq);
      (*it)->getRoute()->push_back(r28_w_izq);
      (*it)->getRoute()->push_back(r29_w_izq);
      (*it)->getRoute()->push_back(r30_w_izq);
      (*it)->getRoute()->push_back(r31_w_izq);
      (*it)->getRoute()->push_back(r32_w_izq);

      (*it)->getRoute()->push_back(r3_subida_izq);
      (*it)->getRoute()->push_back(r4_subida_izq);
      (*it)->getRoute()->push_back(r22_w_izq);
      (*it)->getRoute()->push_back(r23_w_izq);
      (*it)->getRoute()->push_back(r24_w_izq);
      (*it)->getRoute()->push_back(r25_w_izq);
      (*it)->getRoute()->push_back(r26_w_izq);
      (*it)->getRoute()->push_back(r27_w_izq);
      (*it)->getRoute()->push_back(r28_w_izq);
      (*it)->getRoute()->push_back(r29_w_izq);
      (*it)->getRoute()->push_back(r30_w_izq);
      (*it)->getRoute()->push_back(r31_w_izq);
      (*it)->getRoute()->push_back(r32_w_izq);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_noreste_1(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r1_w_dcha);
      (*it)->getRoute()->push_back(r2_w_dcha);
      (*it)->getRoute()->push_back(r3_w_dcha);
      (*it)->getRoute()->push_back(r4_w_dcha);
      (*it)->getRoute()->push_back(r5_w_dcha);
      (*it)->getRoute()->push_back(r6_w_dcha);
      (*it)->getRoute()->push_back(r7_w_dcha);
      (*it)->getRoute()->push_back(r8_w_dcha);
      (*it)->getRoute()->push_back(r9_w_dcha);
      (*it)->getRoute()->push_back(r10_w_dcha);
      (*it)->getRoute()->push_back(r11_w_dcha);
      (*it)->getRoute()->push_back(r12_w_dcha);
      (*it)->getRoute()->push_back(r13_w_dcha);
      (*it)->getRoute()->push_back(r14_w_dcha);
      (*it)->getRoute()->push_back(r15_w_dcha);
      (*it)->getRoute()->push_back(r16_w_dcha);
      (*it)->getRoute()->push_back(r17_w_dcha);
      (*it)->getRoute()->push_back(r18_w_dcha);
      (*it)->getRoute()->push_back(r19_w_dcha);

      (*it)->getRoute()->push_back(r1_subida_dcha);
      (*it)->getRoute()->push_back(r2_subida_dcha);
      (*it)->getRoute()->push_back(r4_w_dcha);
      (*it)->getRoute()->push_back(r5_w_dcha);
      (*it)->getRoute()->push_back(r6_w_dcha);
      (*it)->getRoute()->push_back(r7_w_dcha);
      (*it)->getRoute()->push_back(r8_w_dcha);
      (*it)->getRoute()->push_back(r9_w_dcha);
      (*it)->getRoute()->push_back(r10_w_dcha);
      (*it)->getRoute()->push_back(r11_w_dcha);
      (*it)->getRoute()->push_back(r12_w_dcha);
      (*it)->getRoute()->push_back(r13_w_dcha);
      (*it)->getRoute()->push_back(r14_w_dcha);
      (*it)->getRoute()->push_back(r15_w_dcha);
      (*it)->getRoute()->push_back(r16_w_dcha);
      (*it)->getRoute()->push_back(r17_w_dcha);
      (*it)->getRoute()->push_back(r18_w_dcha);
      (*it)->getRoute()->push_back(r19_w_dcha);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_noreste_2(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r2_w_dcha);
      (*it)->getRoute()->push_back(r3_w_dcha);
      (*it)->getRoute()->push_back(r4_w_dcha);
      (*it)->getRoute()->push_back(r5_w_dcha);
      (*it)->getRoute()->push_back(r6_w_dcha);
      (*it)->getRoute()->push_back(r7_w_dcha);
      (*it)->getRoute()->push_back(r8_w_dcha);
      (*it)->getRoute()->push_back(r9_w_dcha);
      (*it)->getRoute()->push_back(r10_w_dcha);
      (*it)->getRoute()->push_back(r11_w_dcha);
      (*it)->getRoute()->push_back(r12_w_dcha);
      (*it)->getRoute()->push_back(r13_w_dcha);
      (*it)->getRoute()->push_back(r14_w_dcha);
      (*it)->getRoute()->push_back(r15_w_dcha);
      (*it)->getRoute()->push_back(r16_w_dcha);
      (*it)->getRoute()->push_back(r17_w_dcha);
      (*it)->getRoute()->push_back(r18_w_dcha);
      (*it)->getRoute()->push_back(r19_w_dcha);

      (*it)->getRoute()->push_back(r1_subida_dcha);
      (*it)->getRoute()->push_back(r2_subida_dcha);
      (*it)->getRoute()->push_back(r4_w_dcha);
      (*it)->getRoute()->push_back(r5_w_dcha);
      (*it)->getRoute()->push_back(r6_w_dcha);
      (*it)->getRoute()->push_back(r7_w_dcha);
      (*it)->getRoute()->push_back(r8_w_dcha);
      (*it)->getRoute()->push_back(r9_w_dcha);
      (*it)->getRoute()->push_back(r10_w_dcha);
      (*it)->getRoute()->push_back(r11_w_dcha);
      (*it)->getRoute()->push_back(r12_w_dcha);
      (*it)->getRoute()->push_back(r13_w_dcha);
      (*it)->getRoute()->push_back(r14_w_dcha);
      (*it)->getRoute()->push_back(r15_w_dcha);
      (*it)->getRoute()->push_back(r16_w_dcha);
      (*it)->getRoute()->push_back(r17_w_dcha);
      (*it)->getRoute()->push_back(r18_w_dcha);
      (*it)->getRoute()->push_back(r19_w_dcha);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_noreste_3(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r3_w_dcha);
      (*it)->getRoute()->push_back(r4_w_dcha);
      (*it)->getRoute()->push_back(r5_w_dcha);
      (*it)->getRoute()->push_back(r6_w_dcha);
      (*it)->getRoute()->push_back(r7_w_dcha);
      (*it)->getRoute()->push_back(r8_w_dcha);
      (*it)->getRoute()->push_back(r9_w_dcha);
      (*it)->getRoute()->push_back(r10_w_dcha);
      (*it)->getRoute()->push_back(r11_w_dcha);
      (*it)->getRoute()->push_back(r12_w_dcha);
      (*it)->getRoute()->push_back(r13_w_dcha);
      (*it)->getRoute()->push_back(r14_w_dcha);
      (*it)->getRoute()->push_back(r15_w_dcha);
      (*it)->getRoute()->push_back(r16_w_dcha);
      (*it)->getRoute()->push_back(r17_w_dcha);
      (*it)->getRoute()->push_back(r18_w_dcha);
      (*it)->getRoute()->push_back(r19_w_dcha);

      (*it)->getRoute()->push_back(r1_subida_dcha);
      (*it)->getRoute()->push_back(r2_subida_dcha);
      (*it)->getRoute()->push_back(r4_w_dcha);
      (*it)->getRoute()->push_back(r5_w_dcha);
      (*it)->getRoute()->push_back(r6_w_dcha);
      (*it)->getRoute()->push_back(r7_w_dcha);
      (*it)->getRoute()->push_back(r8_w_dcha);
      (*it)->getRoute()->push_back(r9_w_dcha);
      (*it)->getRoute()->push_back(r10_w_dcha);
      (*it)->getRoute()->push_back(r11_w_dcha);
      (*it)->getRoute()->push_back(r12_w_dcha);
      (*it)->getRoute()->push_back(r13_w_dcha);
      (*it)->getRoute()->push_back(r14_w_dcha);
      (*it)->getRoute()->push_back(r15_w_dcha);
      (*it)->getRoute()->push_back(r16_w_dcha);
      (*it)->getRoute()->push_back(r17_w_dcha);
      (*it)->getRoute()->push_back(r18_w_dcha);
      (*it)->getRoute()->push_back(r19_w_dcha);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_sureste(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r20_w_dcha);
      (*it)->getRoute()->push_back(r21_w_dcha);
      (*it)->getRoute()->push_back(r22_w_dcha);
      (*it)->getRoute()->push_back(r23_w_dcha);
      (*it)->getRoute()->push_back(r24_w_dcha);
      (*it)->getRoute()->push_back(r25_w_dcha);
      (*it)->getRoute()->push_back(r26_w_dcha);
      (*it)->getRoute()->push_back(r27_w_dcha);
      (*it)->getRoute()->push_back(r28_w_dcha);
      (*it)->getRoute()->push_back(r29_w_dcha);
      (*it)->getRoute()->push_back(r30_w_dcha);
      (*it)->getRoute()->push_back(r31_w_dcha);
      (*it)->getRoute()->push_back(r32_w_dcha);

      (*it)->getRoute()->push_back(r3_subida_dcha);
      (*it)->getRoute()->push_back(r4_subida_dcha);
      (*it)->getRoute()->push_back(r22_w_dcha);
      (*it)->getRoute()->push_back(r23_w_dcha);
      (*it)->getRoute()->push_back(r24_w_dcha);
      (*it)->getRoute()->push_back(r25_w_dcha);
      (*it)->getRoute()->push_back(r26_w_dcha);
      (*it)->getRoute()->push_back(r27_w_dcha);
      (*it)->getRoute()->push_back(r28_w_dcha);
      (*it)->getRoute()->push_back(r29_w_dcha);
      (*it)->getRoute()->push_back(r30_w_dcha);
      (*it)->getRoute()->push_back(r31_w_dcha);
      (*it)->getRoute()->push_back(r32_w_dcha);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_aterrizaje_principal(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(ra1);
      (*it)->getRoute()->push_back(ra2);
      (*it)->getRoute()->push_back(ra3);
      (*it)->getRoute()->push_back(ra4);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_aterrizaje_izq(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r1_a_izq);
      (*it)->getRoute()->push_back(r2_a_izq);
      (*it)->getRoute()->push_back(r3_a_izq);
      (*it)->getRoute()->push_back(r4_a_izq);
      (*it)->getRoute()->push_back(r5_a_izq);
      (*it)->getRoute()->push_back(r6_a_izq);
      (*it)->getRoute()->push_back(r7_a_izq);
      (*it)->getRoute()->push_back(r8_a_izq);
      (*it)->getRoute()->push_back(r9_a_izq);
      (*it)->getRoute()->push_back(r10_a_izq);
    }
    it++;
  }
  return it;
}

std::list<Flight*>::iterator ruta_aterrizaje_dcha(std::string id)
{
  std::list<Flight*>::iterator it;
  std::list<Flight*> flights = Airport::getInstance()->getFlights();

  it = flights.begin();

  while(it != flights.end())
  {
    if((*it)->getId().compare(id) == 0)
    {
      (*it)->getRoute()->push_back(r1_a_dcha);
      (*it)->getRoute()->push_back(r2_a_dcha);
      (*it)->getRoute()->push_back(r3_a_dcha);
      (*it)->getRoute()->push_back(r4_a_dcha);
      (*it)->getRoute()->push_back(r5_a_dcha);
      (*it)->getRoute()->push_back(r6_a_dcha);
      (*it)->getRoute()->push_back(r7_a_dcha);
      (*it)->getRoute()->push_back(r8_a_dcha);
      (*it)->getRoute()->push_back(r9_a_dcha);
      (*it)->getRoute()->push_back(r10_a_dcha);
    }
    it++;
  }
  return it;
}


void
AirController::doWork()
{
  std::list<Flight*> flights = Airport::getInstance()->getFlights();
  std::list<Flight*>::iterator it, i;

  float velocidad_espera;
  velocidad_espera = 100.0;

  float velocidad_subida;
  velocidad_subida = 75.0;

  ra1.pos = pos_aterrizaje_1;
  ra1.speed = 200.0;
  ra2.pos = pos_aterrizaje_2;
  ra2.speed = 150.0;
  ra3.pos = pos_aterrizaje_3;
  ra3.speed = 19.0;
  ra4.pos = pos_aterrizaje_4;
  ra4.speed = 15.0;

  r1_a_izq.pos = pos_aterrizaje_izq_1;
  r1_a_izq.speed = 200.0;
  r2_a_izq.pos = pos_aterrizaje_izq_2;
  r2_a_izq.speed = 200.0;
  r3_a_izq.pos = pos_aterrizaje_izq_3;
  r3_a_izq.speed = 200.0;
  r4_a_izq.pos = pos_aterrizaje_izq_4;
  r4_a_izq.speed = 200.0;
  r5_a_izq.pos = pos_aterrizaje_izq_5;
  r5_a_izq.speed = 200.0;
  r6_a_izq.pos = pos_aterrizaje_izq_6;
  r6_a_izq.speed = 175.0;
  r7_a_izq.pos = pos_aterrizaje_izq_7;
  r7_a_izq.speed = 150.0;
  r8_a_izq.pos = pos_aterrizaje_izq_8;
  r8_a_izq.speed = 100.0;
  r9_a_izq.pos = pos_aterrizaje_izq_9;
  r9_a_izq.speed = 19.0;
  r10_a_izq.pos = pos_aterrizaje_izq_10;
  r10_a_izq.speed = 15.0;

  r1_a_dcha.pos = pos_aterrizaje_dcha_1;
  r1_a_dcha.speed = 200.0;
  r2_a_dcha.pos = pos_aterrizaje_dcha_2;
  r2_a_dcha.speed = 200.0;
  r3_a_dcha.pos = pos_aterrizaje_dcha_3;
  r3_a_dcha.speed = 200.0;
  r4_a_dcha.pos = pos_aterrizaje_dcha_4;
  r4_a_dcha.speed = 200.0;
  r5_a_dcha.pos = pos_aterrizaje_dcha_5;
  r5_a_dcha.speed = 200.0;
  r6_a_dcha.pos = pos_aterrizaje_dcha_6;
  r6_a_dcha.speed = 175.0;
  r7_a_dcha.pos = pos_aterrizaje_dcha_7;
  r7_a_dcha.speed = 150.0;
  r8_a_dcha.pos = pos_aterrizaje_dcha_8;
  r8_a_dcha.speed = 100.0;
  r9_a_dcha.pos = pos_aterrizaje_dcha_9;
  r9_a_dcha.speed = 19.0;
  r10_a_dcha.pos = pos_aterrizaje_dcha_10;
  r10_a_dcha.speed = 15.0;


  r1_w_izq.pos = pos_wait_izq_1;
  r1_w_izq.speed = velocidad_espera;
  r2_w_izq.pos = pos_wait_izq_2;
  r2_w_izq.speed = velocidad_espera;
  r3_w_izq.pos = pos_wait_izq_3;
  r3_w_izq.speed = velocidad_espera;
  r4_w_izq.pos = pos_wait_izq_4;
  r4_w_izq.speed = velocidad_espera;
  r5_w_izq.pos = pos_wait_izq_5;
  r5_w_izq.speed = velocidad_espera;
  r6_w_izq.pos = pos_wait_izq_6;
  r6_w_izq.speed = velocidad_espera;
  r7_w_izq.pos = pos_wait_izq_7;
  r7_w_izq.speed = velocidad_espera;
  r8_w_izq.pos = pos_wait_izq_8;
  r8_w_izq.speed = velocidad_espera;
  r9_w_izq.pos = pos_wait_izq_9;
  r9_w_izq.speed = velocidad_espera;
  r10_w_izq.pos = pos_wait_izq_10;
  r10_w_izq.speed = velocidad_espera;
  r11_w_izq.pos = pos_wait_izq_11;
  r11_w_izq.speed = velocidad_espera;
  r12_w_izq.pos = pos_wait_izq_12;
  r12_w_izq.speed = velocidad_espera;
  r13_w_izq.pos = pos_wait_izq_13;
  r13_w_izq.speed = velocidad_espera;
  r14_w_izq.pos = pos_wait_izq_14;
  r14_w_izq.speed = velocidad_espera;
  r15_w_izq.pos = pos_wait_izq_15;
  r15_w_izq.speed = velocidad_espera;
  r16_w_izq.pos = pos_wait_izq_16;
  r16_w_izq.speed = velocidad_espera;
  r17_w_izq.pos = pos_wait_izq_17;
  r17_w_izq.speed = velocidad_espera;
  r18_w_izq.pos = pos_wait_izq_18;
  r18_w_izq.speed = velocidad_espera;
  r19_w_izq.pos = pos_wait_izq_19;
  r19_w_izq.speed = velocidad_espera;

  r1_subida_izq.pos = pos_subida_izq_1;
  r1_subida_izq.speed = velocidad_subida;
  r2_subida_izq.pos = pos_subida_izq_2;
  r2_subida_izq.speed = velocidad_subida;

  r20_w_izq.pos = pos_wait_izq_20;
  r20_w_izq.speed = velocidad_espera;
  r21_w_izq.pos = pos_wait_izq_21;
  r21_w_izq.speed = velocidad_espera;
  r22_w_izq.pos = pos_wait_izq_22;
  r22_w_izq.speed = velocidad_espera;
  r23_w_izq.pos = pos_wait_izq_23;
  r23_w_izq.speed = velocidad_espera;
  r24_w_izq.pos = pos_wait_izq_24;
  r24_w_izq.speed = velocidad_espera;
  r25_w_izq.pos = pos_wait_izq_25;
  r25_w_izq.speed = velocidad_espera;
  r26_w_izq.pos = pos_wait_izq_26;
  r26_w_izq.speed = velocidad_espera;
  r27_w_izq.pos = pos_wait_izq_27;
  r27_w_izq.speed = velocidad_espera;
  r28_w_izq.pos = pos_wait_izq_28;
  r28_w_izq.speed = velocidad_espera;
  r29_w_izq.pos = pos_wait_izq_29;
  r29_w_izq.speed = velocidad_espera;
  r30_w_izq.pos = pos_wait_izq_30;
  r30_w_izq.speed = velocidad_espera;
  r31_w_izq.pos = pos_wait_izq_31;
  r31_w_izq.speed = velocidad_espera;
  r32_w_izq.pos = pos_wait_izq_32;
  r32_w_izq.speed = velocidad_espera;

  r3_subida_izq.pos = pos_subida_izq_3;
  r3_subida_izq.speed = velocidad_subida;
  r4_subida_izq.pos = pos_subida_izq_4;
  r4_subida_izq.speed = velocidad_subida;


  r1_w_dcha.pos = pos_wait_dcha_1;
  r1_w_dcha.speed = velocidad_espera;
  r2_w_dcha.pos = pos_wait_dcha_2;
  r2_w_dcha.speed = velocidad_espera;
  r3_w_dcha.pos = pos_wait_dcha_3;
  r3_w_dcha.speed = velocidad_espera;
  r4_w_dcha.pos = pos_wait_dcha_4;
  r4_w_dcha.speed = velocidad_espera;
  r5_w_dcha.pos = pos_wait_dcha_5;
  r5_w_dcha.speed = velocidad_espera;
  r6_w_dcha.pos = pos_wait_dcha_6;
  r6_w_dcha.speed = velocidad_espera;
  r7_w_dcha.pos = pos_wait_dcha_7;
  r7_w_dcha.speed = velocidad_espera;
  r8_w_dcha.pos = pos_wait_dcha_8;
  r8_w_dcha.speed = velocidad_espera;
  r9_w_dcha.pos = pos_wait_dcha_9;
  r9_w_dcha.speed = velocidad_espera;
  r10_w_dcha.pos = pos_wait_dcha_10;
  r10_w_dcha.speed = velocidad_espera;
  r11_w_dcha.pos = pos_wait_dcha_11;
  r11_w_dcha.speed = velocidad_espera;
  r12_w_dcha.pos = pos_wait_dcha_12;
  r12_w_dcha.speed = velocidad_espera;
  r13_w_dcha.pos = pos_wait_dcha_13;
  r13_w_dcha.speed = velocidad_espera;
  r14_w_dcha.pos = pos_wait_dcha_14;
  r14_w_dcha.speed = velocidad_espera;
  r15_w_dcha.pos = pos_wait_dcha_15;
  r15_w_dcha.speed = velocidad_espera;
  r16_w_dcha.pos = pos_wait_dcha_16;
  r16_w_dcha.speed = velocidad_espera;
  r17_w_dcha.pos = pos_wait_dcha_17;
  r17_w_dcha.speed = velocidad_espera;
  r18_w_dcha.pos = pos_wait_dcha_18;
  r18_w_dcha.speed = velocidad_espera;
  r19_w_dcha.pos = pos_wait_dcha_19;
  r19_w_dcha.speed = velocidad_espera;

  r1_subida_dcha.pos = pos_subida_dcha_1;
  r1_subida_dcha.speed = velocidad_subida;
  r2_subida_dcha.pos = pos_subida_dcha_2;
  r2_subida_dcha.speed = velocidad_subida;

  r20_w_dcha.pos = pos_wait_dcha_20;
  r20_w_dcha.speed = velocidad_espera;
  r21_w_dcha.pos = pos_wait_dcha_21;
  r21_w_dcha.speed = velocidad_espera;
  r22_w_dcha.pos = pos_wait_dcha_22;
  r22_w_dcha.speed = velocidad_espera;
  r23_w_dcha.pos = pos_wait_dcha_23;
  r23_w_dcha.speed = velocidad_espera;
  r24_w_dcha.pos = pos_wait_dcha_24;
  r24_w_dcha.speed = velocidad_espera;
  r25_w_dcha.pos = pos_wait_dcha_25;
  r25_w_dcha.speed = velocidad_espera;
  r26_w_dcha.pos = pos_wait_dcha_26;
  r26_w_dcha.speed = velocidad_espera;
  r27_w_dcha.pos = pos_wait_dcha_27;
  r27_w_dcha.speed = velocidad_espera;
  r28_w_dcha.pos = pos_wait_dcha_28;
  r28_w_dcha.speed = velocidad_espera;
  r29_w_dcha.pos = pos_wait_dcha_29;
  r29_w_dcha.speed = velocidad_espera;
  r30_w_dcha.pos = pos_wait_dcha_30;
  r30_w_dcha.speed = velocidad_espera;
  r31_w_dcha.pos = pos_wait_dcha_31;
  r31_w_dcha.speed = velocidad_espera;
  r32_w_dcha.pos = pos_wait_dcha_32;
  r32_w_dcha.speed = velocidad_espera;

  r3_subida_dcha.pos = pos_subida_dcha_3;
  r3_subida_dcha.speed = velocidad_subida;
  r4_subida_dcha.pos = pos_subida_dcha_4;
  r4_subida_dcha.speed = velocidad_subida;


  if(!Airport::getInstance()->is_booked_landing())
  {
    Flight* primero = *(flights.begin());
    primero->getRoute()->clear();
  }


  for(it = flights.begin(); it != flights.end(); ++it)
  {
    if((*it)->getRoute()->empty() && Airport::getInstance()->is_booked_landing())
    {
      if((*it)->getPosition().get_x() >= 8500 and (*it)->getPosition().get_x() <= 15000 and (*it)->getPosition().get_y() >= 15000){
        i = ruta_noroeste_1((*it)->getId());

      }else if((*it)->getPosition().get_x() > 15000 and (*it)->getPosition().get_y() >= 9250){
        i = ruta_noroeste_2((*it)->getId());

      }else if((*it)->getPosition().get_x() > 8500 and (*it)->getPosition().get_x() < 15000 and (*it)->getPosition().get_y() > 9250 and (*it)->getPosition().get_y() < 15000){
        i = ruta_noroeste_2((*it)->getId());

      }else if((*it)->getPosition().get_x() > 15000 and (*it)->getPosition().get_y() > 0 and (*it)->getPosition().get_y() < 9250){
        i = ruta_noroeste_3((*it)->getId());

      }else if((*it)->getPosition().get_x() < 8500 and (*it)->getPosition().get_y() >= 8500){
        i = ruta_suroeste((*it)->getId());

      }else if((*it)->getPosition().get_x() >= 8500 and (*it)->getPosition().get_x() <= 15000 and (*it)->getPosition().get_y() < -15000){
        i = ruta_noreste_1((*it)->getId());

      }else if((*it)->getPosition().get_x() > 15000 and (*it)->getPosition().get_y() <= -9250){
        i = ruta_noreste_2((*it)->getId());

      }else if((*it)->getPosition().get_x() > 8500 and (*it)->getPosition().get_x() < 15000 and (*it)->getPosition().get_y() < -9250 and (*it)->getPosition().get_y() > -15000){
        i = ruta_noreste_2((*it)->getId());

      }else if((*it)->getPosition().get_x() >= 15000 and (*it)->getPosition().get_y() < 0 and (*it)->getPosition().get_y() > -9250){
        i = ruta_noreste_3((*it)->getId());

      }else if((*it)->getPosition().get_x() < 8500 and (*it)->getPosition().get_y() <= -8500){
        i = ruta_sureste((*it)->getId());
      }
    }

    if(!Airport::getInstance()->is_booked_landing())
    {
      if(((*it)->getPosition().get_y() >= 0 or (*it)->getPosition().get_y() < 0) and (*it)->getPosition().get_x() >= 8500)
      {
        Airport::getInstance()->book_landing();
        (*it)->getRoute()->clear();
        i = ruta_aterrizaje_principal((*it)->getId());

      }else if((*it)->getPosition().get_y() >= 0 and (*it)->getPosition().get_x() < 8500)
      {
        Airport::getInstance()->book_landing();
        (*it)->getRoute()->clear();
        i = ruta_aterrizaje_izq((*it)->getId());

      }else if((*it)->getPosition().get_y() <= 0 and (*it)->getPosition().get_x() < 8500)
      {
        Airport::getInstance()->book_landing();
        (*it)->getRoute()->clear();
        i = ruta_aterrizaje_dcha((*it)->getId());
      }
    }
  }
}


}  // namespace atcsim
