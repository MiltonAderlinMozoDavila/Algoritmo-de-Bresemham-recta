#include <iostream>
#include <conio.h>
#include <string>
#include "cPunto.h"

using namespace std;

class cBresemham
{
        /* *********************** ATRIBUTOS ************************ */
        private:
            cPunto *aPuntoInicial;
            cPunto *aPuntoFinal;
            int aNroPuntos;

        /* *********************** METODOS ************************ */
        public:
        /* ==================== CONSTRUCTORES ======================= */
        // ----------------------------------------------------------------
        cBresemham()
        {
            aPuntoInicial = new cPunto();
            aPuntoFinal = new cPunto();
            
        }

        // ----------------------------------------------------------------
        cBresemham( cPunto *pPuntoInicial, cPunto *pPuntoFinal)
        {
            
            aPuntoInicial = pPuntoInicial;
            aPuntoFinal = pPuntoFinal;
        }

        /* ==================== MÉTODOS GET Y SET ======================= */
        // ----------------------------------------------------------------
        cPunto *GetPuntoInicial()
        {
            return aPuntoInicial;
        }
        // ----------------------------------------------------------------
        void SetPuntoInicial(cPunto *pPuntoInicial)
        {
            aPuntoInicial = pPuntoInicial;
        }
        // ----------------------------------------------------------------
        cPunto *GetPuntoFinal()
        {
            return aPuntoFinal;
        }
        // ----------------------------------------------------------------
        void SetPuntoFinal(cPunto *pPuntoFinal)
        {
            aPuntoFinal = pPuntoFinal;
        }
        // ----------------------------------------------------------------
        float GetNroPuntos(){
            return aNroPuntos;
        }
        // ----------------------------------------------------------------
        //  --- DX : diferencial de X (Xf - Xi)
        float Get_DX(){
            return aPuntoFinal->GetX() - aPuntoInicial->GetX();
        }
        //  -- DY : diferencia de Y (Yf - Yi)
        float Get_DY(){
            return aPuntoFinal->GetY() - aPuntoInicial->GetY();
        }
        //  --- calcular la pendiente
        float Getpendiente(){
            return ((float)Get_DY()/Get_DX());
        }

        /* ==================== MÉTODOS PROCESO ======================= */

        //  --- --------------- evaluar pendiente ------------------
        int EvaluarPendiente(){
            //--- recuperar pendiente
            float Pendiente = Getpendiente();
            int caso ;
            //  --- si la pendiente  es menor a -1 ; (m < -1)
            
            if(Pendiente < -1 )
            {
                cout << " m  =  "<<Pendiente << "  --->si la pendiente es menor a -1 (m < -1)  procesa Caso : 1" << endl;
                caso = 1;
                aNroPuntos = Get_DY()*3;
            }
                
            else//entonces la pendiente es mayor a -1
            {
                //  --- si la pendientes  esta en el rago <-1, 0> (-1 < m < 0)
                if(Pendiente < 0 )
                {
                    cout << " m  =  "<<Pendiente << "  --->la pendiente  esta en el rago <-1, 0> ; (-1 < m < 0)   procesa Caso : 1" << endl;
                    caso = 2;
                    aNroPuntos = Get_DX()*3;
                }
                    
                else // entonces la pendiente es mayor a 0
                {   
                    // si pendiente esta el el rango <0 , 1> ( 0 < m < 1)
                    if(Pendiente < 1)
                    {
                        cout << " m  =  "<<Pendiente << "   ---> pendiente esta el el rango <0 , 1> ;  ( 0 < m < 1)   procesa Caso : 1 " << endl;
                        caso = 3;
                        aNroPuntos = Get_DX()*3;
                    }

                    else // --- entonces la pendiente es mayor 1 (m > 1)
                    {
                        cout << " m  =  "<<Pendiente << "  --->la pendiente es mayor 1 ;(m > 1)  procesa Caso : 1 " << endl;
                        caso = 4;
                        aNroPuntos = Get_DY()*3;
                    }
                }

            }
            //--- retornar caso
            return caso;
            
        }
        
