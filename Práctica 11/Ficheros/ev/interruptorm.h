//---------------------------------------------------------
// interruptor.h
//---------------------------------------------------------

#include <iostream>
#include <thread>
#include <mutex>

//---------------------------------------------------------
using namespace std;

class interruptorm
{
public:
    interruptorm() 
        : leidos(0), 
          escritos(0) 
    {
    }

	void seccion_critica(char c)
	{
		for (char i = 0; i < 10; ++i)
			cout << c++;
		cout << endl;
	}

    void adquirirLectura()
    {   
        interno.lock();
        if (leidos == 0)  
            contenido.lock();

        ++leidos;
        if(leidos > 0 && escritos == 0)
        	seccion_critica('0');
        interno.unlock();
    }
    
    void adquirirEscritura()
    {   
        contenido.lock();
        ++escritos;
        if(escritos == 1 && leidos == 0)
        	seccion_critica('a');
    }
    
    void liberarLectura()
    {   
        interno.lock();
        --leidos;

        if (leidos == 0 && escritos == 0 && leidos >= 0)	  
            contenido.unlock();
        interno.unlock();
    }

    void liberarEscritura()
    {   
        --escritos;

        if(leidos == 0 && escritos == 0)
        	contenido.unlock();
    }
    
private:
    mutex contenido;
    mutex interno;
    int leidos;
    int escritos;
};    


//---------------------------------------------------------

