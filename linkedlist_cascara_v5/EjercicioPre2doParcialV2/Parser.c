#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Empleado.h"

#define BUFFER 2000

int parser_parseEmpleados(char* fileName, LinkedList* listaEmpleados)
{
    int retorno = -1;
    char* bufferId;
    char* bufferName;
    char* bufferHorasTrabajadas;
    char bufferText[BUFFER];
    FILE* auxFile = fopen(fileName,"r");
    Empleado* pEmployee;

    if(auxFile != NULL)
    {
        while(!feof(auxFile))
        {
            fgets(bufferText,sizeof(bufferText),auxFile);
            if(bufferText != NULL || strlen(bufferText) > 8)
            {

                bufferId = strtok(bufferText,",");
                bufferName = strtok(NULL,",");
                bufferHorasTrabajadas = strtok(NULL,"\n");

                pEmployee = employee_newConParametros(bufferId,bufferName,bufferHorasTrabajadas,"1");
                if(pEmployee != NULL)
                {
                    ll_add(listaEmpleados,pEmployee);//Se agrega ELEMENTO a LINKED LIST
                    retorno = 0;
                }
            }
        }
        fclose(auxFile);
    }
    return retorno;
}


int parser_SaveToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Empleado* auxEmployee;
    int len;
    int index;
    int bufferId;
    char bufferName[BUFFER];
    int bufferHorasTrabajadas;
    float bufferSueldo;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        len = ll_len(pArrayListEmployee);

        for(index=0;index<len;index++)//Recorro todo el array hasta el LEN
        {
            auxEmployee = ll_get(pArrayListEmployee,index);//Obtengo el elemento del array en posicion index
            employee_getAll(auxEmployee,bufferName,&bufferHorasTrabajadas,&bufferSueldo,&bufferId);
            fprintf(pFile,"%d,%s,%d,%.2f\n",bufferId,bufferName,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    return retorno;
}


//Estudiar strstr (Busca un string dentro de un string)
//Tratar de parsear un archivo JSON