        //  --- AQUI SE DESARRLLA EL ALGORITMO --- LE PUSE NOMOBRE GETPUNTOS PARA PODER MANIPULAR EXTERMAMENTE.
        //  --- obtener puntos de la grafica, esta funcion devuele un vector con los puntos de la grafica
        void GetPuntos(float *VectorPixel){
            //  --- evaluar pendiente
            int Caso = EvaluarPendiente();

            //  --- declarar variables
            float P;  // p: parametro de decicion
            float factorNorma = 0.001;
            float incrimento = 1;

            //  --- inicialicar variables
            float Xi = aPuntoInicial->GetX();
            float Yi = aPuntoInicial->GetY();

            float Xf = aPuntoFinal->GetX();
            float Yf = aPuntoFinal->GetY();

            float Dx = Get_DX();
            float Dy = Get_DY();
            //  --- agregar pixel inicial (punto incial)
            //float * VectorPixel = pVectorPixel; //-e agrega al vector los puntos en grupos de 3 (x,y,z) para z = 0
            int i = 0; // inicializamos i, recorrera el vector de puntos 
            VectorPixel[i++] = Xi*factorNorma;
            VectorPixel[i++] = Yi*factorNorma;
            VectorPixel[i++] = 0*factorNorma;   //  coordena Z para opemGL; 
        
            //  --- evaluar la pendiente
            switch (Caso)
            {
            //  --- si la pendfloate es menor a -1 (m < -1)
            case 1:
                //  --- calcular parametro de decicion inicial
                P= 2 * Dx + Dy;
                //  ---
                while (Yi <= Yf)// se incrementa a lo largo del eje Y.
                {
                    //  --- evaluar el parametro de decicion
                    if (P > 0)
                            // X = xi
                            P = P + (2 * Dx); // calcular nuevo parametro de decicion
                    else
                    {
                        Xi = Xi - incrimento; // actualizar x
                        P = P + (2 * Dx) + (2 * Dy); // calcular nuevo parametro de decicion
                    }
                    //  actualizar Y
                    Yi = Yi + incrimento;
                    //  --- agregar pixel al vector (siguiente punto)
                    VectorPixel[i++] = Xi*factorNorma;
                    VectorPixel[i++] = Yi*factorNorma;
                    VectorPixel[i++] = 0.0*factorNorma;   //  coordena Z para opemGL; 
                }
                
                break;//    --- fin del caso 1
            
            case 2: //  --- si la pendfloate esta en el rago <-1, 0>;  (-1 < m < 0)
                cout << " entra al caso 2 "<< endl;
                P = (2 * Dy) + Dx;  //--> calcular Parametro de decicion Inicial
                while (Xi <= Xf)
                {
                    if (P > 0)  // Evaluar paramentro de decicion
                    {
                        //  Yi = yi --se mantiene
                        P = P + (2 * Dy);   //---> calcular nuevo parametro de decicion
                    }
                    else
                    {
                        Yi = Yi - incrimento; // ---> Se se actualiza
                        P = P + (2 * Dy) + (2 * Dx); //---> calcular nuevo parametro de decicion
                    }
                    //----
                    Xi = Xi + incrimento;
                    //  --- agregar pixel al vector (siguiente punto)
                    VectorPixel[i++] = Xi*factorNorma;
                    VectorPixel[i++] = Yi*factorNorma;
                    VectorPixel[i++] = 0.0*factorNorma;   //  coordena Z para opemGL; 
                    cout << " entra al caso 2 "<< endl;
                }
                break; //    --- fin del caso 2
            
            case 3: // si pendiente esta el el rango <0 , 1> ( 0 < m < 1)
                P = (2 * Dy) - Dx;  //--> calcular Parametro de decicion Inicial
                while (Xi <= Xf )// incremento en X
                {
                    if (P < 0)  // Evaluar paramentro de decicion
                    {
                        //  Yi = yi --se mantiene
                        P = P + (2 * Dy);   //---> calcular nuevo parametro de decicion
                    }
                    else
                    {
                        Yi = Yi + incrimento; // ---> Se se actualiza
                        P = P + (2 * Dy) - (2 * Dx); //---> calcular nuevo parametro de decicion
                    }
                    //----
                    Xi = Xi + incrimento;
                    //  --- agregar pixel al vector (siguiente punto)
                    VectorPixel[i++] = Xi*factorNorma;
                    VectorPixel[i++] = Yi*factorNorma;
                    VectorPixel[i++] = 0*factorNorma;   //  coordena Z para opemGL; 
                }
                break;//    --- fin del caso 3
            
            case 4: // --- entonces la pendiente es mayor 1 (m > 1)
                P = (2 * Dx) - Dy;  //--> calcular Parametro de decicion Inicial
                while (Yi <= Yf )
                {
                    if (P < 0)  // Evaluar paramentro de decicion
                    {
                        //  X = xi --se mantiene
                        P = P + (2 * Dx);   //---> calcular nuevo parametro de decicion
                    }
                    else
                    {
                        Xi = Xi + incrimento; // ---> Se se actualiza
                        P = P + (2 * Dx) - (2 * Dy); //---> calcular nuevo parametro de decicion
                        
                    }
                    //----
                    Yi = Yi + incrimento;
                    //  --- agregar pixel al vector (siguiente punto)
                    VectorPixel[i++] = Xi*factorNorma;
                    VectorPixel[i++] = Yi*factorNorma;
                    VectorPixel[i++] = 0*factorNorma;   //  coordena Z para opemGL; 
               
                
                }
                break;//    --- fin del caso 4

            }
        }



       //   --- Leer puntos
       void LeerPuntos(){
        //  --- Leer punto inicial
        string rotulo;
        rotulo ="ALGORITMO DE BRESEMHAM PARA GRAFICAR UNA RECTA\n====================================================\n \n INGRESE 2 PUNTOS PARA GRTAFICAR \n\n";
        cout<<rotulo;
        aPuntoInicial->Leer(" INICIAL");
        cout<<"\n \n";
        aPuntoFinal->Leer(" FINAL ");
       } 

};

