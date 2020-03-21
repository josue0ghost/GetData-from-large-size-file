#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define bufzise 8388608 //tam buffer

char bytes[bufzise];//buffer de lectura
long res[128];//respuesta de analisis
char readdone;//bandera de fin
FILE *fp; //archivo de origen

void* ReadFile()
{
    //variables de metodo
    int count; //bytes leidos
    char flread; //bandera de primera linea
    char byt[1024];
    int i; //indice
    int by; //indice
    flread = 0;
    while (flread == 0)
    {
        count = fread(&byt,1,1024,fp);
        for (i = 0; i < count; i++)
        {
            //posición de resultado
            by = byt[i];
            if (flread == 1)
            {
                //primera linea hecha, acumular
                res[by]++;
            }
            else
            {
                //identificar primera linea
                if(by == 13 || by == 10) flread = 1;
            }
        }
    }
    count = bufzise;
    //leer hasta fin de archivo
    while (count == bufzise){
        //leer buffer
        count = fread(&bytes,1,bufzise,fp);
        for (i = 0; i < count; i++)
        {
            //posición de resultado
            by = bytes[i];
            res[by]++;
        }
    }
    //marca la bandera
    readdone = 1;
}

int main(void){
    //variables metodo
    time_t tinit, tfini, tref; //variables de tiempo
    double di; //diferencia de valor
    long a; //valor de respuesta
    char c; //caracter de referencia
    int i; //indice
    pthread_t idH; //indice de hilo
    char file_name[75];//archivo de origen
    char resf_name[75];//archivo de resultado
    FILE *rs; //archivo de respuesta
    //ruta de archivo de origen
    printf("Ingrese Archivo\n");
    scanf("%s",file_name);
    //ruta de archivo de respuesta
    printf("Archivo de Resultado\n");
    scanf("%s",resf_name);
    //marca tiempo de inicio
    time(&tinit);
    //abrir archivo de origen
    fp = fopen(file_name,"r");
    if (fp == NULL){
        perror("Error al abrir archivo\n");
        exit(EXIT_FAILURE);
    }
    //crea hilo de lectura
    readdone = 0;//marca la bandera
    pthread_create(&idH,NULL,ReadFile,NULL);
    //marca tiempo de inicio info
    time(&tref);
    //hasta bandera arriba
    while (readdone == 0)
    {
        //marca tiempo actual
        time(&tfini);
        if(difftime(tfini,tref)>0){
            //cada segundo
            di = difftime(tfini,tinit);
            printf("Segundos en Ejecución = %f\n", di);
            //imprimir resultado
            c = 97;
            for (i = 65; i < 91; i++)
            {
                a = res[i] + res[c];
                c++;
                printf("%c,%ld\n",i,a);
            }
            //marca tiempo de inicio info
            time(&tref);
        }
    }
    //cierra archivo
    fclose(fp);
    //crear archivo de respuesta
    rs = fopen(resf_name,"w");
    if (rs == NULL){
        perror("Error al crear archivo\n");
        exit(EXIT_FAILURE);
    }
    //tiempo de fin de examen
    time(&tfini);
    di = difftime(tfini,tinit);
    printf("Segundos en Ejecución = %f\n", di);
    //imprime resultado
    c = 97;
    for (i = 65; i < 91; i++)
    {
        a = res[i] + res[c];
        c++;
        printf("%c,%ld\n",i,a);
        fprintf(rs,"%c,%ld\n",i,a);
    }
    fclose(rs);
    printf("Fin de Programa\n");
}