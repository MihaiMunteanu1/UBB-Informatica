class Emisiune:
    def __init__(self,id,nume,tip,durata,descriere):
        self.__id=id
        self.__nume=nume
        self.__tip=tip
        self.__durata=durata
        self.__descriere=descriere
    def get_id(self):
        return self.__id
    def get_nume(self):
        return self.__nume
    def get_tip(self):
        return self.__tip
    def get_durata(self):
        return self.__durata
    def get_descriere(self):
        return self.__descriere
    def set_durata(self,new_durata):
        self.__durata=new_durata
    def set_descriere(self,new_desc):
        self.__descriere=new_desc
    def __eq__(self, other):
        return self.__id==other.__id

    def __str__(self):
        return (f'{self.__id},{self.__nume},{self.__tip},{self.__durata},{self.__descriere}')