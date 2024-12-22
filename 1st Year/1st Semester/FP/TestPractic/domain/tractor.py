class Tractor:
    def __init__(self,id,denumire,pret,model,data):
        self.__id=id
        self.__denumire=denumire
        self.__pret=pret
        self.__model=model
        self.__data=data

    def get_id(self):
        return self.__id
    def get_denumire(self):
        return self.__denumire
    def get_pret(self):
        return self.__pret
    def get_model(self):
        return self.__model
    def get_data(self):
        return self.__data
    def set_denumire(self,new_denumire):
        self.__denumire=new_denumire
    def set_pret(self,new_pret):
        self.__pret=new_pret
    def set_model(self,new_model):
        self.__model=new_model
    def set_data(self,new_data):
        self.__data=new_data
    def __eq__(self, other):
        return self.__id==other.__id
    def __str__(self):
        return (f'{self.__id},{self.__denumire},{self.__pret},{self.__model},{self.__data}')