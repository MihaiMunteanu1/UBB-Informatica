from domain.tractor import Tractor
import datetime
class FileRepositoryTractoare:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier
        self.__tractoare={}
        self.__undo={}

    def __read_all_from_file(self):
        """
        Functie care citeste toate tractoarele din fisier si le pune in repository
        :return:
        """
        with open(self.__cale_fisier,'r') as f:
            self.__tractoare.clear()
            lines=f.readlines()
            for line in lines:
                line=line.strip()
                if line!=' ':
                    parti=line.split(',')
                    id=int(parti[0])
                    denumire=parti[1]
                    pret=int(parti[2])
                    model=parti[3]
                    data=parti[4]
                    tractor=Tractor(id,denumire,pret,model,data)
                    self.__tractoare[id]=tractor

    def __write_all_to_file(self):
        """
        Functie care scrie toate tractoarele in fisier
        :return:
        """
        with open(self.__cale_fisier,'w') as f:
            for id in self.__tractoare:
                f.write(str(self.__tractoare[id])+'\n')

    def __expirare_revizie(self, data):
        """
        Functie care verifica daca data de revizie a unui tractor e expirata
        :param data:
        :return:
        """
        zi = int(data[0:2])
        luna = int(data[3:5])
        an = int(data[6:])
        data_azi = str(datetime.date.today())
        zi_azi = int(data_azi[8:])
        luna_azi = int(data_azi[5:7])
        an_azi = int(data_azi[0:4])
        if an < an_azi:
            return 0
        elif an == an_azi:
            if luna < luna_azi:
                return 0
            elif luna == luna_azi:
                if zi < zi_azi:
                    return 0
        return 1
    def filtreaza_tractoare(self,text,numar):
        """
        Functie care verifica pentru fiecare caz de filtrare
        1. text!='' si numar!=-1
        2. text!=-1 si numar==-1
        3. text==-1 si numar==-1
        4. text==-1 si numar!=-1
        Si creeaza lista result care contine toata tractoarele care indeplinesc conditiile(parametrul text se afla in denumirea lor
        si pretul lor este mai mic decat parametrul numar)
        Lista final_result adauga '*' in fata denumirii tractoarelor a caror data de revizie este expirata
        :param text:
        :param numar:
        :return:
        """
        result=[]
        if text!='' and numar!=-1:
            for tractor in self.get_all():
                denumire=tractor.get_denumire()
                if text in denumire:
                    pret=tractor.get_pret()
                    if pret<numar:
                        result.append(tractor)
        if text!='' and numar==-1:
            for tractor in self.get_all():
                denumire=tractor.get_denumire()
                if text in denumire:
                    result.append(tractor)
        if text=='' and numar!=-1:
            for tractor in self.get_all():
                pret=tractor.get_pret()
                if pret<numar:
                    result.append(tractor)
        if text=='' and numar==-1:
            return []
        final_result=[]
        if result!=[]:
            for tractor in result:
                data=tractor.get_data()
                if self.__expirare_revizie(data)==1:
                    final_result+=[f'{tractor.get_id()},{tractor.get_denumire()},{tractor.get_pret()},{tractor.get_model()},{tractor.get_data()}']
                else:
                    final_result+=[f'{tractor.get_id()},*{tractor.get_denumire()},{tractor.get_pret()},{tractor.get_model()},{tractor.get_data()}']
        return final_result

    def undo(self):
        """
        Functie care face operatia de undo, lista de undo primeste valoare listei de tractoare inainte de actiunile
        de adaugare si stergere, iar aici lista de tractoare va deveni lista de undo
        :return:
        """
        self.__read_all_from_file()
        self.__tractoare.clear()
        self.__tractoare=self.__undo.copy()
        self.__write_all_to_file()

    def add_tractor(self,tractor):
        """
        Functie care verifica daca id-ul tractorului pe care dorim sa-l adaugam exista sau nu deja in repository
        Daca nu exista adaugam un tractor nou si il scriem dupa in fisier
        :param tractor:
        :return:
        """
        self.__read_all_from_file()
        id_tractor=tractor.get_id()
        if id_tractor in self.__tractoare:
            raise Exception("id existent")
        self.__undo=self.__tractoare.copy()
        self.__tractoare[id_tractor]=tractor
        self.__write_all_to_file()

    def sterge_tractor(self,cifra):
        """
        Functie care sterge tractoarele al caror id contine
        o anumita cifra data de noi si dupa le scrie pe cele ramase in fisier
        :param cifra:
        :return:
        """
        self.__read_all_from_file()
        toate_tractoare=self.get_all()
        ok=int(0)
        self.__undo=self.__tractoare.copy()
        for tractor in toate_tractoare:
            id_tractor=tractor.get_id()
            copie_id=id_tractor
            while copie_id >0:
                cifra_id=copie_id%10
                if cifra_id==cifra:
                    del self.__tractoare[id_tractor]
                    ok=1
                    copie_id=0
                copie_id=copie_id/10
        if ok==1:
            self.__write_all_to_file()

    def get_all(self):
        """
        Functie care returneaza toata tractoarele
        :return:
        """
        self.__read_all_from_file()
        return [self.__tractoare[x] for x in self.__tractoare.keys()]