class StudentRepository:
    def __init__(self):
        self.__studentz={}

    def add_student(self,student):
        id_student=student.get_id_student()
        if id_student in self.__studentz:
            raise Exception("id existent")
        self.__studentz[id_student]=student

    def sterge_student(self,id_student):
        if id_student in self.__studentz:
            del self.__studentz[id_student]
        else:
            raise Exception("student inexistent")

    def modifica_student(self,student):
        id_student=student.get_id_student()
        if id_student in self.__studentz.keys():
            self.__studentz[id_student]=student
        else:
            raise Exception("id invalid")

    def cauta_student_dupa_id(self,id_student):
        if id_student<0:
            raise Exception("id invalid")
        """for id_studenti in self.__studentz.keys():
            student = self.__studentz[id_studenti]
            if student.get_id_student() == id_student:
                return student
        SAU        
                """
        if id_student in self.__studentz:
            return self.__studentz[id_student]
        raise Exception("Nu exista studenti cu acest id")

    def get_all(self):
        return [self.__studentz[x] for x in self.__studentz.keys()]

