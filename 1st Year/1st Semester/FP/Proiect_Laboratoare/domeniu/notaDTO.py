class NotaDTO:
    def __init__(self,id_nota,id_student,id_laborator,val_nota):
        self.__id_nota=id_nota
        self.__id_student=id_student
        self.__id_laborator=id_laborator
        self.__val_nota=val_nota

    def get_id_nota(self):
        return self.__id_nota
    def get_id_student(self):
        return self.__id_student
    def get_id_laborator(self):
        return self.__id_laborator
    def get_val_nota(self):
        return self.__val_nota

    def __eq__(self, other):
        return self.__id_nota==other.__id_nota
    def __str__(self):
        return (f"{self.__id_nota},{self.__id_student},{self.__id_laborator},{self.__val_nota}")