class Student:
    def __init__(self, studentID, nume, grup):
        self.__studentID=studentID
        self.__nume=nume
        self.__grup=grup

    def get_studentid(self):
        return self.__studentID
    def get_nume(self):
        return self.__nume
    def get_grup(self):
        return self.__grup

    def set_studentid(self,new_studentID):
        self.__studentID=new_studentID
    def set_nume(self,new_nume):
        self.__nume=new_nume
    def set_grup(self,new_grup):
        self.__grup=new_grup

    def __eq__(self,other):
        return self.__studentID == other.__studentID

    """def __str__(self):
        return (f"ID: [{self.__studentID}] Nume: {self.__nume} Grup: {self.__grup}")"""
    def __str__(self):
        return (f"{self.__studentID},{self.__nume},{self.__grup}")