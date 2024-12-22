class Note:
    def __init__(self,id_nota,student,laborator,nota):
        self.__idnota = id_nota
        self.__student = student
        self.__laborator = laborator
        self.__nota = nota

    def get_nota_id(self):
        return self.__idnota

    def get_student(self):
        return self.__student

    def get_laborator(self):
        return self.__laborator

    def get_nota(self):
        return self.__nota


    def __str__(self):
         return f'{self.__idnota} {self.__student.get_nume()} a luat la laboratorul {self.__laborator.get_descriere()} nota {self.__nota}'

