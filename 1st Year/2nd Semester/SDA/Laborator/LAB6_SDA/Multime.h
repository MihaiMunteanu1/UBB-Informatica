#pragma once
#include <cmath>
#define EMPTY_POSITION -999999
#define DELETED_POSITION 999999
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
        TElem* elemente;
        int capacitate;
        int dimensiune;

        int hashFunction1(TElem elem) const{
            return elem % capacitate;
        }
        int hashFunction2(TElem elem) const{
            return 1 + (elem % (capacitate - 1));
        }

        int doubleHash(TElem elem) const{
            int aux_elem = abs(elem);
            int probe_number = 0;
            int position;
            bool gasit = false;
            while (!gasit){
                position = (hashFunction1(aux_elem) + probe_number * hashFunction2(aux_elem)) % capacitate;
                if (elemente[position] == EMPTY_POSITION || elemente[position] == DELETED_POSITION){
                    gasit = true;
                }
                else{
                    probe_number++;
                    if (probe_number >= capacitate){
                        return -1;
                    }
                }
            }
            return position;
        }
        void resize();

    public:
 		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

        int get_capacitate() const{
            return this->capacitate;
        }
        const TElem* get_elemente() const{
            return elemente;
        }
		// destructorul multimii
		~Multime();

        bool submultime(Multime& m) const;
};



