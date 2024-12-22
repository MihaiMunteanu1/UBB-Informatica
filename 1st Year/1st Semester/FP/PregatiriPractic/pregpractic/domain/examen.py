class Examen:
    def __init__(self,id,data,ora,materia,tip):
        self.__id=id
        self.__data=data
        self.__ora=ora
        self.__materia=materia
        self.__tip=tip
    def get_id(self):
        return self.__id
    def get_data(self):
        return self.__data
    def get_ora(self):
        return self.__ora
    def get_materia(self):
        return self.__materia
    def get_tip(self):
        return self.__tip
    def set_data(self,new_data):
        self.__data=new_data
    def set_ora(self,new_ora):
        self.__ora=new_ora
    def set_materia(self,new_materia):
        self.__materia=new_materia
    def set_tip(self,new_tip):
        self.__tip=new_tip
    def __eq__(self, other):
        return self.__id==other.__id
    def __str__(self):
        return (f"{self.__id},{self.__data},{self.__ora},{self.__materia},{self.__tip}")
