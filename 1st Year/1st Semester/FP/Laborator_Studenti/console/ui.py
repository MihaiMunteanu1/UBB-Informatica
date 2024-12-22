class UI:
    def __init__(self,srv_student):
        self.__service_student=srv_student
        self.__comands={
            "add_student":self.__ui_add_student,
            "print_student":self.__ui_print_student,
            "sterge_student":self.__ui_sterge_student,
            "modifica_student":self.__ui_modifica_student,
            "cauta_student_dupa_id":self.__ui_cauta_student_dupa_id,
            "sortare_dupa_grup":self.__ui_sortare_dupa_grup
        }
    def __ui_sortare_dupa_grup(self,params):
        if len(params) != 0:
            raise Exception("nr parametrii invalid")
            return
        studenti_sortati=self.__service_student.sortare_dupa_grup()
        for student in studenti_sortati:
            print(student)
    def __ui_cauta_student_dupa_id(self,params):
        if len(params) != 1:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student = int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        student=self.__service_student.cauta_student_dupa_id(id_student)
        print(student)
    def __ui_modifica_student(self,params):
        if len(params) != 3:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student = int(params[0])
            nume=params[1]
            grup=int(params[2])
        except ValueError:
            raise Exception("valoari numerice invalide")
        self.__service_student.modifica_student(id_student,nume,grup)
        print("student modificat cu succes")
    def __ui_sterge_student(self,params):
        if len(params) != 1:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__service_student.sterge_student(id_student)
        print("student sters cu succes")
    def __ui_print_student(self,params):
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        studenti=self.__service_student.get_all()
        for student in studenti:
            print(student)
    def __ui_add_student(self,params):
        if len(params)!=3:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_student=int(params[0])
            nume=params[1]
            grup=int(params[2])
        except ValueError:
            raise Exception("valori invalide")
        self.__service_student.add_student(id_student,nume,grup)
        print("student adaugat cu succes")

    def run(self):
        while True:
            cmd=input(">>>")
            cmd.strip()
            if cmd=="exit":
                return
            parti=cmd.split(" ")
            nume_comanda=parti[0]
            params=parti[1:]
            if nume_comanda in self.__comands:
                try:
                    self.__comands[nume_comanda](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida")