from domain.emisiune import Emisiune
import random
class RepositoryEmisiuniFiles:
    def __init__(self,cale_fisier):
        self.__emisiuni={}
        self.__cale_fisier=cale_fisier

    def __read_all_from_file(self):
        with open(self.__cale_fisier,'r') as f:
            self.__emisiuni.clear()
            lines=f.readlines()
            for line in lines:
                line=line.strip()
                if line!='':
                    parti=line.split(',')
                    id=int(parti[0])
                    nume=parti[1]
                    tip=parti[2]
                    durata=int(parti[3])
                    descriere=parti[4]
                    emisiune=Emisiune(id,nume,tip,durata,descriere)
                    self.__emisiuni[id]=emisiune
    def __write_all_to_file(self):
        with open(self.__cale_fisier,'w') as f:
            for id in self.__emisiuni:
                f.write(str(self.__emisiuni[id])+'\n')
    def update(self,nume,tip,durata,descriere):
        self.__read_all_from_file()
        emisiuni = self.get_all()
        ok=int(0)
        for emisiune in emisiuni:
            if emisiune.get_nume() == nume and emisiune.get_tip() == tip:
                emisiune.set_durata(durata)
                emisiune.set_descriere(descriere)
                ok=1
        if ok==0:
            raise Exception("nu exista emisiunea respectiva")
        else:
            self.__write_all_to_file()
            self.__read_all_from_file()
    def ore(self,ora_inceput,ora_sfarsit):
        emisiune_toate = self.get_all()
        result = []
        while len(emisiune_toate)>0:
            x = int(random.randint(ora_inceput, ora_sfarsit))
            ok=int(0)
            for emisiune in emisiune_toate:
                durata = int(emisiune.get_durata())
                if durata == x:
                    result.append(emisiune)
                    emisiune_toate.remove(emisiune)
                    ok=1
            if ok==0:
                emisiune_toate.remove(emisiune)
        return result
    def sterge(self,nume,tip):
        self.__read_all_from_file()
        emisiuni=self.get_all()
        ok=int(0)
        for emisiune in emisiuni:
            if emisiune.get_nume()==nume and emisiune.get_tip()==tip:
                del self.__emisiuni[emisiune.get_id()]
                ok=1
        if ok==0:
            raise Exception("nume/tip invalid")
        else:
            self.__write_all_to_file()
            self.__read_all_from_file()

    def get_all(self):
        self.__read_all_from_file()
        return [self.__emisiuni[x] for x in self.__emisiuni.keys()]