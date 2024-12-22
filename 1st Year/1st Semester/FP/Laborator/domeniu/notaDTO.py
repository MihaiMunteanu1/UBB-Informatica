class NotaDTO:
    def __init__(self, id_nota, id_student, id_lab, valoare_nota):
        self.__id_nota = id_nota
        self.__id_student = id_student
        self.__id_lab = id_lab
        self.__valoare_nota = valoare_nota

    def get_id_nota(self):
        return self.__id_nota

    def get_id_laborator(self):
        return self.__id_lab

    def get_id_student(self):
        return self.__id_student

    def get_nota(self):
        return self.__valoare_nota

    def __str__(self):
        return f'{self.__id_nota},{self.__id_student},{self.__id_lab},{self.__valoare_nota}'