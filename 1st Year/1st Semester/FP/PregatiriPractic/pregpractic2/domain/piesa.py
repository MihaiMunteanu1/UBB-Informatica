class Piesa:
    def __init__(self,id,titlu,regizor,gen,durata):
        self.__id=id
        self.__titlu=titlu
        self.__regizor=regizor
        self.__gen=gen
        self.__durata=durata

    def get_id(self):
        return self.__id
    def get_titlu(self):
        return self.__titlu
    def get_regizor(self):
        return self.__regizor
    def get_gen(self):
        return self.__gen
    def get_durata(self):
        return self.__durata
    def set_gen(self,new_gen):
        self.__gen=new_gen
    def set_durata(self,new_durata):
        self.__durata=new_durata
    def __str__(self):
        return (f'{self.__id},{self.__titlu},{self.__regizor},{self.__gen},{self.__durata}')