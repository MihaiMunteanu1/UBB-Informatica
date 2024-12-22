class Agentie:
    def __init__(self,id,adresa,oras,pret,garantie):
        self.__id=id
        self.__adresa=adresa
        self.__oras=oras
        self.__pret=pret
        self.__garantie=garantie
    def get_id(self):
        return self.__id
    def get_adresa(self):
        return self.__adresa
    def get_oras(self):
        return self.__oras
    def get_pret(self):
        return self.__pret
    def get_garantie(self):
        return self.__garantie
    def set_adresa(self,new_adresa):
        self.__adresa=new_adresa
    def set_oras(self,new_oras):
        self.__oras=new_oras
    def set_pret(self,new_pret):
        self.__pret=new_pret
    def set_garantie(self,new_garantie):
        self.__garantie=new_garantie

    def __eq__(self, other):
        return self.__id==other.__id
    def __str__(self):
        return (f"{self.__id},{self.__adresa},{self.__oras},{self.__pret},{self.__garantie}")