#include <iostream>
//Juan Miguel Regalado Nuño
//Practica Lista doblemente ligada 
template<class T>
class LDLLSE;

class Socio{
private:
    int numeroSocio;
    int anioIngreso;
    std::string nombre;
    std::string domicilio;
public:
    Socio():numeroSocio(0), anioIngreso(0), nombre(""), domicilio(""){};

    friend std::ostream & operator<<(std::ostream &os, Socio &x){
        os<<"Nombre del Socio: "<<x.nombre<<std::endl;
        os<<"Domicilio de Socio: "<<x.domicilio<<std::endl;
        os<<"Numero de Socio: "<<x.numeroSocio<<std::endl;
        os<<"Año de ingreso: "<<x.anioIngreso<<std::endl;
        return os;
    }
    friend std::istream & operator>>(std::istream &is, Socio &x){
        std::cout<<"Nombre del Socio: ";
        is>>x.nombre;
        std::cout<<"Domicilio de Socio: ";
        is>>x.domicilio;
        std::cout<<"Numero de Socio: ";
        is>>x.numeroSocio;
        std::cout<<"Anio de ingreso: ";
        is>>x.anioIngreso;
        return is;
    }
    bool operator == (Socio &a){
            return nombre == a.nombre && domicilio == a.domicilio && numeroSocio == a.numeroSocio && anioIngreso == a.anioIngreso;
    }
    bool operator != (Socio &a){
            return nombre != a.nombre || domicilio != a.domicilio;
    }

    int getNumeroSocio(){
        return numeroSocio;
    }
    void setNombre(std::string n){
        nombre = n;
    }
    void setDomicilio(std::string d){
        domicilio = d;
    }

    //friend class LDLLSE<Socio>;
};

template<class T>
class nodo{
private:
    T data;
    nodo<T>* sig;
    nodo<T>* ant;
public:
    nodo():sig(nullptr), ant(nullptr){};
    friend class LDLLSE<T>;
    T getData(){
        return data;
    }
    nodo<T>* getSig(){
        return sig;
    }
};

template<class T>
class LDLLSE{
private:
    nodo<T>* ancla;
public:
    LDLLSE(): ancla(nullptr){};
    bool vacia()const;
    nodo<T>* primero()const;
    nodo<T>* ultimo()const;
    nodo<T>* anterior(nodo<T>*)const;
    nodo<T>* siguiente(nodo<T>* )const;
    nodo<T>* localiza(T)const;
    T recupera(nodo<T>* )const;
    void imprime()const;
    void anula();
    void inserta(nodo<T>* pos, T elem);
    void elimina(nodo<T>* pos);
};

template<class T>
void LDLLSE<T>::inserta(nodo<T>* pos, T elem){
    nodo<T>* aux= new nodo<T>;
    aux->data=elem;
    if(pos==nullptr){
        aux->sig=ancla;
        if(ancla)
            ancla->ant=aux;
        ancla=aux;
    }
    else{
        aux->sig=pos->sig;
        if(pos->sig)
            pos->sig->ant= aux;
        pos->sig=aux;
        aux->ant=pos;
    }
}

template<class T>
void LDLLSE<T>::elimina(nodo<T>* pos){
    if(vacia() || pos==nullptr){
        return;
    }

    if(pos->ant){
        pos->ant->sig = pos->sig;
    }
    if(pos->sig){
        pos->sig->ant = pos->ant;
    }
    if(pos==ancla){
        ancla=ancla->sig;
    }
    delete pos;
}

template<class T>
nodo<T>* LDLLSE<T>::primero()const{
    return ancla;
}

template<class T>
nodo<T>* LDLLSE<T>::ultimo()const{
    if(vacia()){
        return ancla;
    }
    else{
        nodo<T>* aux=ancla;
        while(aux->sig!=nullptr){
            aux=aux->sig;
        }
        return aux;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::anterior(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return nullptr;
    }
    else{
        return pos->ant;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::siguiente(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return nullptr;
    }
    else{
        return pos->sig;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::localiza(T elem)const{
    nodo<T>* aux=ancla;
    while(aux!=nullptr && aux->data!=elem){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
T LDLLSE<T>::recupera(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){

    }
    else{
        return pos->data;
    }
}


template<class T>
bool LDLLSE<T>::vacia()const{
    if(ancla==nullptr){
        return true;
    }
    return false;
}

template<class T>
void LDLLSE<T>::imprime()const{
    if(!vacia()){
        nodo<T>* aux=ancla;
        while(aux!=nullptr){
            std::cout<<aux->data<<std::endl;
            aux=aux->sig;
        }
    }
}

template<class T>
void LDLLSE<T>::anula(){
    nodo<T>* aux;
    while(ancla!=nullptr){
        aux=ancla;
        ancla=aux->sig;
        delete aux;
    }
}

int main()
{
    LDLLSE<Socio> milista;
    Socio elem;
    nodo<Socio>* pos = nullptr;
    bool flag = true;
    int opc;
    std::string aux;

    do
    {
        system("cls");
        std::cout<<"Digite una opcion\n"<<std::endl;
        std::cout<<"[1] Registrar un nuevo Socio"<<std::endl;
        std::cout<<"[2] Dar de baja a un Socio"<<std::endl;
        std::cout<<"[3] Reporte de todos los Socios"<<std::endl;
        std::cout<<"[4] Buscar a un Socio"<<std::endl;
        std::cout<<"[5] Salir"<<std::endl<<": ";
        std::cin>>opc;

        switch (opc)
        {
            case 1:
                system("cls");
                std::cout<<"Registrar un nuevo Socio\n"<<std::endl;
                std::cout<<"Ingrese los datos del Socio:"<<std::endl;
                std::cin>>elem;
                pos = milista.primero();
                flag=true;
                while(pos && flag){
                    if(pos->getData().getNumeroSocio() == elem.getNumeroSocio())
                        flag = false;
                    pos = pos->getSig();
                }
                if(flag){
                    milista.inserta(milista.ultimo(), elem);
                    std::cout<<"\nEl socio se ha registrado"<<std::endl;
                }
                else
                    std::cout<<"\nYa hay un socio con el mismo numero de Socio"<<std::endl;
                system("pause");
            break;
            case 2:
                system("cls");
                std::cout<<"Dar de baja a un Socio\n"<<std::endl;
                std::cout<<"Ingrese los datos del Socio:"<<std::endl;
                std::cin>>elem;
                milista.elimina(milista.localiza(elem));
                system("pause");
            break;
            case 3:
                system("cls");
                std::cout<<"Reporte de todos los Socios\n"<<std::endl;
                milista.imprime();
                system("pause");
            break;
            case 4:
                system("cls");
                std::cout<<"Buscar a un Socio\n"<<std::endl;
                std::cout<<"Ingrese los datos del Socio:"<<std::endl;
                std::cout<<"Nombre: ";
                std::cin>>aux; elem.setNombre(aux);
                std::cout<<"Domicilio: ";
                std::cin>>aux; elem.setDomicilio(aux);
                if(milista.localiza(elem)){
                    elem = milista.localiza(elem)->getData();
                    std::cout<<"\n\nLos datos del socio son:"<<std::endl<<elem;
                }
                else
                    std::cout<<"No se encontro el socio"<<std::endl;
                system("pause");
            break;
        }
    } while (opc != 5);


    return 0;
}
