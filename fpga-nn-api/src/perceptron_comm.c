/*******************************************************************************
 *	perceptron_comm.c
 *
 *  Functionality to communicate with the perceptron
 *
 *
 *  This file is part of fpga-nn
 * 
 *  Copyright (C) 2015  Dennis Pinto Rivero
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/


#include "perceptron_comm.h"
#include <stdio.h>
#include <stdlib.h>

int write_weights(perceptron_package_t *p) {
    FILE *fp;
    byte response;
    byte package[5];
    
    // open file
    fp = fopen(FILE_NAME, "a+");
    if (fp == NULL)
        return 102;
    
    p->operation = WRITE_WEIGHTS;
    
    // write data
    package[0] = p->operation;
    package[1] = ((byte*)(&p->weight1))[1];    // w1 high
    package[2] = ((byte*)(&p->weight1))[0];    // w1 low
    package[3] = ((byte*)(&p->weight2))[1];    // w2 high
    package[4] = ((byte*)(&p->weight2))[0];    // w2 low
    
    fwrite(package, sizeof(byte)*5, 1, fp);
    
    // flush data
    fflush(fp);
    
    // read response
    //fread(&response, sizeof(byte), 1, fp);
    response = WRITE_OK;
    
    // close file
    fclose(fp);
    
    return response;
}


int write_inputs(perceptron_package_t *p) {
    FILE *fp;
    byte response;
    byte package[5];
    
    // open file
    fp = fopen(FILE_NAME, "a+");
    if (fp == NULL)
        return 102;
    
    p->operation = WRITE_INPUTS;
    
    // write data
    package[0] = p->operation;
    package[1] = ((byte*)(&p->input1))[1];    // i1 high
    package[2] = ((byte*)(&p->input1))[0];    // i1 low
    package[3] = ((byte*)(&p->input2))[1];    // i2 high
    package[4] = ((byte*)(&p->input2))[0];    // i2 low
    
    fwrite(package, sizeof(byte)*5, 1, fp);
    
    // flush data
    fflush(fp);
    
      
    // read response
    //fread(&response, sizeof(byte), 1, fp);
    response = WRITE_OK;
    
    // close file
    fclose(fp);
    
    return response;
}

int read_perceptron(perceptron_package_t *p) {
    FILE *fp;
    byte response;
    byte package[7];
    
    // Open file
    fp = fopen(FILE_NAME, "a+");
    if (fp == NULL)
        return 102;
    
    p->operation = WRITE_INPUTS;
    
    
    // write data
    package[0] = READ_RESPONSE;
    
    fwrite(package, sizeof(byte), 1, fp);
    
    // flush data
    fflush(fp);
    
    // read data
    fread(package, sizeof(byte)*7, 1, fp);
    
    p->operation = package[0];
    p->weight1 = (package[1] << 8) || package[2];
    p->weight2 = (package[3] << 8) || package[4];
    p->result = (package[5] << 8) || package[6];
    
    // close file
    fclose(fp);
    
    return p->operation;
}
