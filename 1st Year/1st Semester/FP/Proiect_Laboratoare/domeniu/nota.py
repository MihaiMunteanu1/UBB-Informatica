class Nota:
    def __init__(self,id_nota,student,laborator,val_nota):
        self.__id_nota=id_nota
        self.__student=student
        self.__laborator=laborator
        self.__val_nota=val_nota
    def get_id_nota(self):
        return self.__id_nota
    def get_student(self):
        return self.__student
    def get_laborator(self):
        return self.__laborator
    def get_val_nota(self):
        return self.__val_nota

    def __eq__(self, other):
        return self.__id_nota==other.__id_nota
    def __str__(self):
        return (f"{self.__id_nota},{self.__student.get_nume()},{self.__laborator.get_descriere()},{self.__val_nota}")