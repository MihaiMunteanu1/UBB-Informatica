class Materiale:
    def __init__(self,cod,denumire,unitate_de_masura,cantitate_pe_stoc,pret_unitar):
        self.__cod=cod
        self.__denumire=denumire
        self.__unitate_de_masura=unitate_de_masura
        self.__cantitate_pe_stoc=cantitate_pe_stoc
        self.__pret_unitar=pret_unitar
    def get_cod(self):
        return self.__cod
    def get_denumire(self):
        return self.__denumire
    def get_unitate_de_masura(self):
        return self.__unitate_de_masura
    def get_cantitate_pe_stoc(self):
        return self.__cantitate_pe_stoc
    def get_pret_unitar(self):
        return self.__pret_unitar
    def set_denumire(self,new_denumire):
        self.__denumire=new_denumire
    def set_unitate_de_masura(self,new_um):
        self.__unitate_de_masura=new_um
    def set_cantitate_pe_stoc(self,new_cantitate):
        self.__cantitate_pe_stoc=new_cantitate
    def set_pret_unitar(self,new_pret):
        self.__pret_unitar=new_pret
    def __eq__(self, other):
        return self.__cod==other.__cod
    def __str__(self):
        return f"{self.__cod},{self.__denumire},{self.__unitate_de_masura},{self.__cantitate_pe_stoc},{self.__pret_unitar}"