from domain.materiale import Materiale


class RepositoryMaterialeFisiere():
    def __init__(self,cale_fisier,cale_fisier1,cale_fisier2):
        self._materiale = {}
        self.__cale_fisier=cale_fisier
        self.__cale_fisier1=cale_fisier1
        self.__cale_fisier2=cale_fisier2

    def __read_all_from_file(self):
        cale_fisier=self.__cale_fisier
        with open(cale_fisier,"r") as f:
            self._materiale.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    line.strip()
                    parti=line.split(',')
                    cod=int(parti[0])
                    denumire=parti[1]
                    unitate_masura=parti[2]
                    cantitate_pe_stoc=int(parti[3])
                    pret_unitar=int(parti[4])
                    material=Materiale(cod,denumire,unitate_masura,cantitate_pe_stoc,pret_unitar)
                    self._materiale[cod]=material
    def __write_all_to_file(self):
        cale_fisier=self.__cale_fisier
        with open(cale_fisier,"w") as f:
            for cod in self._materiale:
                f.write(str(self._materiale[cod])+'\n')
    def __goleste_fisier(self,path_fisier):
        with open(path_fisier,"w") as f:
            f.write('')
    def add_material(self):
        """
        Functie care citeste si adauga maetrialele din fisier in repository
        :return:
        """
        self.__read_all_from_file()
    def valoare_mai_mare(self, valoare):
        """
        Functia care ne afiseaza in alt fisier materialele care au o valoare mai mare decat
        una introdusa de noi de la tastatura
        :param valoare: ex:10
        :return:
        """
        self.__read_all_from_file()
        self.__goleste_fisier(self.__cale_fisier1)
        for materiale in self.get_all():
            produs=int(materiale.get_cantitate_pe_stoc()*materiale.get_pret_unitar())
            if produs>valoare:
                with open(self.__cale_fisier1,"a") as f:
                    f.write(f"{materiale.get_cod()},{materiale.get_denumire()},"
                            f"{materiale.get_cantitate_pe_stoc()},{materiale.get_pret_unitar()}"+'\n')
        self.__write_all_to_file()
    def efectueaza_vanzarea(self,cod,cantitate_ceruta):
        """
        Functie care efectueaza vanzarea daca cantitatea ceruta este mai mica decat
        cantitatea curenta de pe stoc. In caz afirmativ afiseaza pe ecranul mesajul 'vanzarea este
        posibila' si afiseaza in alt fisier text datele vanzarii
        :param cod:
        :param cantitate_ceruta:
        :return:
        """
        self.__read_all_from_file()
        for materiale in self.get_all():
            if materiale.get_cod()==cod:
                if materiale.get_cantitate_pe_stoc()>=cantitate_ceruta:
                    print("vanzarea este posibila")
                    with open(self.__cale_fisier2,"a") as f:
                        f.write(f"{materiale.get_denumire()},{cantitate_ceruta},{cantitate_ceruta*materiale.get_pret_unitar()}"+'\n')
                    materiale.set_cantitate_pe_stoc(materiale.get_cantitate_pe_stoc()-cantitate_ceruta)
                else:
                    raise Exception("cantitate invalida")
        self.__write_all_to_file()

    def get_all(self):
        """
        Functie care returneaza toate materialele din repository
        :return:
        """
        return [self._materiale[x] for x in self._materiale.keys()]